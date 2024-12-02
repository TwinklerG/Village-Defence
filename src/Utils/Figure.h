#include "Element.h"

class Figure : public Element
{
public:
  Figure();
  Figure(const sf::Sprite &, const sf::Vector2u &, const std::vector<int>&);
  void Update(const sf::Time& elapsed);

private:
  std::vector<int> m_increments;
  double m_mileage;
};