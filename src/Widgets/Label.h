#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

namespace gl {
  class Label {
  public:
    Label(const sf::Texture &l_texture, const sf::Vector2f &l_pos,
          const std::string &l_textString, unsigned int l_charSize, const sf::Font &l_font,
          const std::function<void()> &l_callback);

    void Update(const sf::RenderWindow &l_window);

    void Render(sf::RenderWindow &l_window) const;

    void SetTextString(const std::string &l_textString) const;

  private:
    std::unique_ptr<sf::Sprite> m_sprite;
    std::unique_ptr<sf::Text> m_text;

    std::function<void()> m_callBack;
    bool m_isPressed;
  };
}
