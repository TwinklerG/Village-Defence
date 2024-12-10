#include "StartPoint.h"
#include "Utils.hpp"
sf::Time StartPoint::m_BreakTime = sf::seconds(5);

StartPoint::StartPoint() = default;

StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor)
  : Element(l_sp, l_size),
    m_totalCalmTime(sf::seconds(1)),
    m_coordinate(l_cor) {
  std::ifstream in;
  in.open("res/config/invader.cfg");
  int typeSum;
  in >> typeSum;
  for (int i = 0; i < typeSum; ++i) {
    int tag, lives, speed;
    in >> tag >> lives >> speed;
    m_figureInfos.push_back({lives, speed});
  }
}

StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor,
                       const std::vector<InvadeTurnInfo> &l_invaderTurns)
  : Element(l_sp, l_size),
    m_coordinate(l_cor),
    m_invaderTurns(l_invaderTurns) {
  std::ifstream in;
  in.open("res/config/invader.cfg");
  int typeSum;
  in >> typeSum;
  for (int i = 0; i < typeSum; ++i) {
    int tag, lives, speed, reward;
    in >> tag >> lives >> speed >> reward;
    m_figureInfos.push_back({lives, speed, reward});
  }
}

void StartPoint::SetCalmTime(const sf::Time &l_t) { m_calmTime = l_t; }
const sf::Time &StartPoint::GetCalmTime() const { return m_calmTime; }

void StartPoint::RestartCalmTime() {
  m_calmTime = !m_invaderTurns.empty()
                 ? sf::seconds(static_cast<float>(m_invaderTurns.front().m_calmTime))
                 : sf::seconds(0);
}

std::pair<int, int> StartPoint::GetCoordinate() const { return m_coordinate; }

std::shared_ptr<Figure> StartPoint::Update(const sf::Time &l_elapsed) {
  if (m_calmTime.asSeconds() > 0) {
    m_calmTime -= l_elapsed;
    return nullptr;
  }
  RestartCalmTime();
  if (m_invaderTurns.empty()) {
    return nullptr;
  }
  auto &[l_calmTime, l_speedBuff, l_infos] = m_invaderTurns.front();
  const int idx = Utils::RandInt(0, static_cast<int>(l_infos.size()) - 1);
  const int tag = l_infos[idx].first;
  l_infos[idx].second -= 1;
  if (l_infos[idx].second == 0) {
    l_infos.erase(l_infos.begin() + idx);
  }
  if (l_infos.empty()) {
    m_invaderTurns.erase(m_invaderTurns.begin());
    m_calmTime = sf::seconds(5);
  }
  std::string l_figureName = "invader" + std::to_string(tag);
  if (m_textures.find(l_figureName) == m_textures.end()) {
    m_textures[l_figureName].loadFromFile("res/img/invader/" + l_figureName + ".png");
  }
  sf::Sprite l_sp(m_textures[l_figureName]);
  l_sp.setOrigin(static_cast<float>(m_textures[l_figureName].getSize().x / 2.0),
                 static_cast<float>(m_textures[l_figureName].getSize().y / 2.0));
  l_sp.setPosition(static_cast<float>(45 + m_coordinate.first * 90), static_cast<float>(405 + 90 * m_coordinate.second));
  return std::make_shared<Figure>(l_sp, l_sp.getTexture()->getSize(), m_roads[Utils::RandInt(0, static_cast<int>(m_roads.size()) - 1)],
                                  m_figureInfos[tag].m_lives, static_cast<int>(m_figureInfos[tag].m_speed * l_speedBuff),
                                  m_figureInfos[tag].m_reward);
}

void StartPoint::SetRoads(const std::vector<std::vector<Direction> > &l_roads) {
  m_roads = l_roads;
}

int StartPoint::GetLeftTurns() const { return static_cast<int>(m_invaderTurns.size()); }
