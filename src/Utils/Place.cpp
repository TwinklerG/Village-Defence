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

sf::Time Tower::m_totalClickCalmTime = sf::seconds(0.5);
Tower::Tower()
    : Element(),
      m_circle(nullptr),
      m_clamTime(sf::seconds(0)),
      m_totalCalmTime(sf::seconds(1)),
      m_attackPoint(1) {}
Tower::Tower(const sf::Sprite &l_sp, const sf::Vector2u &l_size)
    : Element(l_sp, l_size),
      m_circle(nullptr),
      m_clamTime(sf::seconds(0)),
      m_totalCalmTime(sf::seconds(1)),
      m_attackPoint(1),
      m_bulletSpeed(180) {}
Tower::Tower(const sf::Sprite &l_sp,
             const sf::Vector2u &l_size,
             const sf::Time &l_ct, int l_atk, float l_bspeed, int l_range, int l_cost)
    : Element(l_sp, l_size),
      m_circle(nullptr),
      m_clamTime(sf::seconds(0)),
      m_totalCalmTime(l_ct),
      m_attackPoint(l_atk),
      m_bulletSpeed(l_bspeed),
      m_range(l_range),
      m_cost(l_cost) {}
void Tower::SetCalmTime(const sf::Time &l_t) { m_clamTime = l_t; }
const sf::Time Tower::GetCalmTime() const { return m_clamTime; }
sf::CircleShape *Tower::GetCircle() const { return m_circle; }
void Tower::SetCircle(const sf::CircleShape *l_circle)
{
  if (m_circle)
  {
    delete m_circle;
    m_circle = nullptr;
  }
  if (l_circle)
  {
    m_circle = new sf::CircleShape(*l_circle);
  }
}
void Tower::Render(sf::RenderWindow *l_wind) const
{
  l_wind->draw(m_sprite);
  if (m_circle)
  {
    l_wind->draw(*m_circle);
  }
}
const sf::Time Tower::GetClickCalmTime() const { return m_clickCalmTime; }
void Tower::SetClickCalmTime(const sf::Time &l_time) { m_clickCalmTime = l_time; }
const int &Tower::GetAttackPoint() const { return m_attackPoint; }
const float &Tower::GetBulletSpeed() const { return m_bulletSpeed; }
const int &Tower::GetCost() const { return m_cost; }
const int &Tower::GetRange() const { return m_range; }