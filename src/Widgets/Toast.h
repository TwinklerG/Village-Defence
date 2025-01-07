#pragma once
#include <SFML/Graphics.hpp>

namespace gl {
  class Toast {
  public:
    explicit Toast(const sf::String &l_text, const sf::Font &l_font, const sf::Vector2f &l_windowSize);

    bool Update(const sf::Time &l_time);

    void Render(sf::RenderWindow &l_window) const;

  private:
    std::shared_ptr<sf::RectangleShape> m_rect;
    std::shared_ptr<sf::Text> m_text;
    float m_timeSum;

    static float m_increment;
    static float m_elapsedSum;
  };
}
