#include "Label.h"

namespace gl {
  Label::Label(const sf::Texture &l_texture, const sf::Vector2f &l_pos,
               const std::string &l_textString, const unsigned int l_charSize, const sf::Font &l_font,
               const std::function<void()> &l_callback)
    : m_isPressed(true) {
    m_sprite.setTexture(l_texture);
    m_sprite.setOrigin(static_cast<float>(l_texture.getSize().x) / 2.0f,
                       static_cast<float>(l_texture.getSize().y) / 2.0f);
    m_sprite.setPosition(l_pos);
    m_text.setFont(l_font);
    m_text.setCharacterSize(l_charSize);
    m_text.setString(l_textString);
    const auto l_lb = m_text.getLocalBounds();
    m_text.setOrigin(l_lb.left + l_lb.width / 2.0f, l_lb.top + l_lb.height / 2.0f);
    m_text.setPosition(m_sprite.getPosition().x,
                       m_sprite.getPosition().y + static_cast<float>(l_texture.getSize().y) / 2.0f + m_text.
                       getLocalBounds().height / 2.0f);
    m_callBack = l_callback;
  }

  void Label::Update(const sf::RenderWindow &l_window) {
    if (Utils::IsHover(m_sprite, l_window)) {
      if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_isPressed = false;
      } else if (!m_isPressed) {
        m_callBack(); // Call Back
        m_isPressed = true;
      }
    }
  }

  void Label::Render(sf::RenderWindow &l_window) const {
    l_window.draw(m_sprite);
    l_window.draw(m_text);
  }
}
