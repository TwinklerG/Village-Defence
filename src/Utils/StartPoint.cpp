#include "StartPoint.h"

#include <utility>
#include "Utils.hpp"

int StartPoint::m_YRange = 10;

sf::Time StartPoint::m_BreakTime = sf::seconds(5);

StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor,
                       const std::vector<InvadeTurnInfo> &l_invaderTurns, std::string l_resolution,
                       const sf::Vector2f l_atomResolution)
  : Element(l_sp, l_size),
    m_coordinate(l_cor),
    m_invadeTurns(l_invaderTurns),
    m_resolution(std::move(l_resolution)),
    m_atomResolution(l_atomResolution) {
  OnCreate();
}

void StartPoint::OnCreate() {
  std::ifstream in("res/config/invader.json");
  nlohmann::json invaderData = nlohmann::json::parse(in);
  for (const auto &invader: invaderData) {
    m_figureInfos.push_back({invader["lives"], invader["speed"], invader["reward"]});
  }
}

void StartPoint::ResetInvadeTurns(const std::vector<InvadeTurnInfo> &l_invaderTurns) {
  m_invadeTurns = l_invaderTurns;
  OnCreate();
}

void StartPoint::SetCalmTime(const sf::Time &l_time) { m_calmTime = l_time; }
const sf::Time &StartPoint::GetCalmTime() const { return m_calmTime; }

void StartPoint::RestartCalmTime() {
  m_calmTime = !m_invadeTurns.empty()
                 ? sf::seconds(static_cast<float>(m_invadeTurns.front().m_calmTime))
                 : sf::seconds(0);
}

std::pair<int, int> StartPoint::GetCoordinate() const { return m_coordinate; }

std::shared_ptr<Figure> StartPoint::Update(const sf::Time &l_elapsed) {
  if (m_calmTime.asSeconds() > 0) {
    m_calmTime -= l_elapsed;
    return nullptr;
  }
  RestartCalmTime();
  if (m_invadeTurns.empty()) {
    return nullptr;
  }
  auto &[l_calmTime, l_speedBuff, l_infos] = m_invadeTurns.front();
  const int idx = gl::RandInt(0, static_cast<int>(l_infos.size()) - 1);
  const int tag = l_infos[idx].first;
  l_infos[idx].second -= 1;
  if (l_infos[idx].second == 0) {
    l_infos.erase(l_infos.begin() + idx);
  }
  if (l_infos.empty()) {
    m_invadeTurns.erase(m_invadeTurns.begin());
    m_calmTime = sf::seconds(5);
  }
  const std::string l_figureName = "invader" + std::to_string(tag);
  if (m_textures.find(l_figureName) == m_textures.end()) {
    m_textures[l_figureName] = sf::Texture("res/img/invader/" + m_resolution + "/" + l_figureName + ".png");
  }
  sf::Sprite l_sp(m_textures[l_figureName]);
  l_sp.setOrigin({
    static_cast<float>(m_textures[l_figureName].getSize().x / 2.0),
    static_cast<float>(m_textures[l_figureName].getSize().y / 2.0)
  });
  l_sp.setPosition({
    m_atomResolution.x / 2.0f + m_atomResolution.x * static_cast<float>(m_coordinate.first),
    m_atomResolution.y * static_cast<float>(m_YRange) / 4.0f + m_atomResolution.y / 2.0f + m_atomResolution.y *
    static_cast<float>(m_coordinate.second)
  });
  return std::make_shared<Figure>(idx, l_sp, l_sp.getTexture().getSize(),
                                  m_roads[gl::RandInt(0, static_cast<int>(m_roads.size()) - 1)],
                                  m_figureInfos[tag].m_lives,
                                  static_cast<int>(m_figureInfos[tag].m_speed * l_speedBuff),
                                  m_figureInfos[tag].m_reward, m_atomResolution);
}

void StartPoint::SetRoads(const std::vector<std::vector<Direction> > &l_roads) {
  m_roads = l_roads;
}

int StartPoint::GetLeftTurns() const { return static_cast<int>(m_invadeTurns.size()); }

std::vector<InvadeTurnInfo> StartPoint::GetInvadeTurns() const {
  return m_invadeTurns;
}
