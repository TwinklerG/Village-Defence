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

  sf::Sprite &GetSprite();

protected:
  sf::Texture m_texture;
  sf::Sprite m_sprite;
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