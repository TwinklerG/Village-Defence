#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace gl {
  class Button {
  public:
    explicit Button(const sf::String &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                    unsigned int l_charSize,
                    const sf::Font &l_font, const std::function<void()> &l_callBack);

    explicit Button(const sf::String &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                    unsigned int l_charSize,
                    const sf::Font &l_font,
                    const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                    const sf::Color &l_textHoverColor, const std::function<void()> &l_callBack);

    void OnCreate(const sf::String &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                  unsigned int l_charSize,
                  const sf::Font &l_font,
                  const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                  const sf::Color &l_textHoverColor,
                  const std::function<void()> &l_callBack);

    bool UpdateRender(sf::RenderWindow &l_window);

    const sf::RectangleShape &GetRectangleShape() const;

    sf::Text GetText() const;

    void SetText(const sf::Text &l_text);

    sf::Vector2f GetPosition() const;

    void SetPosition(const sf::Vector2f &l_pos);

    sf::Vector2f GetSize() const;

    unsigned int GetCharSize() const;

    void SetIsPressed(bool l_isPressed);

    void SetCallBack(const std::function<void()> &l_callBack);

  private:
    sf::RectangleShape m_rect;
    std::shared_ptr<sf::Text> m_text;
    sf::Color m_backColor, m_textColor, m_backHoverColor, m_textHoverColor;
    std::function<void()> m_callBack;
    bool m_isPressed;
  };
};
