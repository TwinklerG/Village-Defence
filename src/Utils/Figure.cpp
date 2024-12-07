#include "Figure.h"

Figure::Figure() {}
Figure::Figure(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::vector<Direction> &l_increments, int l_lives, int l_speed)
    : Element(l_sp, l_size),
      m_mileage(0),
      m_increments(l_increments),
      m_lives(l_lives),
      m_totalLives(l_lives),
      m_speed(l_speed)
{
  m_livesBar = sf::RectangleShape(sf::Vector2f(m_size.x, 10));
  m_livesBar.setPosition(getPosition().x - m_size.x / 2, getPosition().y - m_size.y / 2);
  m_livesBar.setFillColor(sf::Color::Red);
}
void Figure::Render(sf::RenderWindow *l_wind) const
{
  l_wind->draw(m_sprite);
  l_wind->draw(m_livesBar);
}
void Figure::Update(const sf::Time &elapsed)
{
  if (m_mileage / 90 >= m_increments.size())
  {
    return;
  }
  switch (m_increments[m_mileage / 90])
  {
  case Direction::Right:
    m_sprite.setPosition(m_sprite.getPosition().x + elapsed.asSeconds() * 90, m_sprite.getPosition().y);
    m_livesBar.setPosition(m_livesBar.getPosition().x + elapsed.asSeconds() * 90, m_livesBar.getPosition().y);
    break;
  case Direction::Down:
    m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + elapsed.asSeconds() * 90);
    m_livesBar.setPosition(m_livesBar.getPosition().x, m_livesBar.getPosition().y + elapsed.asSeconds() * 90);
    break;
  case Direction::Left:
    m_sprite.setPosition(m_sprite.getPosition().x - elapsed.asSeconds() * 90, m_sprite.getPosition().y);
    m_livesBar.setPosition(m_livesBar.getPosition().x - elapsed.asSeconds() * 90, m_livesBar.getPosition().y);
    break;
  case Direction::Up:
    m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - elapsed.asSeconds() * 90);
    m_livesBar.setPosition(m_livesBar.getPosition().x, m_livesBar.getPosition().y - elapsed.asSeconds() * 90);
  default:
    break;
  }
  m_mileage += elapsed.asSeconds() * 90;
}
int Figure::GetLives() { return m_lives; }
void Figure::SetLives(int l_lives)
{
  m_lives = l_lives;
  m_livesBar.setSize(sf::Vector2f(m_size.x * (double)m_lives / (double)m_totalLives, 10));
}