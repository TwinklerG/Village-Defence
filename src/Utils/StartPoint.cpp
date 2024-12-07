#include "StartPoint.h"

sf::Time StartPoint::m_BreakTime = sf::seconds(5);

StartPoint::StartPoint() {}
StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor)
    : Element(l_sp, l_size),
      m_cordinate(l_cor),
      m_totalCalmTime(sf::seconds(1)) {}
StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor, const sf::Time &l_tct, const std::vector<std::vector<std::pair<int, int>>> &l_invaderTurns)
    : Element(l_sp, l_size),
      m_cordinate(l_cor),
      m_totalCalmTime(l_tct),
      m_invaderTurns(l_invaderTurns)
{
  std::ifstream in;
  in.open("res/config/invader.cfg");
  int typeSum;
  in >> typeSum;
}
void StartPoint::SetCalmTime(const sf::Time &l_t) { m_calmTime = l_t; }
const sf::Time &StartPoint::GetCalmTime() const { return m_calmTime; }
void StartPoint::RestartCalmTime() { m_calmTime = m_totalCalmTime; }
const std::pair<int, int> StartPoint::GetCordinate() const { return m_cordinate; }
Figure *StartPoint::Update(const sf::Time &l_elapsed)
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
  int idx = rand() % curTurn.size();
  curTurn[idx].second -= 1;
  if (curTurn[idx].second == 0)
  {
    curTurn.erase(curTurn.begin() + idx);
  }
  return nullptr;
}