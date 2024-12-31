#pragma once

#include <random>

namespace gl {
  /**
   *
   * @param min
   * @param max
   * @return random Integer in [min, max]
   */
  inline int RandInt(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
  }

  /**
   *
   * @param l_rect Rectangle Shape
   * @param l_window RenderWindow
   * @return whether Mouse is hovering on the Rectangle
   */
  inline bool IsHover(const sf::RectangleShape &l_rect, const sf::RenderWindow &l_window) {
    const sf::Vector2i l_mousePos = sf::Mouse::getPosition(l_window);
    return static_cast<float>(l_mousePos.x) > l_rect.getPosition().x - l_rect.getSize().x / 2.0f &&
           static_cast<float>(l_mousePos.x) < l_rect.getPosition().x + l_rect.getSize().x / 2.0f &&
           static_cast<float>(l_mousePos.y) > l_rect.getPosition().y - l_rect.getSize().y / 2.0f &&
           static_cast<float>(l_mousePos.y) < l_rect.getPosition().y + l_rect.getSize().y / 2.0f;
  }

  /**
   *
   * @param l_sprite Sprite
   * @param l_window RenderWindow
   * @return whether Mouse is hovering on the Sprite
   */
  inline bool IsHover(const sf::Sprite &l_sprite, const sf::RenderWindow &l_window) {
    const sf::Vector2i l_mousePos = sf::Mouse::getPosition(l_window);
    return static_cast<float>(l_mousePos.x) > l_sprite.getPosition().x - static_cast<float>(l_sprite.getTexture().
             getSize()
             .x) / 2.0f &&
           static_cast<float>(l_mousePos.x) < l_sprite.getPosition().x + static_cast<float>(l_sprite.getTexture().
             getSize()
             .x) / 2.0f &&
           static_cast<float>(l_mousePos.y) > l_sprite.getPosition().y - static_cast<float>(l_sprite.getTexture().
             getSize()
             .y) / 2.0f &&
           static_cast<float>(l_mousePos.y) < l_sprite.getPosition().y + static_cast<float>(l_sprite.getTexture().
             getSize()
             .y) / 2.0f;
  }

  /**
   *
   * @tparam T
   * @param target
   * @param l_wind
   * @return whether Mouse in the range of target
   */
  template<class T>
  bool checkMouseSelect(const T &target, sf::RenderWindow *l_wind) {
    return target.getPosition().x - target.getSize().x / 2.0 <= sf::Mouse::getPosition(*l_wind).x &&
           target.getPosition().x + target.getSize().x / 2.0 >= sf::Mouse::getPosition(*l_wind).x &&
           target.getPosition().y - target.getSize().y / 2.0 <= sf::Mouse::getPosition(*l_wind).y &&
           target.getPosition().y + target.getSize().y / 2.0 >= sf::Mouse::getPosition(*l_wind).y;
  }

  /**
   *
   * @param l_sprite
   * @param l_wind
   * @return whether Mouse selects Sprite
   */
  inline bool checkMouseSelectSprite(const sf::Sprite &l_sprite, const sf::RenderWindow *l_wind) {
    return l_sprite.getPosition().x - l_sprite.getTexture().getSize().x / 2.0 <= sf::Mouse::getPosition(*l_wind).x &&
           l_sprite.getPosition().x + l_sprite.getTexture().getSize().x / 2.0 >= sf::Mouse::getPosition(*l_wind).x &&
           l_sprite.getPosition().y - l_sprite.getTexture().getSize().y / 2.0 <= sf::Mouse::getPosition(*l_wind).y &&
           l_sprite.getPosition().y + l_sprite.getTexture().getSize().y / 2.0 >= sf::Mouse::getPosition(*l_wind).y;
  }

  /**
   *
   * @tparam T
   * @tparam F
   * @param source
   * @param target
   * @param range
   * @return whether target in the range of source
   */
  template<class T, class F>
  bool checkInRange(const T &source, const F &target, const double range) {
    return (source.getPosition().x - target.getPosition().x) * (source.getPosition().x - target.getPosition().x) + (
             source.getPosition().y - target.getPosition().y) * (source.getPosition().y - target.getPosition().y) <=
           range * range;
  }

  /**
   *
   * @tparam F sf::Texture sf::Rectangle
   * @param source circle shape of Bullet
   * @param target
   * @return whether collision happens between source and target
   */
  template<class F>
  bool checkCollision(const sf::CircleShape &source, const F &target) {
    return (source.getPosition().x - target.getPosition().x) * (source.getPosition().x - target.getPosition().x) + (
             source.getPosition().y - target.getPosition().y) * (source.getPosition().y - target.getPosition().y) <= (
             source.getRadius() + target.getSize().x) * (source.getRadius() + target.getSize().x) / 8 + (
             source.getRadius() + target.getSize().y) * (source.getRadius() + target.getSize().y) / 8;
  }
}
