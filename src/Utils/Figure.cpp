#include "Figure.h"

#include <algorithm>

#include "Utils.hpp"

Figure::Figure(const int l_tag, const sf::Sprite &l_sp,
               const sf::Vector2u &l_size,
               const std::vector<Direction> &l_increments, const int l_lives,
               const int l_speed, const int l_reward,
               const sf::Vector2f l_atomResolution)
    : Element(l_sp, l_size), m_atomResolution(l_atomResolution),
      m_increments(l_increments), m_totalLives(l_lives), m_lives(l_lives),
      m_speed(l_speed), m_reward(l_reward), m_tag(l_tag) {
  m_livesBar =
      sf::RectangleShape(sf::Vector2f(static_cast<float>(m_size.x), 10));
  m_livesBar.setPosition({static_cast<float>(getPosition().x - m_size.x / 2.0),
                          static_cast<float>(getPosition().y - m_size.y / 2.0 +
                                             gl::RandInt(-5, 5))});
  m_livesBar.setOutlineColor(sf::Color::Black);
  m_livesBar.setOutlineThickness(2.0f);
  m_livesBar.setFillColor(sf::Color::Red);
}

void Figure::Render(sf::RenderWindow *l_wind) const {
  l_wind->draw(m_sprite);
  l_wind->draw(m_livesBar);
}

void Figure::Update(const sf::Time &elapsed, const double l_ratio) {
  if (m_mileage / m_atomResolution.x >=
      static_cast<double>(m_increments.size())) {
    return;
  }
  const float delta = elapsed.asSeconds() * static_cast<float>(m_speed) *
                      static_cast<float>(l_ratio) * m_atomResolution.x / 8;
  switch (
      m_increments[static_cast<long long>(m_mileage / m_atomResolution.x)]) {
  case Direction::Right:
    m_sprite.setPosition(
        {m_sprite.getPosition().x + delta, m_sprite.getPosition().y});
    m_livesBar.setPosition(
        {m_livesBar.getPosition().x + delta, m_livesBar.getPosition().y});
    break;
  case Direction::Down:
    m_sprite.setPosition(
        {m_sprite.getPosition().x, m_sprite.getPosition().y + delta});
    m_livesBar.setPosition(
        {m_livesBar.getPosition().x, m_livesBar.getPosition().y + delta});
    break;
  case Direction::Left:
    m_sprite.setPosition(
        {m_sprite.getPosition().x - delta, m_sprite.getPosition().y});
    m_livesBar.setPosition(
        {m_livesBar.getPosition().x - delta, m_livesBar.getPosition().y});
    break;
  case Direction::Up:
    m_sprite.setPosition(
        {m_sprite.getPosition().x, m_sprite.getPosition().y - delta});
    m_livesBar.setPosition(
        {m_livesBar.getPosition().x, m_livesBar.getPosition().y - delta});
  default:
    break;
  }
  m_mileage += delta;
}

std::vector<int> Figure::GetIncrements() const {
  std::vector<int> ret;
  std::transform(m_increments.begin(), m_increments.end(),
                 std::back_inserter(ret),
                 [](const Direction d) { return static_cast<int>(d); });
  return ret;
}

double Figure::GetMileage() const { return m_mileage; }

void Figure::SetMileage(const double l_mileage) { m_mileage = l_mileage; }

int Figure::GetLives() const { return m_lives; }

void Figure::SetLives(const int l_lives) {
  m_lives = l_lives;
  m_livesBar.setSize(
      sf::Vector2f(static_cast<float>(m_size.x * m_lives /
                                      static_cast<double>(m_totalLives)),
                   10));
}

int Figure::GetReward() const { return m_reward; }

int Figure::GetTag() const { return m_tag; }

int Figure::GetSpeed() const { return m_speed; }
