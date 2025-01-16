#include "Label.h"
#include "../Utils/Utils.hpp"

namespace gl {
  Label::Label(const sf::Texture &l_texture, const sf::Vector2f &l_pos,
               const std::string &l_textString, const unsigned int l_charSize, const sf::Font &l_font,
               const std::function<void()> &l_callback)
    : m_isPressed(true) {
    m_sprite = std::make_unique<sf::Sprite>(l_texture);
    m_sprite->setOrigin({
      static_cast<float>(l_texture.getSize().x) / 2.0f,
      static_cast<float>(l_texture.getSize().y) / 2.0f
    });
    m_sprite->setPosition(l_pos);
    m_text = std::make_unique<sf::Text>(l_font, l_textString, l_charSize);
    const auto l_lb = m_text->getLocalBounds();
    m_text->setOrigin({l_lb.position.x + l_lb.size.x / 2.0f, l_lb.position.y + l_lb.size.y / 2.0f});
    m_text->setPosition({
      m_sprite->getPosition().x,
      m_sprite->getPosition().y + static_cast<float>(l_texture.getSize().y) / 2.0f + m_text->getLocalBounds().size.y /
      2.0f
    });
    m_callBack = l_callback;
  }

  void Label::Update(const sf::RenderWindow &l_window) {
    if (gl::IsHover(*m_sprite, l_window)) {
      if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        m_isPressed = false;
      } else if (!m_isPressed) {
        m_callBack(); // Call Back
        m_isPressed = true;
      }
    }
  }

  void Label::Render(sf::RenderWindow &l_window) const {
    l_window.draw(*m_sprite);
    l_window.draw(*m_text);
  }

  void Label::SetTextString(const std::string &l_textString) const {
    m_text->setString(l_textString);
  }
}
