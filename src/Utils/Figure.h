#include "Element.h"
#include <iostream>

class Figure : public Element
{
public:
  Figure();
  Figure(const sf::Sprite &, const sf::Vector2u &, const std::vector<int> &, int l_lives = 5);
  void Render(sf::RenderWindow *l_wind) const override;
  void Update(const sf::Time &elapsed);
  int GetLives();
  void SetLives(int l_lives);

private:
  std::vector<int> m_increments;
  double m_mileage;
  int m_lives;
  sf::RectangleShape m_livesBar;
};