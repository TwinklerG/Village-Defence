#pragma once
#include "Element.h"

class Tower : public Element
{
public:
  Tower();
  Tower(const sf::Sprite &, const sf::Vector2u &);
  void Render(sf::RenderWindow *l_wind) const override;
  void SetCalmTime(const sf::Time &l_time);
  const sf::Time &GetCalmTime();
  sf::CircleShape &GetCircle();
  void SetCircle(const sf::CircleShape &l_circle);

private:
  sf::Time m_clamTime;
  sf::CircleShape *m_circle;
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