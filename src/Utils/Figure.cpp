#include "Figure.h"
#include "Utils.hpp"

Figure::Figure() = default;

Figure::Figure(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::vector<Direction> &l_increments,
               const int l_lives, const int l_speed, const int l_reward)
  : Element(l_sp, l_size),
    m_increments(l_increments),
    m_totalLives(l_lives),
    m_lives(l_lives),
    m_speed(l_speed),
    m_reward(l_reward) {
  m_livesBar = sf::RectangleShape(sf::Vector2f(static_cast<float>(m_size.x), 10));
  m_livesBar.setPosition(static_cast<float>(getPosition().x - m_size.x / 2.0),
                         static_cast<float>(getPosition().y - m_size.y / 2.0 + Utils::RandInt(-5, 5)));
  m_livesBar.setOutlineColor(sf::Color::Black);
  m_livesBar.setOutlineThickness(2.0f);
  m_livesBar.setFillColor(sf::Color::Red);
}

void Figure::Render(sf::RenderWindow *l_wind) const {
  l_wind->draw(m_sprite);
  l_wind->draw(m_livesBar);
}

void Figure::Update(const sf::Time &elapsed) {
  if (m_mileage / 90 >= static_cast<double>(m_increments.size())) {
    return;
  }
  switch (m_increments[static_cast<long long>(m_mileage / 90)]) {
    case Direction::Right:
      m_sprite.setPosition(m_sprite.getPosition().x + elapsed.asSeconds() * static_cast<float>(m_speed), m_sprite.getPosition().y);
      m_livesBar.setPosition(m_livesBar.getPosition().x + elapsed.asSeconds() * static_cast<float>(m_speed), m_livesBar.getPosition().y);
      break;
    case Direction::Down:
      m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y + elapsed.asSeconds() * static_cast<float>(m_speed));
      m_livesBar.setPosition(m_livesBar.getPosition().x, m_livesBar.getPosition().y + elapsed.asSeconds() * static_cast<float>(m_speed));
      break;
    case Direction::Left:
      m_sprite.setPosition(m_sprite.getPosition().x - elapsed.asSeconds() * static_cast<float>(m_speed), m_sprite.getPosition().y);
      m_livesBar.setPosition(m_livesBar.getPosition().x - elapsed.asSeconds() * static_cast<float>(m_speed), m_livesBar.getPosition().y);
      break;
    case Direction::Up:
      m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - elapsed.asSeconds() * static_cast<float>(m_speed));
      m_livesBar.setPosition(m_livesBar.getPosition().x, m_livesBar.getPosition().y - elapsed.asSeconds() * static_cast<float>(m_speed));
    default:
      break;
  }
  m_mileage += elapsed.asSeconds() * static_cast<float>(m_speed);
}

int Figure::GetLives() const { return m_lives; }

void Figure::SetLives(const int l_lives) {
  m_lives = l_lives;
  m_livesBar.setSize(sf::Vector2f(static_cast<float>(m_size.x * m_lives / static_cast<double>(m_totalLives)), 10));
}

int Figure::GetReward() const { return m_reward; }
