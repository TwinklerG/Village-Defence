#include "Figure.h"

Figure::Figure(const int &l_headlthPoint, const int &l_attackPoint) : m_healthPoint(l_headlthPoint), m_attackPoint(l_attackPoint) {}
Figure::~Figure() {}
sf::Sprite &Figure::GetSprite() { return m_sprite; }

Ordinary::Ordinary() : Figure(100, 10) { OnCreate(); }
Ordinary::~Ordinary() {}
void Ordinary::OnCreate()
{
  m_texture.loadFromFile("res/ordinary.png");
  m_sprite = sf::Sprite(m_texture);
  m_sprite.setPosition(0, 360);
}
void Ordinary::Update(const sf::Time &l_elapsed)
{
  if (m_sprite.getPosition().x > 1920)
  {
    m_sprite.setPosition(0, m_sprite.getPosition().y);
  }
  m_sprite.setPosition(m_sprite.getPosition().x + l_elapsed.asSeconds() * 40, m_sprite.getPosition().y);
  // if (GetSize().x + GetSprite().getPosition().x > )
}
void Ordinary::OnDestroy() {}