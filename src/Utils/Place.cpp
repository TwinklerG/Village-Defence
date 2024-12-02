#include "Place.h"
Place::Place() : Element() {}
Place::Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size) {}
void Place::Render(sf::RenderWindow *l_wind) const
{
  l_wind->draw(m_sprite);
  m_tower.Render(l_wind);
}
Tower &Place::GetTower() { return m_tower; }
void Place::SetTower(const Tower &l_tower) { m_tower = l_tower; }

Tower::Tower() {}
Tower::Tower(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size) {}
void Tower::SetCalmTime(const sf::Time &l_t) { m_clamTime = l_t; }
const sf::Time &Tower::GetCalmTime() { return m_clamTime; }