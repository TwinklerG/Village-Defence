#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Figure.h"

class Bullet {
public:
  Bullet();

  Bullet(sf::CircleShape l_circle, std::shared_ptr<Figure> l_targetFig, int = 180, int = 1);

  ~Bullet();

  std::shared_ptr<Figure> GetTargetFigure();

  sf::Vector2f getPosition() const;

  float getRadius() const;

  sf::CircleShape &GetCircle();

  int GetSpeed() const;

  int GetAtk() const;

  std::shared_ptr<Figure> GetTargetFigure() const;

  std::vector<int> GetRgba() const;

private:
  sf::CircleShape m_circle;
  std::shared_ptr<Figure> m_targetFig;
  int m_speed{};
  int m_attackPoint{};
};
