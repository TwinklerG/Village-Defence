#include "Map.h"

template <class T>
bool checkMouseSelect(T target, sf::RenderWindow *l_wind)
{
  return target.getPosition().x - target.getSize().x / 2 <= sf::Mouse::getPosition(*l_wind).x &&
         target.getPosition().x + target.getSize().x / 2 >= sf::Mouse::getPosition(*l_wind).x &&
         target.getPosition().y - target.getSize().y / 2 <= sf::Mouse::getPosition(*l_wind).y &&
         target.getPosition().y + target.getSize().y / 2 >= sf::Mouse::getPosition(*l_wind).y;
}

template <class T, class F>
bool checkInRange(T source, F target, double range)
{
  return ((double)source.getPosition().x - target.getPosition().x) * ((double)source.getPosition().x - target.getPosition().x) + ((double)source.getPosition().y - target.getPosition().y) * ((double)source.getPosition().y - target.getPosition().y) <= range * range;
}

template <class F>
bool checkCollision(sf::CircleShape source, F target)
{
  return (source.getPosition().x - target.getPosition().x) * (source.getPosition().x - target.getPosition().x) + (source.getPosition().y - target.getPosition().y) * (source.getPosition().y - target.getPosition().y) <= (source.getRadius() + target.getSize().x) * (source.getRadius() + target.getSize().x) / 4 + (source.getRadius() + target.getSize().y) * (source.getRadius() + target.getSize().y) / 4;
}

int Map::m_XRange = 24;
int Map::m_YRange = 9;
float Map::m_FrameTime = 1.0f / 60.0f;

Map::Map(sf::RenderWindow *l_wind) { OnCreate(l_wind); }

Map::~Map() = default;

void Map::OnCreate(sf::RenderWindow *l_wind)
{
  m_selectedItem = nullptr;
  m_wind = l_wind;
  m_places = std::vector<std::vector<int>>(m_XRange, std::vector<int>(m_YRange));
  LoadLogicMap();
  if (m_textures.find("ordinary0") == m_textures.end())
  {
    m_textures["ordinary0"].loadFromFile("res/ordinary0.png");
  }
  sf::Sprite l_sp(m_textures["ordinary0"]);
  l_sp.setOrigin(m_textures["ordinary0"].getSize().x / 2, m_textures["ordinary0"].getSize().y / 2);
  l_sp.setPosition(45, 405);
  auto increments = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 1};
  m_figures.emplace_back(l_sp, m_textures["ordinary0"].getSize(), increments);
}

void Map::Update(sf::RenderWindow *l_wind)
{
  RestartClock();
  // if (m_selected)
  // {
    // m_selected->setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
    // m_selected->setOrigin(m_selected->getSize().x / 2, m_selected->getSize().y / 2);
  // }
  if (m_selectedItem)
  {
    m_selectedItem->GetSprite().setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
    m_selectedItem->GetCircle().setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    if (m_selectedItem)
    {
      for (int i = 0; i < m_XRange; i++)
      {
        for (int j = 0; j < m_YRange; j++)
        {
          if (m_places[i][j] == 0 && checkMouseSelect(m_placesSprite[i][j], m_wind))
          {
            if (m_textures.find("tower0") == m_textures.end())
            {
              m_textures["tower0"].loadFromFile("res/tower0.png");
            }
            sf::Sprite l_sp(m_textures["tower0"]);
            l_sp.setOrigin(m_textures["tower0"].getSize().x / 2, m_textures["tower0"].getSize().y / 2);
            l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
            Tower t(l_sp, m_textures["tower0"].getSize());
            m_placesSprite[i][j].SetTower(t);
            m_places[i][j] = 2;
            // m_selected.reset(nullptr);
            m_selectedItem = nullptr;
          }
        }
      }
    }
  }
  if (m_elapsed >= sf::seconds(m_FrameTime))
  {
    for (Figure &l_fig : m_figures)
    {
      l_fig.Update(sf::seconds(m_FrameTime));
    }
    for (int i = 0; i < m_XRange; ++i)
    {
      for (int j = 0; j < m_YRange; ++j)
      {
        if (m_places[i][j] == 2)
        {
          if (m_placesSprite[i][j].GetTower().GetCalmTime().asSeconds() > 0)
          {
            m_placesSprite[i][j].GetTower().SetCalmTime(m_placesSprite[i][j].GetTower().GetCalmTime() - sf::seconds(m_FrameTime));
            continue;
          }
          for (auto &l_fig : m_figures)
          {
            if (checkInRange(l_fig, m_placesSprite[i][j], 400))
            {
              sf::CircleShape cs(10);
              cs.setFillColor(sf::Color::Yellow);
              cs.setPosition(m_placesSprite[i][j].getPosition());
              cs.setOrigin(cs.getRadius(), cs.getRadius());
              m_bullets.emplace_back(cs, &l_fig);
            }
          }
          m_placesSprite[i][j].GetTower().SetCalmTime(sf::seconds(1));
        }
      }
    }
    auto prev_bullets(m_bullets);
    m_bullets.clear();
    for (auto &l_b : prev_bullets)
    {
      if (checkCollision<>(l_b.first, *(l_b.second)))
      {
        std::vector<Figure> next_figures;
        std::copy_if(m_figures.begin(), m_figures.end(), std::back_inserter(next_figures), [&](Figure &l_fig)
                     {
          if (&l_fig != l_b.second) {return true;}
          l_fig.SetLives(l_fig.GetLives() - 1);
          return l_fig.GetLives() > 0; });
        m_figures = next_figures;
        continue;
      }
      double dx = -l_b.first.getPosition().x + l_b.second->getPosition().x;
      double dy = -l_b.first.getPosition().y + l_b.second->getPosition().y;
      double d = sqrt(dx * dx + dy * dy);
      l_b.first.setPosition(l_b.first.getPosition().x + 160 / d * m_FrameTime * dx, l_b.first.getPosition().y + 160 / d * m_FrameTime * dy);
      m_bullets.emplace_back(l_b);
    }
    m_elapsed -= sf::seconds(m_FrameTime);
  }
}
void Map::Render(sf::RenderWindow *l_wind)
{
  sf::RectangleShape rs(sf::Vector2f(180, 90));
  rs.setPosition(0, 0);
  rs.setFillColor(sf::Color::Magenta);
  l_wind->draw(rs);
  for (int i = 2; i < 3; ++i)
  {
    sf::RectangleShape rs(sf::Vector2f(89, 90));
    rs.setPosition(90 * i + 270, 45);
    rs.setOrigin(rs.getSize().x / 2, rs.getSize().y / 2);
    rs.setFillColor(sf::Color::Blue);
    l_wind->draw(rs);
    if (checkMouseSelect<sf::RectangleShape>(rs, m_wind) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      // m_selected = std::make_unique<sf::RectangleShape>(rs);
      // m_selected->setSize(sf::Vector2f(m_selected->getSize().x / 2, m_selected->getSize().y / 2));
      if (m_textures.find("tower0") == m_textures.end())
      {
        m_textures["tower0"].loadFromFile("res/tower0.png");
      }
      sf::Sprite l_sp(m_textures["tower0"]);
      l_sp.setOrigin(m_textures["tower0"].getSize().x / 2, m_textures["tower0"].getSize().y / 2);
      m_selectedItem = new Tower(l_sp, m_textures["tower0"].getSize());
      sf::CircleShape l_circle(400);
      l_circle.setOrigin(l_circle.getRadius(), l_circle.getRadius());
      l_circle.setFillColor(sf::Color(0, 0, 0, 0));
      l_circle.setOutlineColor(sf::Color::Red);
      l_circle.setOutlineThickness(1.0f);
      m_selectedItem->SetCircle(l_circle);
    }
  }
  for (int i = 0; i < m_XRange; i++)
  {
    for (int j = 0; j < m_YRange; j++)
    {
      m_placesSprite[i][j].Render(l_wind);
    }
  }
  // if (m_selected)
  // {
  //   l_wind->draw(*m_selected);
  // }
  for (const auto &l_b : m_bullets)
  {
    l_wind->draw(l_b.first);
  }
  for (const Figure &l_fig : m_figures)
  {
    l_fig.Render(l_wind);
  }
  if (m_selectedItem)
  {
    m_selectedItem->Render(l_wind);
  }
}

void Map::OnDestroy() {}

void Map::LoadLogicMap()
{
  std::ifstream map;
  map.open("res/map0.cfg");
  if (!map.is_open())
  {
    std::cout << "! Failed loading map.cfg" << std::endl;
  }
  m_placesSprite = std::vector<std::vector<Place>>(m_XRange, std::vector<Place>(m_YRange));
  for (int j = 0; j < m_YRange; ++j)
  {
    std::string line;
    if (!std::getline(map, line))
    {
      std::cout << "Load LogicMap Failed! Y" << std::endl;
      return;
    }
    std::stringstream placeStream(line);
    std::string l_placeType;
    for (int i = 0; i < m_XRange; ++i)
    {
      placeStream >> l_placeType;
      m_places[i][j] = std::stoi(l_placeType);
      if (m_places[i][j] == 0)
      {
        if (m_textures.find("grass0") == m_textures.end())
        {
          m_textures["grass0"].loadFromFile("res/grass0.png");
        }
        sf::Sprite l_sp(m_textures["grass0"]);
        l_sp.setOrigin(m_textures["grass0"].getSize().x / 2, m_textures["grass0"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_placesSprite[i][j] = Place(l_sp, m_textures["grass0"].getSize());
      }
      else if (m_places[i][j] == 1)
      {
        if (m_textures.find("grass1") == m_textures.end())
        {
          m_textures["grass1"].loadFromFile("res/grass1.png");
        }
        sf::Sprite l_sp(m_textures["grass1"]);
        l_sp.setOrigin(m_textures["grass1"].getSize().x / 2, m_textures["grass1"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_placesSprite[i][j] = Place(l_sp, m_textures["grass1"].getSize());
      }
    }
  }
}

sf::Time Map::GetElapsed() { return m_elapsed; }

void Map::RestartClock() { m_elapsed += m_clock.restart(); }
