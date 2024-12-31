#include "Place.h"

Place::Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size), m_tower(nullptr),
                                                                   m_placeType() {
}

Place::Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const PlaceType &l_placeType) : Element(l_sp, l_size),
  m_tower(nullptr), m_placeType(l_placeType) {
}

std::shared_ptr<Tower> Place::GetTower() { return m_tower; }

void Place::SetTower(std::shared_ptr<Tower> l_tower) {
  m_tower = std::move(l_tower);
}

void Place::Render(sf::RenderWindow *l_wind) const {
  l_wind->draw(m_sprite);
  if (m_tower) {
    m_tower->Render(l_wind);
  }
}

const PlaceType &Place::GetPlaceType() const { return m_placeType; }
void Place::SetPlaceType(const PlaceType &l_t) { m_placeType = l_t; }

sf::Time Tower::m_totalClickCalmTime = sf::seconds(0.5);

Tower::Tower(const sf::Sprite &l_sp,
             const sf::Vector2u &l_size,
             const sf::Time &l_ct, const int l_atk, const float l_bSpeed, const double range, const int l_cost,
             const int red, const int green, const int blue, const double radius,
             int l_tag)
  : Element(l_sp, l_size),
    m_totalCalmTime(l_ct),
    m_clamTime(sf::seconds(0)),
    m_attackPoint(l_atk),
    m_circle(nullptr),
    m_bulletRadius(radius),
    m_bulletColor(sf::Color(red, green, blue)),
    m_bulletSpeed(l_bSpeed),
    m_range(range),
    m_cost(l_cost),
    m_tag(l_tag) {
}

void Tower::SetCalmTime(const sf::Time &l_time) { m_clamTime = l_time; }
sf::Time Tower::GetCalmTime() const { return m_clamTime; }

std::shared_ptr<sf::CircleShape> Tower::GetCircle() const { return m_circle; }

void Tower::SetCircle(const std::shared_ptr<sf::CircleShape> &l_circle) {
  m_circle = l_circle;
}

void Tower::Render(sf::RenderWindow *l_wind) const {
  l_wind->draw(m_sprite);
  if (m_circle) {
    l_wind->draw(*m_circle);
  }
}

const int &Tower::GetAttackPoint() const { return m_attackPoint; }
const float &Tower::GetBulletSpeed() const { return m_bulletSpeed; }
const int &Tower::GetCost() const { return m_cost; }
const double &Tower::GetRange() const { return m_range; }
const sf::Color &Tower::GetBulletColor() const { return m_bulletColor; }
const double &Tower::GetBulletRadius() const { return m_bulletRadius; }
int Tower::GetTag() const { return m_tag; }
