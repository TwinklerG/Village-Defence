#include "Map.h"

template <class T>
bool checkMouseSelect(T target, sf::RenderWindow *l_wind)
{
  return target.getPosition().x - target.getSize().x / 2 <= sf::Mouse::getPosition(*l_wind).x &&
         target.getPosition().x + target.getSize().x / 2 >= sf::Mouse::getPosition(*l_wind).x &&
         target.getPosition().y - target.getSize().y / 2 <= sf::Mouse::getPosition(*l_wind).y &&
         target.getPosition().y + target.getSize().y / 2 >= sf::Mouse::getPosition(*l_wind).y;
}

bool checkMouseSelectSprite(const sf::Sprite &l_sprite, sf::RenderWindow *l_wind)
{
  return l_sprite.getPosition().x - l_sprite.getTexture()->getSize().x / 2 <= sf::Mouse::getPosition(*l_wind).x &&
         l_sprite.getPosition().x + l_sprite.getTexture()->getSize().x / 2 >= sf::Mouse::getPosition(*l_wind).x &&
         l_sprite.getPosition().y - l_sprite.getTexture()->getSize().y / 2 <= sf::Mouse::getPosition(*l_wind).y &&
         l_sprite.getPosition().y + l_sprite.getTexture()->getSize().y / 2 >= sf::Mouse::getPosition(*l_wind).y;
}

template <class T, class F>
bool checkInRange(T source, F target, double range)
{
  return ((double)source.getPosition().x - target.getPosition().x) * ((double)source.getPosition().x - target.getPosition().x) + ((double)source.getPosition().y - target.getPosition().y) * ((double)source.getPosition().y - target.getPosition().y) <= range * range;
}

template <class F>
bool checkCollision(sf::CircleShape source, F target)
{
  return (source.getPosition().x - target.getPosition().x) * (source.getPosition().x - target.getPosition().x) + (source.getPosition().y - target.getPosition().y) * (source.getPosition().y - target.getPosition().y) <= (source.getRadius() + target.getSize().x) * (source.getRadius() + target.getSize().x) / 8 + (source.getRadius() + target.getSize().y) * (source.getRadius() + target.getSize().y) / 8;
}

int Map::m_XRange = 21;
int Map::m_YRange = 8;

Map::Map(sf::RenderWindow *l_wind) { OnCreate(l_wind); }

Map::~Map() = default;

void Map::OnCreate(sf::RenderWindow *l_wind)
{
  m_lives = 10;
  // rgb(120, 120, 0)
  m_backup = sf::RectangleShape(sf::Vector2f(l_wind->getSize().x, l_wind->getSize().y));
  m_backup.setFillColor(sf::Color(120, 120, 0));
  // if (m_textures.find("board") == m_textures.end())
  // {
  //   m_textures["board"].loadFromFile("res/imgs/board.png");
  // }
  // sf::Sprite l_sp(m_textures["board"]);
  // l_sp.setOrigin(m_textures["board"].getSize().x / 2, m_textures["board"].getSize().y / 2);
  // l_sp.setPosition(sf::Vector2f(45, 45));
  // m_board.reset(new Board(l_sp, m_textures["board"].getSize()));
  m_board.reset(new Board());
  m_textbox.Setup(10, 24, 600, sf::Vector2f(1920, 0));
  m_textbox.Add("Welcome to Villege Defence");
  m_selectedItem = nullptr;
  m_wind = l_wind;
  LoadMap();
}

void Map::Update(sf::RenderWindow *l_wind, const sf::Time &l_time)
{
  if (m_selectedItem)
  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
      m_selectedItem = nullptr;
    }
    else
    {
      m_selectedItem->GetSprite().setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
      m_selectedItem->GetCircle()->setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
    }
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    for (int i = 0; i < m_XRange; i++)
    {
      for (int j = 0; j < m_YRange; j++)
      {
        if (checkMouseSelect(m_places[i][j], m_wind))
        {
          if (m_selectedItem)
          {
            sf::Sprite l_sp(m_selectedItem->GetSprite());
            l_sp.setOrigin(l_sp.getTexture()->getSize().x / 2, l_sp.getTexture()->getSize().y / 2);
            l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
            Tower t(l_sp, m_textures["tower0"].getSize());
            m_places[i][j].SetTower(t);
            m_places[i][j].SetPlaceType(PlaceType::Tower);
            m_board->SetMoney(m_board->GetMoney() - 50);
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
      l_startpoint.SetCalmTime(l_startpoint.GetCalmTime() - l_time);
    }
    else
    {
      if (m_textures.find("ordinary0") == m_textures.end())
      {
        m_textures["ordinary0"].loadFromFile("res/ordinary0.png");
      }
      sf::Sprite l_sp(m_textures["ordinary0"]);
      l_sp.setOrigin(m_textures["ordinary0"].getSize().x / 2, m_textures["ordinary0"].getSize().y / 2);
      l_sp.setPosition(45, 405);
      m_figures.emplace_back(new Figure(l_sp, m_textures["ordinary0"].getSize(), m_roads[rand() % m_roads.size()].second));
      l_startpoint.RestartCalmTime();
    }
  }
  for (Figure *&l_fig : m_figures)
  {
    l_fig->Update(l_time);
  }
  for (int i = 0; i < m_XRange; ++i)
  {
    for (int j = 0; j < m_YRange; ++j)
    {
      if (m_places[i][j].GetPlaceType() == PlaceType::Tower)
      {
        if (m_places[i][j].GetTower().GetCalmTime().asSeconds() > 0)
        {
          m_places[i][j].GetTower().SetCalmTime(m_places[i][j].GetTower().GetCalmTime() - l_time);
          continue;
        }
        for (Figure *l_fig : m_figures)
        {
          if (checkInRange(*l_fig, m_places[i][j], 400))
          {
            int cnt = 0;
            for (auto &l_b : m_bullets)
            {
              if (l_b.GetTargetFigure() == l_fig)
              {
                ++cnt;
              }
            }
            if (cnt >= l_fig->GetLives())
            {
              continue;
            }
            sf::CircleShape cs(10);
            cs.setFillColor(sf::Color::Yellow);
            cs.setPosition(m_places[i][j].getPosition());
            cs.setOrigin(cs.getRadius(), cs.getRadius());
            m_bullets.push_back(Bullet(cs, l_fig, 360));
            break;
          }
        }
        m_places[i][j].GetTower().SetCalmTime(sf::seconds(1));
      }
    }
  }
  std::vector<Bullet> next_bullets{};
  for (auto &l_b : m_bullets)
  {
    if (checkCollision(l_b.GetCircle(), *l_b.GetTargetFigure()))
    {
      std::vector<Figure *> next_figures;
      for (Figure *&l_fig : m_figures)
      {
        if (l_fig != l_b.GetTargetFigure())
        {
          next_figures.emplace_back(l_fig);
          continue;
        }
        l_fig->SetLives(l_fig->GetLives() - 1);
        if (l_fig->GetLives() > 0)
        {
          next_figures.emplace_back(l_fig);
          continue;
        }
        // TODO: solve memory leak
        delete l_fig;
        l_fig = nullptr; // impact other bullets
      }
      m_figures = next_figures;
      continue;
    }
    double dx = -l_b.GetCircle().getPosition().x + l_b.GetTargetFigure()->getPosition().x;
    double dy = -l_b.GetCircle().getPosition().y + l_b.GetTargetFigure()->getPosition().y;
    double d = sqrt(dx * dx + dy * dy);
    l_b.GetCircle().setPosition(l_b.GetCircle().getPosition().x + l_b.GetSpeed() / d * l_time.asSeconds() * dx, l_b.GetCircle().getPosition().y + l_b.GetSpeed() / d * l_time.asSeconds() * dy);
    next_bullets.emplace_back(l_b);
  }
  m_bullets = next_bullets;
  if (m_board->GetCalmTime().asSeconds() > 0)
  {
    m_board->SetCalmTime(m_board->GetCalmTime() - l_time);
  }
  else
  {
    m_board->SetMoney(m_board->GetMoney() + 50);
    m_board->SetCalmTime(sf::seconds(3));
  }
  std::vector<Figure *> next_figures{};
  for (const auto &l_fig : m_figures)
  {
    for (const auto &l_ep : m_endPoints)
    {
      if (checkInRange(*l_fig, l_ep, l_fig->getSize().x / 2 + l_ep.getSize().x / 2))
      {
        --m_lives;
        m_textbox.Add("Villege has been invaded. You have " + std::to_string(m_lives) + " lives currently!!!");
      }
      else
      {
        next_figures.emplace_back(l_fig);
      }
    }
  }
  m_figures = next_figures;
  for (const auto &l_choice : m_choices)
  {
    if (checkMouseSelectSprite(l_choice.first, m_wind) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_board->GetMoney() >= 50)
    {
      sf::Sprite l_sp(l_choice.first);
      l_sp.setOrigin(l_choice.first.getTexture()->getSize().x / 2, l_choice.first.getTexture()->getSize().y / 2);
      l_sp.setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
      m_selectedItem = new Tower(l_sp, l_sp.getTexture()->getSize());
      sf::CircleShape l_circle(400);
      l_circle.setOrigin(l_circle.getRadius(), l_circle.getRadius());
      l_circle.setFillColor(sf::Color(0, 0, 0, 0));
      l_circle.setOutlineColor(sf::Color::Red);
      l_circle.setOutlineThickness(1.0f);
      l_circle.setPosition(sf::Mouse::getPosition(*l_wind).x, sf::Mouse::getPosition(*l_wind).y);
      m_selectedItem->SetCircle(&l_circle);
    }
  }
}
void Map::Render(sf::RenderWindow *l_wind)
{
  m_wind->draw(m_backup);
  for (const auto &l_choice : m_choices)
  {
    l_wind->draw(l_choice.first);
    l_wind->draw(l_choice.second);
  }
  for (int i = 0; i < m_XRange; i++)
  {
    for (int j = 0; j < m_YRange; j++)
    {
      if (m_places[i][j].GetPlaceType() == PlaceType::End)
      {
        for (const auto &l_ep : m_endPoints)
        {
          if (l_ep.GetCordinate() == std::make_pair(i, j))
          {
            l_ep.Render(l_wind);
            break;
          }
        }
        continue;
      }
      m_places[i][j].Render(l_wind);
    }
  }
  for (auto &l_b : m_bullets)
  {
    l_wind->draw(l_b.GetCircle());
  }
  for (Figure *l_fig : m_figures)
  {
    l_fig->Render(l_wind);
  }
  if (m_selectedItem)
  {
    m_selectedItem->Render(l_wind);
  }
  m_textbox.Render(*l_wind);
  m_board->Render(l_wind);
}

void Map::OnDestroy() {}

void Map::LoadMap()
{
  std::ifstream in;
  in.open("res/maps/map0.cfg");
  if (!in.is_open())
  { // assert(false);
  }

  int choiceSum;
  in >> choiceSum;
  m_choices = std::vector<std::pair<sf::Sprite, sf::Text>>(choiceSum);
  for (int i = 0; i < choiceSum; ++i)
  {
    int type, cost;
    in >> type >> cost;
    if (m_textures.find("tower" + std::to_string(type)) == m_textures.end())
    {
      m_textures["tower" + std::to_string(type)].loadFromFile("res/imgs/tower/tower" + std::to_string(type) + ".png");
    }
    m_choices[i].first.setTexture(m_textures["tower" + std::to_string(type)]);
    m_choices[i].first.setOrigin(m_choices[i].first.getTexture()->getSize().x / 2, m_choices[i].first.getTexture()->getSize().y / 2);
    m_choices[i].first.setPosition(m_choices[i].first.getTexture()->getSize().x / 2 + 90 * (i + 1), m_choices[i].first.getTexture()->getSize().y / 2);
    if (m_fonts.find("arial") == m_fonts.end())
    {
      m_fonts["arial"].loadFromFile("res/fonts/arial.ttf");
    }
    m_choices[i].second.setFont(m_fonts["arial"]);
    m_choices[i].second.setString(std::to_string(cost));
    m_choices[i].second.setCharacterSize(30);
    m_choices[i].second.setOrigin(m_choices[i].second.getLocalBounds().width / 2, m_choices[i].second.getLocalBounds().height / 2);
    m_choices[i].second.setPosition(m_choices[i].first.getPosition() + sf::Vector2f(0, m_choices[i].first.getTexture()->getSize().y / 2));
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
        if (m_textures.find("road") == m_textures.end())
        {
          m_textures["road"].loadFromFile("res/imgs/road.png");
        }
        sf::Sprite l_sp(m_textures["road"]);
        l_sp.setOrigin(m_textures["road"].getSize().x / 2, m_textures["road"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_places[i][j] = Place(l_sp, m_textures["road"].getSize(), PlaceType::Road);
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
        m_startPoints.emplace_back(StartPoint(l_sp, m_textures["startpoint"].getSize(), std::make_pair(i, j), sf::seconds(1)));
      }
      else if (l_placeType == 4)
      {
        if (m_textures.find("endPoint") == m_textures.end())
        {
          m_textures["endPoint"].loadFromFile("res/endPoint.png");
        }
        sf::Sprite l_esp(m_textures["endPoint"]);
        l_esp.setOrigin(m_textures["endPoint"].getSize().x / 2, m_textures["endPoint"].getSize().y / 2);
        l_esp.setPosition(45 + 90 * i, 405 + 90 * j);
        if (m_textures.find("grass2") == m_textures.end())
        {
          m_textures["grass2"].loadFromFile("res/grass2.png");
        }
        sf::Sprite l_sp(m_textures["grass2"]);
        l_sp.setOrigin(m_textures["grass2"].getSize().x / 2, m_textures["grass2"].getSize().y / 2);
        l_sp.setPosition(45 + 90 * i, 405 + 90 * j);
        m_places[i][j] = Place(l_sp, m_textures["grass2"].getSize(), PlaceType::End);
        m_endPoints.emplace_back(EndPoint(l_sp, m_textures["grass2"].getSize(), l_esp, std::make_pair(i, j)));
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
        // assert(false);
        break;
      }
      dfs(ti, tj, l_road);
      l_road.pop_back();
    }
    st.erase(y * Map::m_XRange + x);
  };
  std::vector<Direction> l_road{};
  for (const auto &l_sp : m_startPoints)
  {
    dfs(l_sp.GetCordinate().first, l_sp.GetCordinate().second, l_road);
  }
}

int Map::GetLives() const { return m_lives; }