#include "Bullet.h"

Bullet::Bullet() {}
Bullet::Bullet(const sf::CircleShape &l_circle, Figure *l_targetFig, int l_speed)
    : m_circle(l_circle),
      m_targetFig(l_targetFig),
      m_speed(l_speed) {}
Bullet::~Bullet() {}
Figure *Bullet::GetTargetFigure() { return m_targetFig; }
const sf::Vector2f Bullet::getPosition() const { return m_circle.getPosition(); }
float Bullet::getRadius() const { return m_circle.getRadius(); }
sf::CircleShape &Bullet::GetCircle() { return m_circle; }
int Bullet::GetSpeed() const { return m_speed; }