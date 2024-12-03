#include "EndPoint.h"

EndPoint::EndPoint() {}
EndPoint::EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size) {}
EndPoint::EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const sf::Sprite &l_esp, const std::pair<int, int> &l_cor) : Element(l_sp, l_size), m_cordinate(l_cor), m_endPointSprite(l_esp) {}
void EndPoint::Render(sf::RenderWindow *l_wind) const
{
  l_wind->draw(m_sprite);
  l_wind->draw(m_endPointSprite);
}
const sf::Sprite &EndPoint::GetEndPointSprite() { return m_endPointSprite; }
void EndPoint::SetEndPointSprite(const sf::Sprite &l_esp) { m_endPointSprite = l_esp; }
const std::pair<int, int> EndPoint::GetCordinate() const { return m_cordinate; }