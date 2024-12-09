#include "StartPoint.h"

sf::Time StartPoint::m_BreakTime = sf::seconds(5);

StartPoint::StartPoint() {}
StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor)
    : Element(l_sp, l_size),
      m_cordinate(l_cor),
      m_totalCalmTime(sf::seconds(1))
{
  std::ifstream in;
  in.open("res/config/invader.cfg");
  int typeSum;
  in >> typeSum;
  for (int i = 0; i < typeSum; ++i)
  {
    int tag, lives, speed;
    in >> tag >> lives >> speed;
    m_figureInfos.push_back({lives, speed});
  }
}
StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor, const std::vector<InvadeTurnInfo> &l_invaderTurns)
    : Element(l_sp, l_size),
      m_cordinate(l_cor),
      m_invaderTurns(l_invaderTurns)
{
  std::ifstream in;
  in.open("res/config/invader.cfg");
  int typeSum;
  in >> typeSum;
  for (int i = 0; i < typeSum; ++i)
  {
    int tag, lives, speed, reward;
    in >> tag >> lives >> speed >> reward;
    m_figureInfos.push_back({lives, speed, reward});
  }
}
void StartPoint::SetCalmTime(const sf::Time &l_t) { m_calmTime = l_t; }
const sf::Time &StartPoint::GetCalmTime() const { return m_calmTime; }
void StartPoint::RestartCalmTime() { m_calmTime = !m_invaderTurns.empty() ? sf::seconds(m_invaderTurns.front().m_calmTime) : sf::seconds(0); }
const std::pair<int, int> StartPoint::GetCordinate() const { return m_cordinate; }
std::shared_ptr<Figure> StartPoint::Update(const sf::Time &l_elapsed)
{
  if (m_calmTime.asSeconds() > 0)
  {
    m_calmTime -= l_elapsed;
    return nullptr;
  }
  RestartCalmTime();
  if (m_invaderTurns.size() == 0)
  {
    return nullptr;
  }
  auto &curTurn = m_invaderTurns.front();
  int idx = rand() % curTurn.m_infos.size();
  int tag = curTurn.m_infos[idx].first;
  int l_speedBuff = curTurn.m_speedBuff;
  curTurn.m_infos[idx].second -= 1;
  if (curTurn.m_infos[idx].second == 0)
  {
    curTurn.m_infos.erase(curTurn.m_infos.begin() + idx);
  }
  if (curTurn.m_infos.size() == 0)
  {
    m_invaderTurns.erase(m_invaderTurns.begin());
    m_calmTime = sf::seconds(5);
  }
  std::string l_figureName = "invader" + std::to_string(tag);
  if (m_textures.find(l_figureName) == m_textures.end())
  {
    m_textures[l_figureName].loadFromFile("res/imgs/invader/" + l_figureName + ".png");
  }
  sf::Sprite l_sp(m_textures[l_figureName]);
  l_sp.setOrigin(m_textures[l_figureName].getSize().x / 2, m_textures[l_figureName].getSize().y / 2);
  l_sp.setPosition(45 + m_cordinate.first * 90, 405 + 90 * m_cordinate.second);
  return std::make_shared<Figure>(l_sp, l_sp.getTexture()->getSize(), m_roads[rand() % m_roads.size()], m_figureInfos[tag].m_lives, m_figureInfos[tag].m_speed * l_speedBuff, m_figureInfos[tag].m_reward);
}
void StartPoint::SetRoads(const std::vector<std::vector<Direction>> &l_roads)
{
  m_roads = l_roads;
}
int StartPoint::GetLeftTurns() const { return m_invaderTurns.size(); }