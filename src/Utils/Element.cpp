#include "Element.h"

Element::Element() {}
Element::Element(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : m_sprite(l_sp), m_size(l_size) {}
Element::~Element() {}
sf::Sprite &Element::GetSprite() { return m_sprite; }
void Element::SetSprite(const sf::Sprite &l_sp) { m_sprite = l_sp; }
void Element::Render(sf::RenderWindow *l_wind) const { l_wind->draw(m_sprite); }
const sf::Vector2f &Element::getPosition() { return m_sprite.getPosition(); }
const sf::Vector2u &Element::getSize() { return m_size; }