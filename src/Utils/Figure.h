#pragma once
#include "Element.h"
#include <iostream>

enum class Direction
{
  Up = 0,
  Down,
  Right,
  Left,
};

class Figure : public Element
{
public:
  Figure();
  Figure(const sf::Sprite &, const sf::Vector2u &, const std::vector<Direction> &, int l_lives = 5, int l_speed = 90);
  void Render(sf::RenderWindow *l_wind) const override;
  void Update(const sf::Time &elapsed);
  int GetLives();
  void SetLives(int l_lives);

private:
  std::vector<Direction> m_increments;
  double m_mileage;
  int m_lives;
  int m_totalLives;
  int m_speed;
  sf::RectangleShape m_livesBar;
};