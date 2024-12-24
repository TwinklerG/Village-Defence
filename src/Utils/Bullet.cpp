#include "Bullet.h"

#include <utility>

Bullet::Bullet() = default;

Bullet::Bullet(sf::CircleShape l_circle, std::shared_ptr<Figure> l_targetFig, const int l_speed,
               const int l_attackPoint)
  : m_circle(std::move(l_circle)),
    m_targetFig(std::move(l_targetFig)),
    m_speed(l_speed),
    m_attackPoint(l_attackPoint) {
}

Bullet::~Bullet() = default;

std::shared_ptr<Figure> Bullet::GetTargetFigure() { return m_targetFig; }

sf::Vector2f Bullet::getPosition() const { return m_circle.getPosition(); }

float Bullet::getRadius() const { return m_circle.getRadius(); }

sf::CircleShape &Bullet::GetCircle() { return m_circle; }

int Bullet::GetSpeed() const { return m_speed; }

int Bullet::GetAtk() const { return m_attackPoint; }

std::shared_ptr<Figure> Bullet::GetTargetFigure() const {
  return m_targetFig;
}

std::vector<int> Bullet::GetRgba() const {
  return {m_circle.getFillColor().r, m_circle.getFillColor().g, m_circle.getFillColor().b, m_circle.getFillColor().a};
}
