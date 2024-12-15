#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
  explicit Button(const sf::Vector2f &l_pos, const sf::Vector2f &l_size, unsigned int l_charSize,
                  const sf::Font &l_font, const std::function<void()> &l_callBack);

  explicit Button(const sf::Vector2f &l_pos, const sf::Vector2f &l_size, unsigned int l_charSize,
                  const sf::Font &l_font,
                  const sf::Color &l_backColor, const sf::Color &l_textSize, const sf::Color &l_backHoverColor,
                  const sf::Color &l_textHoverColor, const std::function<void()> &l_callBack);

  void OnCreate(const sf::Vector2f &l_pos, const sf::Vector2f &l_size, unsigned int l_charSize,
                const sf::Font &l_font,
                const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                const sf::Color &l_textHoverColor,
                const std::function<void()> &l_callBack);

  void UpdateDraw(sf::RenderWindow &l_window);

private:
  sf::RectangleShape m_rect;
  sf::Text m_text;
  sf::Color m_backColor, m_textColor, m_backHoverColor, m_textHoverColor;
  std::function<void()> m_callBack;
  bool m_isPressed;
};

bool IsHover(const sf::RectangleShape &l_rect, const sf::RenderWindow &l_window);
