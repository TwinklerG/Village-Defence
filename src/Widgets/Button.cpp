#include "Button.h"
#include "../Utils/Utils.hpp"

namespace gl {
  Button::Button(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                 const unsigned int l_charSize,
                 const sf::Font &l_font,
                 const std::function<void()> &l_callBack): m_isPressed(true) {
    OnCreate(l_text, l_pos, l_size, l_charSize, l_font, sf::Color::Red, sf::Color::White, sf::Color::White,
             sf::Color::Black,
             l_callBack);
  }

  Button::Button(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                 const unsigned int l_charSize, const sf::Font &l_font,
                 const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                 const sf::Color &l_textHoverColor, const std::function<void()> &l_callBack)
    : m_isPressed(true) {
    OnCreate(l_text, l_pos, l_size, l_charSize, l_font, l_backColor, l_textColor, l_backHoverColor, l_textHoverColor,
             l_callBack);
  }

  void Button::OnCreate(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                        const unsigned int l_charSize,
                        const sf::Font &l_font,
                        const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                        const sf::Color &l_textHoverColor, const std::function<void()> &l_callBack) {
    // Back Rectangle
    m_rect = sf::RectangleShape(l_size);
    m_rect.setOrigin(m_rect.getSize().x / 2, m_rect.getSize().y / 2);
    m_rect.setPosition(l_pos);
    m_rect.setFillColor(l_backColor);
    // Text
    m_text.setString(l_text);
    m_text.setFont(l_font);
    m_text.setCharacterSize(l_charSize);
    const sf::FloatRect rect = m_text.getLocalBounds();
    m_text.setOrigin(rect.left + m_text.getLocalBounds().width / 2.0f
                     , rect.top + m_text.getLocalBounds().height / 2.0f);
    m_text.setPosition(l_pos);
    m_text.setFillColor(l_backColor);
    // Color
    m_backColor = l_backColor;
    m_backHoverColor = l_backHoverColor;
    m_textColor = l_textColor;
    m_textHoverColor = l_textHoverColor;
    // CallBack
    m_callBack = l_callBack;
  }

  bool Button::UpdateRender(sf::RenderWindow &l_window) {
    bool ret = false;
    if (gl::IsHover(m_rect, l_window)) {
      m_rect.setFillColor(m_backHoverColor);
      m_text.setFillColor(m_textHoverColor);
      if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_isPressed = false;
      } else if (!m_isPressed) {
        m_callBack(); // Call Back
        m_isPressed = true;
        ret = true;
      }
    } else {
      m_rect.setFillColor(m_backColor);
      m_text.setFillColor(m_textColor);
    }
    l_window.draw(m_rect);
    l_window.draw(m_text);
    return ret;
  }

  const sf::RectangleShape &Button::GetRectangleShape() const {
    return m_rect;
  }

  sf::Text Button::GetText() const {
    return m_text;
  }

  void Button::SetText(const sf::Text &l_text) {
    m_text = l_text;
  }
};
