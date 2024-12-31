#include "Element.h"

#include <utility>

Element::Element(sf::Sprite l_sp, const sf::Vector2u &l_size) : m_sprite(std::move(l_sp)), m_size(l_size) {}
Element::~Element() = default;
sf::Sprite &Element::GetSprite() { return m_sprite; }
void Element::SetSprite(const sf::Sprite &l_sp) { m_sprite = l_sp; }
void Element::Render(sf::RenderWindow *l_wind) const { l_wind->draw(m_sprite); }
sf::Vector2f Element::getPosition() const{ return m_sprite.getPosition(); }
sf::Vector2u Element::getSize()const { return m_size; }