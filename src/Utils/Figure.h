#pragma once
#include <random>
#include <SFML/Graphics.hpp>
class Map;
class Figure
{
public:
  Figure(const int &l_headlthPoint, const int &l_attackPoint, Map* l_map);
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

  Map* m_map;
};

class Ordinary : public Figure
{
public:
  Ordinary(Map* l_map);
  ~Ordinary();
  void OnCreate() override;
  void Update(const sf::Time &l_elapsed) override;
  void OnDestroy() override;

private:
  sf::Vector2f m_increment;
};

class Guardian : public Figure
{
public:
  Guardian(Map* l_map);
  ~Guardian();
  void OnCreate() override;
  void Update(const sf::Time &l_elapsed) override;
  void OnDestroy() override;
};

class Arrow : public Figure
{
public:
  Arrow(Map* l_map);
  ~Arrow();
  void OnCreate() override;
  void Update(const sf::Time &l_elapsed) override;
  void OnDestroy() override;

private:
  sf::Vector2f m_increment;
};