#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace gl {
  class Button {
  public:
    explicit Button(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                    unsigned int l_charSize,
                    const sf::Font &l_font, const std::function<void()> &l_callBack);

    explicit Button(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                    unsigned int l_charSize,
                    const sf::Font &l_font,
                    const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                    const sf::Color &l_textHoverColor, const std::function<void()> &l_callBack);

    void OnCreate(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                  unsigned int l_charSize,
                  const sf::Font &l_font,
                  const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                  const sf::Color &l_textHoverColor,
                  const std::function<void()> &l_callBack);

    bool UpdateRender(sf::RenderWindow &l_window);

    const sf::RectangleShape &GetRectangleShape() const;

  private:
    sf::RectangleShape m_rect;
    sf::Text m_text;
    sf::Color m_backColor, m_textColor, m_backHoverColor, m_textHoverColor;
    std::function<void()> m_callBack;
    bool m_isPressed;
  };
};
