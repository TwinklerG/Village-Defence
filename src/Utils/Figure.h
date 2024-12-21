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

class Figure final : public Element {
public:
  explicit Figure(int l_tag, const sf::Sprite &, const sf::Vector2u &, const std::vector<Direction> &, int l_lives = 5,
                  int l_speed = 90, int l_reward = 10, sf::Vector2f l_atomResolution = {80, 80});

  void Render(sf::RenderWindow *l_wind) const override;

  void Update(const sf::Time &elapsed, double l_ratio = 1.0);

  std::vector<int> GetIncrements() const;

  double GetMileage() const;

  int GetLives() const;

  void SetLives(int l_lives);

  int GetReward() const;

  int GetTag() const;

private:
  sf::RectangleShape m_livesBar;
  sf::Vector2f m_atomResolution;
  std::vector<Direction> m_increments;
  double m_mileage{};
  int m_totalLives{};

  int m_lives{};
  int m_speed{};
  int m_reward{};

  int m_tag;
};
