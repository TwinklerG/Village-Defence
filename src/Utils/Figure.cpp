#include "Figure.h"

enum class Direction
{
  Right = 0,
  Down = 1,
  Left = 2,
  Up = 3,
};

Figure::Figure() {}
Figure::Figure(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::vector<int> &l_increments) : Element(l_sp, l_size), m_mileage(0), m_increments(l_increments) {}
void Figure::Update(const sf::Time &elapsed)
{
  if (m_mileage / 90 >= m_increments.size())
  {
    return;
  }
  switch (m_increments[m_mileage / 90])
  {
  case 0:
    m_sprite.setPosition(m_sprite.getPosition().x + elapsed.asSeconds() * 90, m_sprite.getPosition().y);
    break;
  case 1:
    m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + elapsed.asSeconds() * 90);
    break;
  case 2:
    m_sprite.setPosition(m_sprite.getPosition().x - elapsed.asSeconds() * 90, m_sprite.getPosition().y);
    break;
  case 3:
    m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + elapsed.asSeconds() * 90);
  default:
    break;
  }
  m_mileage += elapsed.asSeconds() * 90;
}