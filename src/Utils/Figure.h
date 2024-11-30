#pragma once
#include <SFML/Graphics.hpp>
class Figure
{
public:
  Figure(const int &l_headlthPoint, const int &l_attackPoint);
  ~Figure();
  virtual void OnCreate() = 0;
  virtual void Update(const sf::Time &l_elapsed) = 0;
  virtual void OnDestroy() = 0;
  virtual void Render(sf::RenderWindow *l_wind);

  sf::Sprite &GetSprite();
  sf::Vector2f GetPosition();
  void SetPosition(sf::Vector2f l_pos);

protected:
  std::vector<sf::Texture> m_textures;
  std::vector<sf::Sprite> m_sprites;
  int m_curSpriteIndex;
  sf::Vector2f m_position;
  int m_healthPoint;
  int m_attackPoint;
};

class Ordinary : public Figure
{
public:
  Ordinary();
  ~Ordinary();
  void OnCreate() override;
  void Update(const sf::Time &l_elapsed) override;
  void OnDestroy() override;

private:
  sf::Vector2f m_increment;
};