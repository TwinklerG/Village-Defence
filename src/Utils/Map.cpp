#include "Map.h"
#include <cassert>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <iostream>
#include <numeric>

template<class T>
bool checkMouseSelect(const T &target, sf::RenderWindow *l_wind) {
  return target.getPosition().x - target.getSize().x / 2.0 <= sf::Mouse::getPosition(*l_wind).x &&
         target.getPosition().x + target.getSize().x / 2.0 >= sf::Mouse::getPosition(*l_wind).x &&
         target.getPosition().y - target.getSize().y / 2.0 <= sf::Mouse::getPosition(*l_wind).y &&
         target.getPosition().y + target.getSize().y / 2.0 >= sf::Mouse::getPosition(*l_wind).y;
}

bool checkMouseSelectSprite(const sf::Sprite &l_sprite, const sf::RenderWindow *l_wind) {
  return l_sprite.getPosition().x - l_sprite.getTexture()->getSize().x / 2.0 <= sf::Mouse::getPosition(*l_wind).x &&
         l_sprite.getPosition().x + l_sprite.getTexture()->getSize().x / 2.0 >= sf::Mouse::getPosition(*l_wind).x &&
         l_sprite.getPosition().y - l_sprite.getTexture()->getSize().y / 2.0 <= sf::Mouse::getPosition(*l_wind).y &&
         l_sprite.getPosition().y + l_sprite.getTexture()->getSize().y / 2.0 >= sf::Mouse::getPosition(*l_wind).y;
}

template<class T, class F>
bool checkInRange(const T &source, const F &target, const double range) {
  return (source.getPosition().x - target.getPosition().x) * (source.getPosition().x - target.getPosition().x) + (
           source.getPosition().y - target.getPosition().y) * (source.getPosition().y - target.getPosition().y) <= range
         * range;
}

template<class F>
bool checkCollision(const sf::CircleShape &source, const F &target) {
  return (source.getPosition().x - target.getPosition().x) * (source.getPosition().x - target.getPosition().x) + (
           source.getPosition().y - target.getPosition().y) * (source.getPosition().y - target.getPosition().y) <= (
           source.getRadius() + target.getSize().x) * (source.getRadius() + target.getSize().x) / 8 + (
           source.getRadius() + target.getSize().y) * (source.getRadius() + target.getSize().y) / 8;
}

int Map::m_XRange = 21;
int Map::m_YRange = 8;

Map::Map(sf::RenderWindow *l_wind, const int l_level) : m_level(l_level), m_isWin(false) { OnCreate(l_wind); }

Map::~Map() = default;

void Map::OnCreate(sf::RenderWindow *l_wind) {
  m_lives = 10;
  // rgb(120, 120, 0)
  m_backup = sf::RectangleShape(sf::Vector2f(static_cast<float>(l_wind->getSize().x),
                                             static_cast<float>(l_wind->getSize().y)));
  m_backup.setFillColor(sf::Color(120, 120, 0));
  m_board = std::make_unique<Board>();
  m_textbox.Setup(10, 24, 600, sf::Vector2f(1920, 0));
  m_textbox.Add("Welcome to Village Defence");
  m_selected.m_tower = nullptr;
  m_wind = l_wind;
  LoadMap();
  LoadMaps();
}

void Map::Update(sf::RenderWindow *l_wind, const sf::Time &l_time) {
  if (std::accumulate(m_startPoints.begin(), m_startPoints.end(), 0, [](int accum, const StartPoint &l_sp) {
    return accum + l_sp.GetLeftTurns();
  }) == 0 && m_figures.empty()) {
    m_isWin = true;
  }
  if (m_selected.m_tower) {
    if (m_selected.m_selectType == SelectType::Choice) {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        m_selected.m_tower = nullptr;
      } else {
        m_selected.m_tower->GetSprite().setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                                                    static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
        m_selected.m_tower->GetCircle()->setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                                                     static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
      }
    } else {
      m_selected.m_tower->SetCircle(nullptr);
    }
  } else if (m_selected.m_selectType == SelectType::Existence && m_places[m_selected.x][m_selected.y].GetPlaceType() ==
             PlaceType::Tower) {
    m_places[m_selected.x][m_selected.y].GetTower().SetCircle(nullptr);
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    for (int i = 0; i < m_XRange; i++) {
      for (int j = 0; j < m_YRange; j++) {
        if (checkMouseSelect(m_places[i][j], m_wind)) {
          if (m_selected.m_tower && m_selected.m_selectType == SelectType::Choice && m_places[i][j].GetPlaceType() ==
              PlaceType::Land) {
            Tower t(*m_selected.m_tower);
            t.GetSprite().setPosition(static_cast<float>(45 + 90 * i), static_cast<float>(405 + 90 * j));
            t.SetCircle(nullptr);
            m_places[i][j].SetTower(t);
            m_places[i][j].SetPlaceType(PlaceType::Tower);
            m_board->SetMoney(m_board->GetMoney() - t.GetCost());
            m_selected.m_tower = nullptr;
          } else if (m_places[i][j].GetPlaceType() == PlaceType::Tower && m_selected.m_tower == nullptr) {
            m_selected.m_selectType = SelectType::Existence;
            m_selected.x = i;
            m_selected.y = j;
            Tower &l_tower = m_places[i][j].GetTower();
            sf::CircleShape l_circle(static_cast<float>(l_tower.GetRange()));
            l_circle.setOrigin(l_circle.getRadius(), l_circle.getRadius());
            l_circle.setFillColor(sf::Color(0, 0, 0, 0));
            l_circle.setOutlineColor(sf::Color::Red);
            l_circle.setOutlineThickness(1.0f);
            l_circle.setPosition(static_cast<float>(45 + 90 * i), static_cast<float>(405 + 90 * j));
            m_places[i][j].GetTower().SetCircle(std::make_shared<sf::CircleShape>(l_circle));
          }
        }
      }
    }
  }
  for (StartPoint &l_startPoint: m_startPoints) {
    if (auto l_fig = l_startPoint.Update(l_time)) {
      m_figures.emplace_back(l_fig);
    }
  }
  for (auto &l_fig: m_figures) {
    l_fig->Update(l_time);
  }
  for (int i = 0; i < m_XRange; ++i) {
    for (int j = 0; j < m_YRange; ++j) {
      if (m_places[i][j].GetPlaceType() == PlaceType::Tower) {
        if (m_places[i][j].GetTower().GetCalmTime().asSeconds() > 0) {
          m_places[i][j].GetTower().SetCalmTime(m_places[i][j].GetTower().GetCalmTime() - l_time);
          continue;
        }
        for (const auto &l_fig: m_figures) {
          if (checkInRange(*l_fig, m_places[i][j], m_places[i][j].GetTower().GetRange())) {
            int cnt = 0;
            for (auto &l_b: m_bullets) {
              if (l_b.GetTargetFigure() == l_fig) {
                cnt += l_b.GetAtk();
              }
            }
            if (cnt >= l_fig->GetLives()) {
              continue;
            }
            const Tower &l_tower = m_places[i][j].GetTower();
            sf::CircleShape cs(static_cast<float>(l_tower.GetBulletRadius()));
            cs.setFillColor(l_tower.GetBulletColor());
            cs.setPosition(m_places[i][j].getPosition());
            cs.setOrigin(cs.getRadius(), cs.getRadius());
            m_bullets.emplace_back(cs, l_fig, static_cast<int>(m_places[i][j].GetTower().GetBulletSpeed()),
                                   m_places[i][j].GetTower().GetAttackPoint());
            break;
          }
        }
        m_places[i][j].GetTower().SetCalmTime(sf::seconds(1));
      }
    }
  }
  std::vector<Bullet> next_bullets{};
  for (auto l_b: m_bullets) {
    if (checkCollision(l_b.GetCircle(), *l_b.GetTargetFigure())) {
      std::vector<std::shared_ptr<Figure> > next_figures;
      for (const auto &l_fig: m_figures) {
        if (l_fig != l_b.GetTargetFigure()) {
          next_figures.emplace_back(l_fig);
          continue;
        }
        l_fig->SetLives(l_fig->GetLives() - l_b.GetAtk());
        if (l_fig->GetLives() > 0) {
          next_figures.emplace_back(l_fig);
          continue;
        }
        m_board->SetMoney(m_board->GetMoney() + l_fig->GetReward());
      }
      m_figures = next_figures;
      continue;
    }
    double dx = -l_b.GetCircle().getPosition().x + l_b.GetTargetFigure()->getPosition().x;
    double dy = -l_b.GetCircle().getPosition().y + l_b.GetTargetFigure()->getPosition().y;
    double d = sqrt(dx * dx + dy * dy);
    l_b.GetCircle().setPosition(
      static_cast<float>(l_b.GetCircle().getPosition().x + l_b.GetSpeed() / d * l_time.asSeconds() * dx),
      static_cast<float>(l_b.GetCircle().getPosition().y + l_b.GetSpeed() / d * l_time.asSeconds() * dy));
    next_bullets.emplace_back(l_b);
  }
  m_bullets = next_bullets;
  std::vector<std::shared_ptr<Figure> > next_figures{};
  for (const auto &l_fig: m_figures) {
    for (const auto &l_ep: m_endPoints) {
      if (checkInRange(*l_fig, l_ep, l_fig->getSize().x / 2.0 + l_ep.getSize().x / 2.0)) {
        --m_lives;
        m_textbox.Add("Village has been invaded. You have only " + std::to_string(m_lives) + " lives!!!");
        auto itr = std::find(next_figures.begin(), next_figures.end(), l_fig);
        if (itr != next_figures.end()) {
          next_figures.erase(itr);
        }
        break;
      }
      if (std::find(next_figures.begin(), next_figures.end(), l_fig) == next_figures.end()) {
        next_figures.emplace_back(l_fig);
      }
    }
  }
  m_figures = next_figures;
  for (const auto &l_choice: m_choices) {
    if (checkMouseSelectSprite(l_choice.first.first, m_wind) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_board->
        GetMoney() >= l_choice.second.m_cost) {
      if (m_selected.m_selectType == SelectType::Existence) {
        if (m_selected.m_tower) {
          m_selected.m_tower->SetCircle(nullptr);
        }
      }
      m_selected.m_tower = std::make_shared<Tower>(l_choice.first.first,
                                                   l_choice.first.first.getTexture()->getSize(),
                                                   sf::seconds(static_cast<float>(l_choice.second.m_calmTime)),
                                                   l_choice.second.m_attackPoint,
                                                   static_cast<float>(l_choice.second.m_speed),
                                                   l_choice.second.m_range,
                                                   l_choice.second.m_cost,
                                                   l_choice.second.m_red,
                                                   l_choice.second.m_green,
                                                   l_choice.second.m_blue,
                                                   l_choice.second.m_bulletRadius);
      m_selected.m_tower->GetSprite().setOrigin(
        static_cast<float>(l_choice.first.first.getTexture()->getSize().x / 2.0),
        static_cast<float>(l_choice.first.first.getTexture()->getSize().y / 2.0));
      m_selected.m_tower->GetSprite().setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                                                  static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
      sf::CircleShape l_circle(static_cast<float>(l_choice.second.m_range));
      l_circle.setOrigin(l_circle.getRadius(), l_circle.getRadius());
      l_circle.setFillColor(sf::Color(0, 0, 0, 0));
      l_circle.setOutlineColor(sf::Color::Red);
      l_circle.setOutlineThickness(1.0f);
      l_circle.setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                           static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
      m_selected.m_tower->SetCircle(std::make_shared<sf::CircleShape>(l_circle));
      m_selected.m_selectType = SelectType::Choice;
    }
  }
}

void Map::Render(sf::RenderWindow *l_wind) {
  m_wind->draw(m_backup);
  for (const auto &[fst, snd]: m_choices) {
    l_wind->draw(fst.first);
    l_wind->draw(fst.second);
  }
  for (int i = 0; i < m_XRange; i++) {
    for (int j = 0; j < m_YRange; j++) {
      m_places[i][j].Render(l_wind);
    }
  }
  for (const auto &l_ep: m_endPoints) {
    l_ep.Render(l_wind);
  }
  for (auto &l_b: m_bullets) {
    l_wind->draw(l_b.GetCircle());
  }
  for (auto &l_fig: m_figures) {
    l_fig->Render(l_wind);
  }
  if (m_selected.m_tower) {
    m_selected.m_tower->Render(l_wind);
  }
  m_textbox.Render(*l_wind);
  m_board->Render(l_wind);
}

void Map::LoadMaps() {
  std::vector<TowerInfo> l_towerInfos;
  std::ifstream inTower;
  inTower.open("res/config/tower.cfg");
  if (!inTower.is_open()) {
    assert(false);
  }
  // Load Tower Infos
  int towerSum;
  inTower >> towerSum;
  for (int i = 0; i < towerSum; ++i) {
    int tag, cost, atk, range, red, green, blue;
    double calmTime, speed, radius;
    inTower >> tag >> cost >> atk >> range >> calmTime >> speed >> red >> green >> blue >> radius;
    l_towerInfos.push_back({cost, atk, range, calmTime, speed, red, green, blue, radius});
  }
  inTower.close();
  std::ifstream in;
  in.open("res/config/map" + std::to_string(m_level) + ".cfg");
  if (!in.is_open()) {
    assert(false);
  }
  // Load Choices
  int choiceSum;
  in >> choiceSum;
  m_choices = std::vector<std::pair<std::pair<sf::Sprite, sf::Text>, TowerInfo> >(choiceSum);
  for (int i = 0; i < choiceSum; ++i) {
    int tag;
    in >> tag;
    if (m_textures.find("tower" + std::to_string(tag)) == m_textures.end()) {
      m_textures["tower" + std::to_string(tag)].loadFromFile("res/img/tower/tower" + std::to_string(tag) + ".png");
    }
    m_choices[i].first.first.setTexture(m_textures["tower" + std::to_string(tag)]);
    m_choices[i].first.first.setOrigin(static_cast<float>(m_choices[i].first.first.getTexture()->getSize().x / 2.0),
                                       static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0));
    m_choices[i].first.first.setPosition(
      static_cast<float>(m_choices[i].first.first.getTexture()->getSize().x / 2.0 + 90 * (i + 1)),
      static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0));
    if (m_fonts.find("arial") == m_fonts.end()) {
      m_fonts["arial"].loadFromFile("res/fonts/arial.ttf");
    }
    m_choices[i].first.second.setFont(m_fonts["arial"]);
    m_choices[i].first.second.setString(std::to_string(l_towerInfos[tag].m_cost));
    m_choices[i].first.second.setCharacterSize(30);
    m_choices[i].first.second.setOrigin(m_choices[i].first.second.getLocalBounds().width / 2,
                                        m_choices[i].first.second.getLocalBounds().height / 2);
    m_choices[i].first.second.setPosition(
      m_choices[i].first.first.getPosition() + sf::Vector2f(
        0, static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0)));
    m_choices[i].second = l_towerInfos[tag];
  }
  // Load Invader Turns
  std::vector<InvadeTurnInfo> l_invaderTurns;
  int l_turnSum;
  in >> l_turnSum;
  for (int i = 0; i < l_turnSum; ++i) {
    double l_calmTime;
    in >> l_calmTime;
    double l_speedBuff;
    in >> l_speedBuff;
    int l_typeSum;
    in >> l_typeSum;
    std::vector<std::pair<int, int> > l_turn(l_typeSum);
    for (int j = 0; j < l_typeSum; ++j) {
      int type, count;
      in >> type >> count;
      l_turn[j] = {type, count};
    }
    l_invaderTurns.push_back({l_calmTime, l_speedBuff, l_turn});
  }
  // Load Map
  m_places = std::vector<std::vector<Place> >(m_XRange, std::vector<Place>(m_YRange));
  auto l_placesType = std::vector<std::vector<int> >(m_XRange, std::vector<int>(m_YRange));
  int l_placeType;
  for (int j = 0; j < m_YRange; ++j) {
    for (int i = 0; i < m_XRange; ++i) {
      in >> l_placeType;
      l_placesType[i][j] = l_placeType;
      if (l_placeType == 0) {
        if (m_textures.find("grass0") == m_textures.end()) {
          m_textures["grass0"].loadFromFile("res/img/grass/grass0.png");
        }
        sf::Sprite l_sp(m_textures["grass0"]);
        l_sp.setOrigin(static_cast<float>(m_textures["grass0"].getSize().x / 2.0),
                       static_cast<float>(m_textures["grass0"].getSize().y / 2.0));
        l_sp.setPosition(static_cast<float>(45 + 90 * i), static_cast<float>(405 + 90 * j));
        m_places[i][j] = Place(l_sp, m_textures["grass0"].getSize(), PlaceType::Land);
      } else if (l_placeType == 1) {
        if (m_textures.find("road") == m_textures.end()) {
          m_textures["road"].loadFromFile("res/img/grass/road.png");
        }
        sf::Sprite l_sp(m_textures["road"]);
        l_sp.setOrigin(static_cast<float>(m_textures["road"].getSize().x / 2.0),
                       static_cast<float>(m_textures["road"].getSize().y / 2.0));
        l_sp.setPosition(static_cast<float>(45 + 90 * i), static_cast<float>(405 + 90 * j));
        m_places[i][j] = Place(l_sp, m_textures["road"].getSize(), PlaceType::Road);
      } else if (l_placeType == 3) {
        if (m_textures.find("startPoint") == m_textures.end()) {
          m_textures["startPoint"].loadFromFile("res/img/grass/startPoint.png");
        }
        sf::Sprite l_sp(m_textures["startPoint"]);
        l_sp.setOrigin(static_cast<float>(m_textures["startPoint"].getSize().x / 2.0),
                       static_cast<float>(m_textures["startPoint"].getSize().y / 2.0));
        l_sp.setPosition(static_cast<float>(45 + 90 * i), static_cast<float>(405 + 90 * j));
        m_places[i][j] = Place(l_sp, m_textures["startPoint"].getSize(), PlaceType::Road);
        m_startPoints.emplace_back(l_sp, m_textures["startPoint"].getSize(), std::make_pair(i, j), l_invaderTurns);
      } else if (l_placeType == 4) {
        if (m_textures.find("endPoint") == m_textures.end()) {
          m_textures["endPoint"].loadFromFile("res/img/grass/endPoint.png");
        }
        sf::Sprite l_esp(m_textures["endPoint"]);
        l_esp.setOrigin(static_cast<float>(m_textures["endPoint"].getSize().x / 2.0),
                        static_cast<float>(m_textures["endPoint"].getSize().y / 2.0));
        l_esp.setPosition(static_cast<float>(45 + 90 * i), static_cast<float>(405 + 90 * j));
        if (m_textures.find("grass2") == m_textures.end()) {
          m_textures["grass2"].loadFromFile("res/img/grass/grass2.png");
        }
        sf::Sprite l_sp(m_textures["grass2"]);
        l_sp.setOrigin(static_cast<float>(m_textures["grass2"].getSize().x / 2.0),
                       static_cast<float>(m_textures["grass2"].getSize().y / 2.0));
        l_sp.setPosition(static_cast<float>(45 + 90 * i), static_cast<float>(405 + 90 * j));
        m_places[i][j] = Place(l_sp, m_textures["grass2"].getSize(), PlaceType::End);
        m_endPoints.emplace_back(l_esp, l_esp.getTexture()->getSize(), std::make_pair(i, j));
      }
    }
  }
  in.close();
  struct State {
    int x;
    int y;
    std::vector<Direction> m_road;
  };
  for (const auto &l_sp: m_startPoints) {
    std::unordered_set<int> st;
    std::queue<State> q;
    q.push({l_sp.GetCoordinate().first, l_sp.GetCoordinate().second, {}});
    while (!q.empty()) {
      State s = q.front();
      q.pop();
      if (st.count(s.y * m_XRange + s.x)) {
        continue;
      }
      st.insert(s.y * m_XRange + s.x);
      if (m_places[s.x][s.y].GetPlaceType() == PlaceType::End) {
        m_roads.push_back({{s.x, s.y}, s.m_road});
        continue;
      }
      int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
      for (int i = 0; i < 4; ++i) {
        int tx = s.x + dirs[i][0], ty = s.y + dirs[i][1];
        if (tx < 0 || ty < 0 || tx >= m_XRange || ty >= m_YRange ||
            st.count(ty * m_XRange + tx) ||
            (m_places[tx][ty].GetPlaceType() != PlaceType::Road && m_places[tx][ty].GetPlaceType() != PlaceType::End)) {
          continue;
        }
        std::vector<Direction> nxt(s.m_road);
        switch (i) {
          case 0:
            nxt.push_back(Direction::Left);
            break;
          case 1:
            nxt.push_back(Direction::Right);
            break;
          case 2:
            nxt.push_back(Direction::Down);
            break;
          case 3:
            nxt.push_back(Direction::Up);
            break;
          default:
            break;
        }
        q.push({tx, ty, nxt});
      }
    }
  }
  std::vector<std::vector<Direction> > l_roads;
  std::transform(m_roads.begin(), m_roads.end(), std::back_inserter(l_roads), [](const auto &p) { return p.second; });
  for (auto &sp: m_startPoints) {
    sp.SetRoads(l_roads);
  }
}

void Map::LoadMap() {
  std::ifstream inTower("res/config/tower.json");
  const nlohmann::json l_towerData = nlohmann::json::parse(inTower);
  std::vector<TowerInfo> l_towerInfos(l_towerData.size());
  for (const auto &d: l_towerData) {
    l_towerInfos.push_back({
      d["cost"], d["atk"], d["range"], d["calmTime"], d["speed"],
      d["rgb"][0], d["rgb"][1], d["rgb"][2], d["bulletRadius"]
    });
  }
  inTower.close();
  std::ifstream in("res/config/map" + std::to_string(m_level) + ".json");
  nlohmann::json l_mapData = nlohmann::json::parse(in);
  in.close();
  const size_t l_choiceSum = l_mapData["choice"].size();
  m_choices = std::vector<std::pair<std::pair<sf::Sprite, sf::Text>, TowerInfo> >(l_choiceSum);
  for (int i = 0; i < l_choiceSum; ++i) {
    const auto &l_t = l_mapData["choice"][i];
    const int tag = l_t["tag"].get<int>();
    if (m_textures.find("tower" + std::to_string(tag)) == m_textures.end()) {
      m_textures["tower" + std::to_string(tag)].loadFromFile("res/img/tower/tower" + std::to_string(tag) + ".png");
    }
    m_choices[i].first.first.setTexture(m_textures["tower" + std::to_string(tag)]);
    m_choices[i].first.first.setOrigin(static_cast<float>(m_choices[i].first.first.getTexture()->getSize().x / 2.0),
                                       static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0));
    m_choices[i].first.first.setPosition(
      static_cast<float>(m_choices[i].first.first.getTexture()->getSize().x / 2.0 + 90 * (i + 1)),
      static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0));
    if (m_fonts.find("arial") == m_fonts.end()) {
      m_fonts["arial"].loadFromFile("res/fonts/arial.ttf");
    }
    m_choices[i].first.second.setFont(m_fonts["arial"]);
    m_choices[i].first.second.setString(std::to_string(l_towerInfos[tag].m_cost));
    m_choices[i].first.second.setCharacterSize(30);
    m_choices[i].first.second.setOrigin(m_choices[i].first.second.getLocalBounds().width / 2,
                                        m_choices[i].first.second.getLocalBounds().height / 2);
    m_choices[i].first.second.setPosition(
      m_choices[i].first.first.getPosition() + sf::Vector2f(
        0, static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0)));
    m_choices[i].second = l_towerInfos[tag];
  }
  // Load Invader Turns
  // TODO: Load Invader Turns

  // Load Map
  // TODO: Load Map
  m_places = std::vector<std::vector<Place> >(m_XRange, std::vector<Place>(m_YRange));
}


int Map::GetLives() const { return m_lives; }
bool Map::IsWin() const { return m_isWin; }
