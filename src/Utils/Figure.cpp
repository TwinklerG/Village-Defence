#include "Figure.h"

Figure::Figure(const int &l_headlthPoint, const int &l_attackPoint) : m_healthPoint(l_headlthPoint), m_attackPoint(l_attackPoint) {}
Figure::~Figure() {}
sf::Sprite &Figure::GetSprite() { return m_sprites[0]; }
sf::Vector2f Figure::GetPosition() { return m_position; }
void Figure::SetPosition(sf::Vector2f l_pos) { m_position = l_pos; }
void Figure::Render(sf::RenderWindow *l_wind)
{
  l_wind->draw(m_sprites[m_curSpriteIndex]);
}

Ordinary::Ordinary() : Figure(100, 10) { OnCreate(); }
Ordinary::~Ordinary() {}
void Ordinary::OnCreate()
{
  m_curSpriteIndex = 0;
  m_textures = std::vector<sf::Texture>(4);
  m_sprites = std::vector<sf::Sprite>(4);
  for (int i = 0; i < 4; ++i)
  {
    m_textures[i].loadFromFile("res/ordinary" + std::to_string(i) + ".png");
    m_sprites[i] = sf::Sprite(m_textures[i]);
    m_sprites[i].setPosition(0, 360);
  }
  m_position = sf::Vector2f(0, 360);
}
void Ordinary::Update(const sf::Time &l_elapsed)
{
  // if (m_position.x > 1920)
  // {
  //   // m_sprite.setPosition(0, m_sprite.getPosition().y);
  // }
  m_curSpriteIndex = (m_curSpriteIndex + 1) % 4;
  m_position = sf::Vector2f(m_position.x + l_elapsed.asSeconds() * 80, m_position.y);
  m_sprites[m_curSpriteIndex].setPosition(m_position);
  // m_sprite.setPosition(m_sprite.getPosition().x + l_elapsed.asSeconds() * 40, m_sprite.getPosition().y);
  // if (GetSize().x + GetSprite().getPosition().x > )
}
void Ordinary::OnDestroy() {}