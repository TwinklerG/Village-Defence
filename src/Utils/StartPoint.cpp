#include "StartPoint.h"

StartPoint::StartPoint() {}
StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size) {}
StartPoint::StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor, const sf::Time &l_tct) : Element(l_sp, l_size), m_cordinate(l_cor), m_totalCalmTime(l_tct) {}
void StartPoint::SetCalmTime(const sf::Time &l_t) { m_calmTime = l_t; }
const sf::Time &StartPoint::GetCalmTime() const { return m_calmTime; }
void StartPoint::RestartCalmTime() { m_calmTime = m_totalCalmTime; }
const std::pair<int, int> StartPoint::GetCordinate() const { return m_cordinate; }