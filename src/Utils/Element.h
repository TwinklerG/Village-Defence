#pragma once
#include <SFML/Graphics.hpp>
class Element
{
public:
  Element();
  Element(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  ~Element();
  sf::Sprite &GetSprite();
  void SetSprite(const sf::Sprite &l_sp);
  virtual void Render(sf::RenderWindow *l_wind) const;
  const sf::Vector2f &getPosition();
  const sf::Vector2u &getSize();

protected:
  sf::Sprite m_sprite;
  sf::Vector2u m_size;
};