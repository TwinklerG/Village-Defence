#include "EndPoint.h"

EndPoint::EndPoint() {}
EndPoint::EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size) {}
EndPoint::EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor) : Element(l_sp, l_size), m_cordinate(l_cor) {}
void EndPoint::Render(sf::RenderWindow *l_wind) const
{
  l_wind->draw(m_sprite);
}