#pragma once

#include <random>

namespace Utils {
  inline int RandInt(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
  }

  inline bool IsHover(const sf::RectangleShape &l_rect, const sf::RenderWindow &l_window) {
    const sf::Vector2i l_mousePos = sf::Mouse::getPosition(l_window);
    return static_cast<float>(l_mousePos.x) > l_rect.getPosition().x - l_rect.getSize().x / 2 &&
           static_cast<float>(l_mousePos.x) < l_rect.getPosition().x + l_rect.getSize().x / 2 &&
           static_cast<float>(l_mousePos.y) > l_rect.getPosition().y - l_rect.getSize().y / 2 &&
           static_cast<float>(l_mousePos.y) < l_rect.getPosition().y + l_rect.getSize().y / 2;
  }
}
