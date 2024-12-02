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
  m_wind = l_wind;
  m_places = std::vector<std::vector<int>>(m_XRange, std::vector<int>(m_YRange));
  LoadLogicMap();
  auto fig = sf::RectangleShape(sf::Vector2f(60, 60));
  fig.setFillColor(sf::Color::Blue);
  fig.setOrigin(fig.getSize().x / 2, fig.getSize().y / 2);
  fig.setPosition(45, 405);
  auto ptr = std::make_shared<sf::RectangleShape>(fig);
  m_figures.emplace_back(ptr, 0);
  std::vector<int> increments{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 2, 2, 1, 1, 2, 2, 2, 1};
  m_figureIncrementMap.emplace(ptr, increments);
}

void Map::Update(sf::RenderWindow *l_wind)
{
  RestartClock();
  if (m_selected)
  {
    m_selected->setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
    m_selected->setOrigin(m_selected->getSize().x / 2, m_selected->getSize().y / 2);
  }
  for (int i = 0; i < m_XRange; ++i)
  {
    for (int j = 0; j < m_YRange; ++j)
    {
      if (m_places[i][j] == 2)
      {
        for (const auto &l_fig : m_figures)
        {
          if (checkInRange(*l_fig.first, m_placesSprite[i][j], 400))
          {
            // std::cout << "In Range\n";
            sf::CircleShape cs(10);
            cs.setFillColor(sf::Color::Yellow);
            cs.setPosition(m_placesSprite[i][j].getPosition());
            cs.setOrigin(cs.getRadius(), cs.getRadius());
            m_bullets.emplace_back(cs, l_fig.first);
          }
        }
      }
    }
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    if (m_selected)
    {
      // m_figures.emplace_back(*m_selected);
      for (int i = 0; i < m_XRange; i++)
      {
        for (int j = 0; j < m_YRange; j++)
        {
          if (m_places[i][j] == 0 && checkMouseSelect<sf::RectangleShape>(m_placesSprite[i][j], m_wind))
          {
            std::cout << "Selected " << i << " " << j << std::endl;
            m_placesSprite[i][j] = sf::RectangleShape(sf::Vector2f(10, 80));
            m_placesSprite[i][j].setOrigin(m_placesSprite[i][j].getSize().x / 2, m_placesSprite[i][j].getSize().y / 2);
            m_placesSprite[i][j].setFillColor(sf::Color::Red);
            m_placesSprite[i][j].setPosition(45 + 90 * i, 405 + 90 * j);
            m_places[i][j] = 2;
            m_selected.reset(nullptr);
          }
        }
      }
    }
  }
  if (m_elapsed >= sf::seconds(m_FrameTime))
  {
    auto prev_bullets = m_bullets;
    m_bullets = {};
    for (auto &l_b : prev_bullets)
    {
      if (checkCollision<sf::RectangleShape>(l_b.first, *(l_b.second)))
      {
        // std::cout << "Collide\n";
        for (int i = 0; i < m_figures.size(); ++i)
        {
          if (m_figures[i].first == l_b.second)
          {
            m_figures.erase(m_figures.begin() + i);
            m_figureIncrementMap.erase(l_b.second);
            break;
          }
        }
        continue;
      }
      double dx = -l_b.first.getPosition().x + l_b.second->getPosition().x;
      double dy = -l_b.first.getPosition().y + l_b.second->getPosition().y;
      double d = sqrt(dx * dx + dy * dy);
      l_b.first.setPosition(l_b.first.getPosition().x + 160 / d * m_FrameTime * dx, l_b.first.getPosition().y + 160 / d * m_FrameTime * dy);
      m_bullets.emplace_back(l_b);
    }
    for (auto &l_fig : m_figures)
    {
      if (l_fig.second / 90 >= m_figureIncrementMap[l_fig.first].size())
      {
        continue;
      }
      switch (m_figureIncrementMap[l_fig.first][l_fig.second / 90])
      {
      case 0:
        l_fig.first->setPosition(l_fig.first->getPosition().x, l_fig.first->getPosition().y - m_elapsed.asSeconds() * 90);
        break;
      case 1:
        l_fig.first->setPosition(l_fig.first->getPosition().x + m_elapsed.asSeconds() * 90, l_fig.first->getPosition().y);
        break;
      case 2:
        l_fig.first->setPosition(l_fig.first->getPosition().x, l_fig.first->getPosition().y + m_elapsed.asSeconds() * 90);
        break;
      case 3:
        l_fig.first->setPosition(l_fig.first->getPosition().x - m_elapsed.asSeconds() * 90, l_fig.first->getPosition().y);
        break;
      default:
        throw "Undefined Direction Code";
        break;
      }
      l_fig.second += m_elapsed.asSeconds() * 90;
      // std::cout << l_fig.second << std::endl;
      m_elapsed -= sf::seconds(m_FrameTime);
    }
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
      m_selected = std::make_unique<sf::RectangleShape>(rs);
      m_selected->setSize(sf::Vector2f(m_selected->getSize().x / 2, m_selected->getSize().y / 2));
    }
  }
  for (int i = 0; i < m_XRange; i++)
  {
    for (int j = 0; j < m_YRange; j++)
    {
      l_wind->draw(m_placesSprite[i][j]);
    }
  }
  for (auto &l_fig : m_figures)
  {
    l_wind->draw(*(l_fig.first));
  }
  if (m_selected)
  {
    l_wind->draw(*m_selected);
  }
  for (const auto &l_b : m_bullets)
  {
    l_wind->draw(l_b.first);
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
  m_placesSprite = std::vector<std::vector<sf::RectangleShape>>(m_XRange, std::vector<sf::RectangleShape>(m_YRange));
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
      sf::RectangleShape rs(sf::Vector2f(89, 89));
      rs.setOrigin(rs.getSize().x / 2, rs.getSize().y / 2);
      rs.setPosition(45 + 90 * i, 405 + 90 * j);
      rs.setFillColor(m_places[i][j] == 1 ? sf::Color::Green : sf::Color::White);
      m_placesSprite[i][j] = rs;
    }
  }
}

sf::Time Map::GetElapsed() { return m_elapsed; }

void Map::RestartClock() { m_elapsed += m_clock.restart(); }