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

int Map::m_XRange = 9;
int Map::m_YRange = 6;
float Map::m_FrameTime = 1.0f / 60.0f;

Map::Map(sf::RenderWindow *l_wind) { OnCreate(l_wind); }

Map::~Map() = default;

void Map::OnCreate(sf::RenderWindow *l_wind)
{
  m_selectedItem = nullptr;
  m_wind = l_wind;
  LoadMap();
  if (m_textures.find("ordinary0") == m_textures.end())
  {
    m_textures["ordinary0"].loadFromFile("res/ordinary0.png");
  }
  // sf::Sprite l_sp(m_textures["ordinary0"]);
  // l_sp.setOrigin(m_textures["ordinary0"].getSize().x / 2, m_textures["ordinary0"].getSize().y / 2);
  // l_sp.setPosition(45, 405);
  // auto increments = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 1};
  // m_figures.emplace_back(l_sp, m_textures["ordinary0"].getSize(), increments);
}

void Map::Update(sf::RenderWindow *l_wind)
{
  RestartClock();
  if (m_elapsed >= sf::seconds(m_FrameTime))
  {
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
            if (checkMouseSelect(m_places[i][j], m_wind))
            {
              if (m_textures.find("tower0") == m_textures.end())
              {
                m_textures["tower0"].loadFromFile("res/tower0.png");
              }
              sf::Sprite l_sp(m_textures["tower0"]);
              l_sp.setOrigin(m_textures["tower0"].getSize().x / 2, m_textures["tower0"].getSize().y / 2);
              l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
              Tower t(l_sp, m_textures["tower0"].getSize());
              m_places[i][j].SetTower(t);
              m_places[i][j].SetPlaceType(PlaceType::Tower);
              m_selectedItem = nullptr;
            }
          }
        }
      }
    }
    for (StartPoint &l_startpoint : m_startPoints)
    {
      if (l_startpoint.GetCalmTime().asSeconds() > 0)
      {
        l_startpoint.SetCalmTime(l_startpoint.GetCalmTime() - sf::seconds(m_FrameTime));
      }
      else
      {
        sf::Sprite l_sp(m_textures["ordinary0"]);
        l_sp.setOrigin(m_textures["ordinary0"].getSize().x / 2, m_textures["ordinary0"].getSize().y / 2);
        l_sp.setPosition(45, 405);
        m_figures.emplace_back(new Figure(l_sp, m_textures["ordinary0"].getSize(), m_roads[rand() % m_roads.size()].second));
        l_startpoint.RestartCalmTime();
      }
    }
    for (Figure *&l_fig : m_figures)
    {
      l_fig->Update(sf::seconds(m_FrameTime));
    }
    for (int i = 0; i < m_XRange; ++i)
    {
      for (int j = 0; j < m_YRange; ++j)
      {
        if (m_places[i][j].GetPlaceType() == PlaceType::Tower)
        {
          if (m_places[i][j].GetTower().GetCalmTime().asSeconds() > 0)
          {
            m_places[i][j].GetTower().SetCalmTime(m_places[i][j].GetTower().GetCalmTime() - sf::seconds(m_FrameTime));
            continue;
          }
          for (Figure *l_fig : m_figures)
          {
            if (checkInRange(*l_fig, m_places[i][j], 400))
            {
              sf::CircleShape cs(10);
              cs.setFillColor(sf::Color::Yellow);
              cs.setPosition(m_places[i][j].getPosition());
              cs.setOrigin(cs.getRadius(), cs.getRadius());
              m_bullets.emplace_back(cs, l_fig);
              break;
            }
          }
          m_places[i][j].GetTower().SetCalmTime(sf::seconds(1));
        }
      }
    }
    auto prev_bullets(m_bullets);
    m_bullets.clear();
    for (auto &l_b : prev_bullets)
    {
      if (checkCollision(l_b.first, *(l_b.second)))
      {
        std::vector<Figure *> next_figures;
        std::copy_if(m_figures.begin(), m_figures.end(), std::back_inserter(next_figures), [&](Figure *&l_fig)
                     {
          if (l_fig != l_b.second) {return true;}
          l_fig->SetLives(l_fig->GetLives() - 1);
          return l_fig->GetLives() > 0; });
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
      m_places[i][j].Render(l_wind);
    }
  }
  for (const auto &l_b : m_bullets)
  {
    l_wind->draw(l_b.first);
  }
  for (Figure *l_fig : m_figures)
  {
    l_fig->Render(l_wind);
  }
  if (m_selectedItem)
  {
    m_selectedItem->Render(l_wind);
  }
}

void Map::OnDestroy() {}

void Map::LoadMap()
{
  std::ifstream in;
  in.open("res/map0.cfg");
  if (!in.is_open())
  {
    assert(false);
  }
  m_places = std::vector<std::vector<Place>>(m_XRange, std::vector<Place>(m_YRange));
  auto l_placesType = std::vector<std::vector<int>>(m_XRange, std::vector<int>(m_YRange));
  int l_placeType;
  for (int j = 0; j < m_YRange; ++j)
  {
    for (int i = 0; i < m_XRange; ++i)
    {
      in >> l_placeType;
      l_placesType[i][j] = l_placeType;
      if (l_placeType == 0)
      {
        if (m_textures.find("grass0") == m_textures.end())
        {
          m_textures["grass0"].loadFromFile("res/grass0.png");
        }
        sf::Sprite l_sp(m_textures["grass0"]);
        l_sp.setOrigin(m_textures["grass0"].getSize().x / 2, m_textures["grass0"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_places[i][j] = Place(l_sp, m_textures["grass0"].getSize(), PlaceType::Land);
      }
      else if (l_placeType == 1)
      {
        if (m_textures.find("grass1") == m_textures.end())
        {
          m_textures["grass1"].loadFromFile("res/grass1.png");
        }
        sf::Sprite l_sp(m_textures["grass1"]);
        l_sp.setOrigin(m_textures["grass1"].getSize().x / 2, m_textures["grass1"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_places[i][j] = Place(l_sp, m_textures["grass1"].getSize(), PlaceType::Road);
      }
      else if (l_placeType == 3)
      {
        if (m_textures.find("startPoint") == m_textures.end())
        {
          m_textures["startPoint"].loadFromFile("res/startPoint.png");
        }
        sf::Sprite l_sp(m_textures["startPoint"]);
        l_sp.setOrigin(m_textures["startPoint"].getSize().x / 2, m_textures["startPoint"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_places[i][j] = Place(l_sp, m_textures["startPoint"].getSize(), PlaceType::Road);
        m_startPointss.emplace_back(i, j);
        m_startPoints.emplace_back(StartPoint(l_sp, m_textures["startpoint"].getSize(), std::make_pair(i, j), sf::seconds(1)));
      }
      else if (l_placeType == 4)
      {
        if (m_textures.find("endPoint") == m_textures.end())
        {
          m_textures["endPoint"].loadFromFile("res/endPoint.png");
        }
        sf::Sprite l_sp(m_textures["endPoint"]);
        l_sp.setOrigin(m_textures["endPoint"].getSize().x / 2, m_textures["endPoint"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_places[i][j] = Place(l_sp, m_textures["endPoint"].getSize(), PlaceType::End);
      }
    }
  }
  in.close();
  std::unordered_set<int> st;
  std::function<void(int, int, std::vector<Direction> &)> dfs = [&](int x, int y, std::vector<Direction> &l_road)
  {
    if (Map::m_places[x][y].GetPlaceType() == PlaceType::End)
    {
      int flag = 1;
      std::transform(Map::m_roads.begin(), Map::m_roads.end(), Map::m_roads.begin(), [x, y, &l_road, &flag](const std::pair<std::pair<int, int>, std::vector<Direction>> &l_p)
                     {if (l_p.first.first == x && l_p.first.second == y) {flag = 0;
          return l_road.size() < l_p.second.size() ? std::make_pair(l_p.first, l_road) : l_p;
        }return l_p; });
      if (flag == 1)
      {
        Map::m_roads.push_back({{x, y}, l_road});
      }
      return;
    }
    if (st.count(y * Map::m_XRange + x))
    {
      return;
    }
    st.insert(y * Map::m_XRange + x);
    int vect[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
    for (int i = 0; i < 4; ++i)
    {
      int ti = x + vect[i][0], tj = y + vect[i][1];
      if (ti < 0 || ti >= Map::m_XRange || tj < 0 || tj >= Map::m_YRange || st.count(tj * Map::m_XRange + ti) || (Map::m_places[ti][tj].GetPlaceType() != PlaceType::Road && Map::m_places[ti][tj].GetPlaceType() != PlaceType::End))
      {
        continue;
      }
      switch (i)
      {
      case 0:
        l_road.emplace_back(Direction::Left);
        break;
      case 1:
        l_road.emplace_back(Direction::Down);
        break;
      case 2:
        l_road.emplace_back(Direction::Up);
        break;
      case 3:
        l_road.emplace_back(Direction::Right);
        break;
      default:
        assert(false);
        break;
      }
      dfs(ti, tj, l_road);
      l_road.pop_back();
    }
    st.erase(y * Map::m_XRange + x);
  };
  std::vector<Direction> l_road{};
  for (const auto &l_sp : m_startPointss)
  {
    dfs(l_sp.first, l_sp.second, l_road);
  }
}

sf::Time Map::GetElapsed() { return m_elapsed; }

void Map::RestartClock() { m_elapsed += m_clock.restart(); }
