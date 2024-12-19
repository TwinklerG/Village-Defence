#pragma once
#include <SFML/Graphics.hpp>

namespace gl {
  class TextBox {
  public:
    explicit TextBox(const sf::Vector2f &l_pos, const sf::Vector2f &l_size, int l_max, const sf::Font &l_font);

    void AddText(const std::string &l_textString);

    void Render(sf::RenderWindow &l_window) const;

  private:
    sf::RectangleShape m_backup;
    std::vector<sf::Text> m_texts;

    const sf::Font m_font;
    const int m_max;
  };
}
