#pragma once
#include "Element.h"

enum class Direction {
  Up = 0,
  Down,
  Right,
  Left,
};

struct FigureInfo {
  int m_lives;
  int m_speed;
  int m_reward;
};

class Figure : public Element {
public:
  Figure();

  Figure(const sf::Sprite &, const sf::Vector2u &, const std::vector<Direction> &, int l_lives = 5, int l_speed = 90,
         int l_reward = 10);

  void Render(sf::RenderWindow *l_wind) const override;

  void Update(const sf::Time &elapsed);

  int GetLives() const;

  void SetLives(int l_lives);

  int GetReward() const;

private:
  sf::RectangleShape m_livesBar;
  std::vector<Direction> m_increments;
  double m_mileage{};
  int m_totalLives{};

  int m_lives{};
  int m_speed{};
  int m_reward{};
};
