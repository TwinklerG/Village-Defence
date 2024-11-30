#include "Figure.h"
#include "Place.h"
#include "Map.h"
namespace Utils
{
  // Random Int Generator
  std::random_device rd;
  std::mt19937 gen(rd());
  int randint(int low, int high)
  {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
  }
}

Figure::Figure(const int &l_headlthPoint, const int &l_attackPoint, Map *l_map) : m_healthPoint(l_headlthPoint), m_attackPoint(l_attackPoint), m_map(l_map) {}
Figure::~Figure() {}
sf::Sprite &Figure::GetSprite() { return m_sprites[0]; }
sf::Vector2f Figure::GetPosition() { return m_position; }
void Figure::SetPosition(sf::Vector2f l_pos) { m_position = l_pos; }
void Figure::Render(sf::RenderWindow *l_wind)
{
  l_wind->draw(m_sprites[m_curSpriteIndex]);
}

Ordinary::Ordinary(Map *l_map) : Figure(100, 10, l_map) { OnCreate(); }
Ordinary::~Ordinary() {}
void Ordinary::OnCreate()
{
  m_increment = sf::Vector2f(Utils::randint(10, 100), 0);
  m_curSpriteIndex = 0;
  m_textures = std::vector<sf::Texture>(4);
  m_sprites = std::vector<sf::Sprite>(4);
  m_position = sf::Vector2f(0, 360 + Utils::randint(0, 8) * 80);
  for (int i = 0; i < 4; ++i)
  {
    m_textures[i].loadFromFile("res/ordinary" + std::to_string(i) + ".png");
    m_sprites[i] = sf::Sprite(m_textures[i]);
    m_sprites[i].setPosition(m_position);
  }
}
void Ordinary::Update(const sf::Time &l_elapsed)
{
  // if (m_position.x > 1920)
  // {
  //   // m_sprite.setPosition(0, m_sprite.getPosition().y);
  // }
  if (dynamic_cast<Stone *>(m_map->GetPlaces()[m_position.x / 80][(m_position.y - 360) / 80]))
  {
    return;
  }
  m_curSpriteIndex = (m_curSpriteIndex + 1) % 4;
  if (m_position.x <= m_map->GetPlaces().back().front()->GetSprite().getPosition().x)
  {
    m_position = sf::Vector2f(m_position.x + l_elapsed.asSeconds() * m_increment.x, m_position.y);
  }
  m_sprites[m_curSpriteIndex].setPosition(m_position);
  // m_sprite.setPosition(m_sprite.getPosition().x + l_elapsed.asSeconds() * 40, m_sprite.getPosition().y);
  // if (GetSize().x + GetSprite().getPosition().x > )
}
void Ordinary::OnDestroy() {}

Guardian::Guardian(Map *l_map) : Figure(100, 10, l_map) { OnCreate(); }
Guardian::~Guardian() {}
void Guardian::OnCreate()
{
  m_curSpriteIndex = 0;
  m_textures = std::vector<sf::Texture>(4);
  m_sprites = std::vector<sf::Sprite>(4);
  m_position = sf::Vector2f(1680, 360 + Utils::randint(0, 8) * 80);
  for (int i = 0; i < 4; ++i)
  {
    m_textures[i].loadFromFile("res/guardian" + std::to_string(i) + ".png");
    m_sprites[i] = sf::Sprite(m_textures[i]);
    m_sprites[i].setPosition(m_position);
  }
}
void Guardian::Update(const sf::Time &l_elapsed)
{
  m_curSpriteIndex = (m_curSpriteIndex + 1) % 4;
  if (m_curSpriteIndex == 1)
  {
    m_map = m_map->AddFigure(new Arrow(m_map));
  }
}
void Guardian::OnDestroy() {}

Arrow::Arrow(Map *l_map) : Figure(0, 10, l_map) { OnCreate(); }
Arrow::~Arrow() {}
void Arrow::OnCreate()
{
  m_curSpriteIndex = 0;
  m_position = sf::Vector2f(1680, Utils::randint(360, 1080));
  m_increment = sf::Vector2f(80, 0);
  m_textures = std::vector<sf::Texture>(1);
  m_sprites = std::vector<sf::Sprite>(1);
  m_textures[0].loadFromFile("res/arrow.png");
  m_sprites[0] = sf::Sprite(m_textures[0]);
  m_sprites[0].setPosition(m_position);
}
void Arrow::Update(const sf::Time &l_elapsed)
{
  m_position = sf::Vector2f(m_position.x - l_elapsed.asSeconds() * m_increment.x, m_position.y);
  m_sprites[0].setPosition(m_position);
}
void Arrow::OnDestroy() {}