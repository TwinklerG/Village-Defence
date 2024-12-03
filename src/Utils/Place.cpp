#include "Place.h"
Place::Place() : Element() {}
Place::Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size) {}
Place::Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const PlaceType &l_placeType) : Element(l_sp, l_size), m_placeType(l_placeType) {}
Tower &Place::GetTower() { return m_tower; }
void Place::SetTower(const Tower &l_tower) { m_tower = l_tower; }
void Place::Render(sf::RenderWindow *l_wind) const
{
  l_wind->draw(m_sprite);
  m_tower.Render(l_wind);
}
const PlaceType &Place::GetPlaceType() { return m_placeType; }
void Place::SetPlaceType(const PlaceType &l_t) { m_placeType = l_t; }

Tower::Tower() : m_circle(nullptr) {}
Tower::Tower(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size), m_circle(nullptr) {}
void Tower::SetCalmTime(const sf::Time &l_t) { m_clamTime = l_t; }
const sf::Time &Tower::GetCalmTime() { return m_clamTime; }
sf::CircleShape &Tower::GetCircle() { return *m_circle; }
void Tower::SetCircle(const sf::CircleShape &l_circle) { m_circle = new sf::CircleShape(l_circle); }
void Tower::Render(sf::RenderWindow *l_wind) const
{
  l_wind->draw(m_sprite);
  if (m_circle)
  {
    l_wind->draw(*m_circle);
  }
}