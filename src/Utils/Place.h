#pragma once
#include "Element.h"

class Tower : public Element
{
public:
  Tower();
  Tower(const sf::Sprite &, const sf::Vector2u &);
  Tower(const sf::Sprite &, const sf::Vector2u &, const sf::Time &, int = 1, float = 90, int range = 400, int = 50);
  void Render(sf::RenderWindow *l_wind) const override;
  void SetCalmTime(const sf::Time &l_time);
  const sf::Time GetCalmTime() const;
  sf::CircleShape *GetCircle() const;
  void SetCircle(const sf::CircleShape *l_circle);
  const sf::Time GetClickCalmTime() const;
  void SetClickCalmTime(const sf::Time &l_time);
  const int &GetAttackPoint() const;
  const float &GetBulletSpeed() const;
  const int& GetCost() const;
  const int& GetRange() const;

  static sf::Time m_totalClickCalmTime;
  sf::Time m_totalCalmTime;

private:
  sf::Time m_clamTime;
  int m_attackPoint;
  sf::CircleShape *m_circle;
  sf::Time m_clickCalmTime;
  float m_bulletSpeed;
  int m_range;
  int m_cost;
};

enum class PlaceType
{
  Land,
  Road,
  Tower,
  Begin,
  End,
};

class Place : public Element
{
public:
  Place();
  Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const PlaceType &l_placeType);
  void Render(sf::RenderWindow *l_wind) const override;
  void SetTower(const Tower &l_tower);
  Tower &GetTower();
  const PlaceType &GetPlaceType();
  void SetPlaceType(const PlaceType &);

private:
  Tower m_tower;
  PlaceType m_placeType;
};

struct TowerInfo
{
  int m_cost;
  int m_attackPoint;
  int m_range;
  double m_calmTime;
  double m_speed;
};