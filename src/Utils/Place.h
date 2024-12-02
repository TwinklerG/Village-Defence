#pragma once
#include "Element.h"

class Tower : public Element
{
public:
  Tower();
  Tower(const sf::Sprite &, const sf::Vector2u &);
  void SetCalmTime(const sf::Time &l_time);
  const sf::Time &GetCalmTime();

private:
  sf::Time m_clamTime;
};

class Place : public Element
{
public:
  Place();
  Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  void Render(sf::RenderWindow *l_wind) const override;
  void SetTower(const Tower &l_tower);
  Tower& GetTower();

private:
  Tower m_tower;
};