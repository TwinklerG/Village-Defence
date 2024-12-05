#pragma once
#include <SFML/Graphics.hpp>
#include "Element.h"
#include "Figure.h"

class Bullet
{
public:
  Bullet();
  Bullet(const sf::CircleShape &l_circle, Figure *l_targetFig, int = 180);
  ~Bullet();
  Figure *GetTargetFigure();
  const sf::Vector2f getPosition() const;
  float getRadius() const;
  sf::CircleShape &GetCircle() ;
  int GetSpeed() const;

private:
  sf::CircleShape m_circle;
  Figure *m_targetFig;
  int m_speed;
};