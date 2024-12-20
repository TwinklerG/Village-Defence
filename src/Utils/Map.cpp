#include "Map.h"
#include <unordered_set>
#include <queue>
#include <cmath>
#include <numeric>
#include <utility>
#include <iostream>

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

int Map::m_XRange = 20;
int Map::m_YRange = 10;

Map::Map(sf::RenderWindow *l_wind, const int l_level, std::string l_resolutions,
         const sf::Vector2f l_resolution) : m_isWin(false), m_resolution(std::move(l_resolutions)),
                                            m_atomResolution(l_resolution),
                                            m_level(l_level) { OnCreate(l_wind); }

Map::~Map() = default;

void Map::OnCreate(sf::RenderWindow *l_wind) {
  m_lives = 10;
  m_backup = sf::RectangleShape(sf::Vector2f(static_cast<float>(l_wind->getSize().x),
                                             static_cast<float>(l_wind->getSize().y)));
  m_backup.setFillColor(sf::Color(120, 120, 0));
  m_board = std::make_unique<Board>(sf::Vector2f(m_atomResolution.x, m_atomResolution.y));
  m_wind = l_wind;
  m_selected.m_tower = nullptr;
  LoadMap();
  if (m_fonts.find("arial") == m_fonts.end()) {
    m_fonts["arial"].loadFromFile("res/fonts/arial.ttf");
  }
  m_textBox = std::make_unique<gl::TextBox>(
    sf::Vector2f(static_cast<float>(l_wind->getSize().x) / 5.0f * 4.0f,
                 static_cast<float>(l_wind->getSize().y) / 10.0f),
    sf::Vector2f(static_cast<float>(l_wind->getSize().x) / 5.0f * 2,
                 static_cast<float>(l_wind->getSize().y) / 5.0f),
    6,
    m_fonts["arial"]);
  m_textBox->AddText("Welcome to Village Defence!");
}

void Map::Update(sf::RenderWindow *l_wind, const sf::Time &l_time) {
  // Update Buff
  if (m_propBuff.m_countDown > 0) {
    m_propBuff.m_countDown -= l_time.asSeconds();
    if (m_propBuff.m_countDown <= 0) {
      m_propBuff.Reset();
    }
  }
  // Check Game Finish Condition
  if (std::accumulate(m_startPoints.begin(), m_startPoints.end(), 0, [](const int accum, const StartPoint &l_sp) {
    return accum + l_sp.GetLeftTurns();
  }) == 0 && m_figures.empty()) {
    m_isWin = true;
  }
  if (m_selected.m_tower) {
    if (m_selected.m_selectType == SelectType::Choice) {
      // Selected Choice
      if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        m_selected.m_tower = nullptr;
      } else {
        m_selected.m_tower->GetSprite().setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                                                    static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
        m_selected.m_tower->GetCircle()->setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                                                     static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
      }
    } else if (m_selected.m_selectType == SelectType::Existence) {
      // Selected Existence
      m_selected.m_tower->SetCircle(nullptr);
      m_selected.m_tower = nullptr;
    }
  }
  // Click a Land
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    for (int i = 0; i < m_XRange; i++) {
      for (int j = 0; j < m_YRange; j++) {
        if (checkMouseSelect(m_places[i][j], m_wind)) {
          if (m_selected.m_tower && m_selected.m_selectType == SelectType::Choice && (m_places[i][j].GetPlaceType() ==
                PlaceType::Land || m_places[i][j].GetPlaceType() == PlaceType::Tower)) {
            // Lay a Tower
            std::shared_ptr<Tower> t = m_selected.m_tower;
            t->GetSprite().setPosition(m_atomResolution.x / 2.0f
                                       + m_atomResolution.x * static_cast<float>(i),
                                       m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f
                                       + m_atomResolution.y / 2.0f + m_atomResolution.y * static_cast<float>(j));
            t->SetCircle(nullptr);
            m_places[i][j].SetTower(t);
            m_places[i][j].SetPlaceType(PlaceType::Tower);
            m_board->SetMoney(m_board->GetMoney() - t->GetCost());
            m_selected.m_tower = nullptr;
          } else if (m_places[i][j].GetPlaceType() == PlaceType::Tower && m_selected.m_tower == nullptr) {
            // Select an Existing Tower
            m_selected.m_selectType = SelectType::Existence;
            m_selected.x = i;
            m_selected.y = j;
            m_selected.m_tower = m_places[i][j].GetTower();
            std::shared_ptr<Tower> l_tower = m_places[i][j].GetTower();
            sf::CircleShape l_circle(static_cast<float>(l_tower->GetRange()) * m_atomResolution.x);
            l_circle.setOrigin(l_circle.getRadius(), l_circle.getRadius());
            l_circle.setFillColor(sf::Color(0, 0, 0, 0));
            l_circle.setOutlineColor(sf::Color::Red);
            l_circle.setOutlineThickness(m_atomResolution.x / 50.0f);
            l_circle.setPosition(
              m_atomResolution.x / 2.0f + m_atomResolution.x * static_cast<float>(i),
              m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f + m_atomResolution.y / 2.0f + m_atomResolution.y
              * static_cast<float>(j));
            m_places[i][j].GetTower()->SetCircle(std::make_shared<sf::CircleShape>(l_circle));
          }
        }
      }
    }
  }
  // StartPoints Update
  for (StartPoint &l_startPoint: m_startPoints) {
    if (auto l_fig = l_startPoint.Update(l_time)) {
      m_figures.emplace_back(l_fig);
    }
  }
  // Figures Update
  for (auto &l_fig: m_figures) {
    l_fig->Update(l_time, m_propBuff.m_decelerate);
  }
  // Tower Attack Invaders
  for (int i = 0; i < m_XRange; ++i) {
    for (int j = 0; j < m_YRange; ++j) {
      if (m_places[i][j].GetPlaceType() == PlaceType::Tower) {
        if (m_places[i][j].GetTower()->GetCalmTime().asSeconds() > 0) {
          m_places[i][j].GetTower()->SetCalmTime(m_places[i][j].GetTower()->GetCalmTime() - l_time);
          continue;
        }
        for (const auto &l_fig: m_figures) {
          if (checkInRange(*l_fig, m_places[i][j],
                           static_cast<float>(m_places[i][j].GetTower()->GetRange()) * m_atomResolution.x)) {
            int cnt = 0;
            for (auto &l_b: m_bullets) {
              if (l_b.GetTargetFigure() == l_fig) {
                cnt += l_b.GetAtk();
              }
            }
            if (cnt >= l_fig->GetLives()) {
              continue;
            }
            const std::shared_ptr<Tower> l_tower = m_places[i][j].GetTower();
            sf::CircleShape cs(static_cast<float>(l_tower->GetBulletRadius()));
            cs.setFillColor(l_tower->GetBulletColor());
            cs.setPosition(m_places[i][j].getPosition());
            cs.setOrigin(cs.getRadius(), cs.getRadius());
            m_bullets.emplace_back(cs, l_fig, static_cast<int>(m_places[i][j].GetTower()->GetBulletSpeed()),
                                   m_places[i][j].GetTower()->GetAttackPoint());
            break;
          }
        }
        m_places[i][j].GetTower()->SetCalmTime(
          sf::seconds(
            m_places[i][j].GetTower()->m_totalCalmTime.asSeconds() / static_cast<float>(m_propBuff.m_accelerate)));
      }
    }
  }
  // Bullets Update
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
  // Invaders Update
  std::vector<std::shared_ptr<Figure> > next_figures{};
  for (const auto &l_fig: m_figures) {
    for (const auto &l_ep: m_endPoints) {
      if (checkInRange(*l_fig, l_ep, l_fig->getSize().x / 2.0 + l_ep.getSize().x / 2.0)) {
        --m_lives;
        m_textBox->AddText("Village Invaded, current lives: " + std::to_string(m_lives));
        if (auto itr = std::find(next_figures.begin(), next_figures.end(), l_fig);
          itr != next_figures.end()) {
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
  // Check whether any Choice is selected
  for (const auto &[l_choice, l_towerInfo]: m_choices) {
    if (checkMouseSelectSprite(l_choice.first, m_wind) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_board->
        GetMoney() >= l_towerInfo.m_cost) {
      if (m_selected.m_selectType == SelectType::Existence) {
        if (m_selected.m_tower) {
          m_selected.m_tower->SetCircle(nullptr);
        }
      }
      m_selected.m_tower = std::make_shared<Tower>(l_choice.first,
                                                   l_choice.first.getTexture()->getSize(),
                                                   sf::seconds(static_cast<float>(l_towerInfo.m_calmTime)),
                                                   l_towerInfo.m_attackPoint,
                                                   static_cast<float>(l_towerInfo.m_speed),
                                                   l_towerInfo.m_range,
                                                   l_towerInfo.m_cost,
                                                   l_towerInfo.m_red,
                                                   l_towerInfo.m_green,
                                                   l_towerInfo.m_blue,
                                                   l_towerInfo.m_bulletRadius);
      m_selected.m_tower->GetSprite().setOrigin(
        static_cast<float>(l_choice.first.getTexture()->getSize().x / 2.0),
        static_cast<float>(l_choice.first.getTexture()->getSize().y / 2.0));
      m_selected.m_tower->GetSprite().setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                                                  static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
      sf::CircleShape l_circle(static_cast<float>(l_towerInfo.m_range) * m_atomResolution.x);
      l_circle.setOrigin(l_circle.getRadius(), l_circle.getRadius());
      l_circle.setFillColor(sf::Color(0, 0, 0, 0));
      l_circle.setOutlineColor(sf::Color::Red);
      l_circle.setOutlineThickness(m_atomResolution.x / 50.0f);
      l_circle.setPosition(static_cast<float>(sf::Mouse::getPosition(*l_wind).x),
                           static_cast<float>(sf::Mouse::getPosition(*l_wind).y));
      m_selected.m_tower->SetCircle(std::make_shared<sf::CircleShape>(l_circle));
      m_selected.m_selectType = SelectType::Choice;
    }
  }
  // Update Labels
  for (auto &l_label: m_labels) {
    l_label.Update(*m_wind);
  }
}

void Map::Render(sf::RenderWindow *l_wind) {
  m_wind->draw(m_backup);
  for (const auto &[fst, snd]: m_choices) {
    l_wind->draw(fst.first);
    l_wind->draw(fst.second);
  }
  for (const auto &l_label: m_labels) {
    l_label.Render(*m_wind);
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
  for (const auto &l_fig: m_figures) {
    l_fig->Render(l_wind);
  }
  if (m_selected.m_tower) {
    m_selected.m_tower->Render(l_wind);
  }
  m_board->Render(l_wind);
  m_textBox->Render(*l_wind);
}

void Map::Reload() {
  LoadProp();
}

void Map::LoadMap() {
  std::ifstream inTower("res/config/tower.json");
  const nlohmann::json l_towerData = nlohmann::json::parse(inTower);
  std::vector<TowerInfo> l_towerInfos;
  for (const auto &d: l_towerData) {
    l_towerInfos.push_back({
      d["tag"], d["cost"], d["atk"], d["range"], d["calmTime"], d["speed"],
      d["rgb"][0], d["rgb"][1], d["rgb"][2], d["bulletRadius"]
    });
  }
  sort(l_towerInfos.begin(), l_towerInfos.end(), [](const TowerInfo &l_towerInfo1, const TowerInfo &l_towerInfo2) {
    return l_towerInfo1.m_tag < l_towerInfo2.m_tag;
  });
  inTower.close();
  std::ifstream in("res/config/map" + std::to_string(m_level) + ".json");
  nlohmann::json l_mapData = nlohmann::json::parse(in);
  in.close();
  // Load choices
  const size_t l_choiceSum = l_mapData["choices"].size();
  m_choices = std::vector<std::pair<std::pair<sf::Sprite, sf::Text>, TowerInfo> >(l_choiceSum);
  for (int i = 0; i < l_choiceSum; ++i) {
    int tag = l_mapData["choices"][i];
    if (m_textures.find("tower" + std::to_string(tag)) == m_textures.end()) {
      m_textures["tower" + std::to_string(tag)].loadFromFile(
        "res/img/tower/" + m_resolution + "/tower" + std::to_string(tag) + ".png");
    }
    m_choices[i].first.first.setTexture(m_textures["tower" + std::to_string(tag)]);
    m_choices[i].first.first.setOrigin(static_cast<float>(m_choices[i].first.first.getTexture()->getSize().x / 2.0),
                                       static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0));
    m_choices[i].first.first.setPosition(
      static_cast<float>(m_choices[i].first.first.getTexture()->getSize().x / 2.0 + m_atomResolution.x * static_cast<
                           float>(i + 1)),
      static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0));
    if (m_fonts.find("arial") == m_fonts.end()) {
      m_fonts["arial"].loadFromFile("res/fonts/arial.ttf");
    }
    m_choices[i].first.second.setFont(m_fonts["arial"]);
    m_choices[i].first.second.setString(std::to_string(l_towerInfos[tag].m_cost));
    m_choices[i].first.second.setCharacterSize(static_cast<unsigned int>(m_atomResolution.x) / 3);
    m_choices[i].first.second.setOrigin(m_choices[i].first.second.getLocalBounds().width / 2,
                                        m_choices[i].first.second.getLocalBounds().height / 2);
    m_choices[i].first.second.setPosition(
      m_choices[i].first.first.getPosition() + sf::Vector2f(
        0, static_cast<float>(m_choices[i].first.first.getTexture()->getSize().y / 2.0)));
    m_choices[i].second = l_towerInfos[tag];
  }
  // Load Invader Turns
  const auto &invadeData = l_mapData["invaderTurns"];
  std::vector<InvadeTurnInfo> l_invaderTurns;
  for (const auto &l_turn: invadeData) {
    const double l_calmTime = l_turn["calmTime"], l_speedBuff = l_turn["buff"];
    const auto &l_invaders = l_turn["invaders"];
    std::vector<std::pair<int, int> > l_invadeTurn;
    for (const auto &l_invader: l_invaders) {
      l_invadeTurn.emplace_back(l_invader["type"], l_invader["num"]);
    }
    l_invaderTurns.push_back({l_calmTime, l_speedBuff, l_invadeTurn});
  }
  // Load Map
  m_places = std::vector<std::vector<Place> >(m_XRange, std::vector<Place>(m_YRange));
  auto l_placesType = l_mapData["map"];
  for (int j = 0; j < m_YRange; ++j) {
    for (int i = 0; i < m_XRange; ++i) {
      if (const int l_placeType = l_placesType[j][i];
        l_placeType == 0) {
        if (m_textures.find("grass0") == m_textures.end()) {
          m_textures["grass0"].loadFromFile("res/img/grass/" + m_resolution + "/grass0.png");
        }
        sf::Sprite l_sp(m_textures["grass0"]);
        l_sp.setOrigin(static_cast<float>(m_textures["grass0"].getSize().x / 2.0),
                       static_cast<float>(m_textures["grass0"].getSize().y / 2.0));
        l_sp.setPosition(
          m_atomResolution.x / 2.0f + m_atomResolution.x *
          static_cast<float>(i),
          m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f + m_atomResolution.y / 2.0f + m_atomResolution.y *
          static_cast<float>(j));
        m_places[i][j] = Place(l_sp, m_textures["grass0"].getSize(), PlaceType::Land);
      } else if (l_placeType == 1) {
        if (m_textures.find("road") == m_textures.end()) {
          m_textures["road"].loadFromFile("res/img/grass/" + m_resolution + "/road.png");
        }
        sf::Sprite l_sp(m_textures["road"]);
        l_sp.setOrigin(static_cast<float>(m_textures["road"].getSize().x / 2.0),
                       static_cast<float>(m_textures["road"].getSize().y / 2.0));
        l_sp.setPosition(m_atomResolution.x / 2.0f
                         + m_atomResolution.x * static_cast<float>(i),
                         m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f
                         + m_atomResolution.y / 2.0f + m_atomResolution.y * static_cast<float>(j));
        m_places[i][j] = Place(l_sp, m_textures["road"].getSize(), PlaceType::Road);
      } else if (l_placeType == 3) {
        if (m_textures.find("startPoint") == m_textures.end()) {
          m_textures["startPoint"].loadFromFile("res/img/grass/" + m_resolution + "/startPoint.png");
        }
        sf::Sprite l_sp(m_textures["startPoint"]);
        l_sp.setOrigin(static_cast<float>(m_textures["startPoint"].getSize().x / 2.0),
                       static_cast<float>(m_textures["startPoint"].getSize().y / 2.0));
        l_sp.setPosition(m_atomResolution.x / 2.0f
                         + m_atomResolution.x * static_cast<float>(i),
                         m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f
                         + m_atomResolution.y / 2.0f +
                         m_atomResolution.y * static_cast<float>(j));
        m_places[i][j] = Place(l_sp, m_textures["startPoint"].getSize(), PlaceType::Road);
        m_startPoints.emplace_back(l_sp, m_textures["startPoint"].getSize(), std::make_pair(i, j), l_invaderTurns,
                                   m_resolution, m_atomResolution);
      } else if (l_placeType == 4) {
        if (m_textures.find("endPoint") == m_textures.end()) {
          m_textures["endPoint"].loadFromFile("res/img/grass/" + m_resolution + "/endPoint.png");
        }
        sf::Sprite l_esp(m_textures["endPoint"]);
        l_esp.setOrigin(static_cast<float>(m_textures["endPoint"].getSize().x / 2.0),
                        static_cast<float>(m_textures["endPoint"].getSize().y / 2.0));
        l_esp.setPosition(m_atomResolution.x / 2.0f
                          + m_atomResolution.x * static_cast<float>(i),
                          m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f
                          + m_atomResolution.y / 2.0f +
                          m_atomResolution.y * static_cast<float>(j));
        if (m_textures.find("grass2") == m_textures.end()) {
          m_textures["grass2"].loadFromFile("res/img/grass/" + m_resolution + "/grass2.png");
        }
        sf::Sprite l_sp(m_textures["grass2"]);
        l_sp.setOrigin(static_cast<float>(m_textures["grass2"].getSize().x / 2.0),
                       static_cast<float>(m_textures["grass2"].getSize().y / 2.0));
        l_sp.setPosition(m_atomResolution.x / 2.0f
                         + m_atomResolution.x * static_cast<float>(i),
                         m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f
                         + m_atomResolution.y / 2.0f + m_atomResolution.y * static_cast<float>(j));
        m_places[i][j] = Place(l_sp, m_textures["grass2"].getSize(), PlaceType::End);
        m_endPoints.emplace_back(l_esp, l_esp.getTexture()->getSize(), std::make_pair(i, j));
      }
    }
  }
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
      auto [x, y, m_road] = q.front();
      q.pop();
      if (st.count(y * m_XRange + x)) {
        continue;
      }
      st.insert(y * m_XRange + x);
      if (m_places[x][y].GetPlaceType() == PlaceType::End) {
        m_roads.push_back({{x, y}, m_road});
        continue;
      }
      int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
      for (int i = 0; i < 4; ++i) {
        int tx = x + dirs[i][0], ty = y + dirs[i][1];
        if (tx < 0 || ty < 0 || tx >= m_XRange || ty >= m_YRange ||
            st.count(ty * m_XRange + tx) ||
            (m_places[tx][ty].GetPlaceType() != PlaceType::Road && m_places[tx][ty].GetPlaceType() != PlaceType::End)) {
          continue;
        }
        std::vector<Direction> nxt(m_road);
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

void Map::Save() {
  nlohmann::json l_gameState;
  l_gameState["m_lives"] = m_lives;
  l_gameState["m_level"] = m_level;
  std::vector<std::vector<int> > l_places(m_YRange, std::vector<int>(m_XRange));
  for (int i = 0; i < m_YRange; ++i) {
    for (int j = 0; j < m_XRange; ++j) {
      l_places[i][j] = static_cast<int>(m_places[j][i].GetPlaceType());
    }
  }
  l_gameState["m_places"] = l_places;
  std::ofstream out("res/config/save.json");
  out << std::setw(2) << l_gameState;
  std::cout << "Save Finished!\n";
}

void Map::LoadProp() {
  m_labels.clear();
  std::ifstream l_propIn("res/config/store.json");
  nlohmann::json l_propData = nlohmann::json::parse(l_propIn);
  l_propIn.close();
  auto l_props = l_propData["props"];
  if (m_textures.find("ACCELERATE") == m_textures.end()) {
    m_textures["ACCELERATE"].loadFromFile("res/img/prop/" + m_resolution + "/prop_accelerate.png");
  }
  if (m_textures.find("DECELERATE") == m_textures.end()) {
    m_textures["DECELERATE"].loadFromFile("res/img/prop/" + m_resolution + "/prop_decelerate.png");
  }
  for (int i = 0; i < l_props.size(); ++i) {
    std::string l_propName = l_props[i]["name"], l_propCnt = nlohmann::to_string(l_props[i]["stock"]);
    m_labels.emplace_back(m_textures[l_propName], sf::Vector2f(
                            m_atomResolution.x * static_cast<float>(6 + i) + static_cast<float>(m_textures[l_propName].
                              getSize().x) / 2.0f,
                            static_cast<float>(m_textures[l_propName].getSize().y) / 2.0f), l_propCnt,
                          static_cast<unsigned int>(m_atomResolution.x) / 3, m_fonts["arial"],
                          [i, this]() {
                            std::ifstream in("res/config/store.json");
                            if (nlohmann::json data = nlohmann::json::parse(in); data["props"][i]["stock"] > 0) {
                              in.close();
                              data["props"][i]["stock"] = static_cast<int>(data["props"][i]["stock"]) - 1;
                              std::ofstream out("res/config/store.json");
                              out << std::setw(4) << data;
                              out.close();
                              m_labels[i].SetTextString(std::to_string(static_cast<int>(data["props"][i]["stock"])));
                              std::cout << data["props"][i]["stock"] << "\n";
                              if (data["props"][i]["name"] == "ACCELERATE") {
                                m_propBuff.m_accelerate = 3;
                              } else if (data["props"][i]["name"] == "DECELERATE") {
                                m_propBuff.m_decelerate = 0.3;
                              }
                              m_propBuff.m_countDown = m_propBuff.m_countDownSum;
                            }
                          });
  }
}

int Map::GetLives() const { return m_lives; }
bool Map::IsWin() const { return m_isWin; }
