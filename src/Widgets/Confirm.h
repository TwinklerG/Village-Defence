#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"


namespace gl {
 enum class ConfirmType {
  CONFIRM,
  SUSPEND,
  CANCEL,
 };

 class Confirm {
 public:
  explicit Confirm(const sf::Vector2f &l_windowSize, const sf::Font &l_font);

  explicit Confirm(const sf::String &l_title, const sf::Vector2f &l_windowSize, const sf::Font &l_font);

  void OnCreate(const sf::String &l_title, const sf::Vector2f &l_windowSize, const sf::Font &l_font);

  ConfirmType UpdateRender(sf::RenderWindow &l_window) const;

 private:
  sf::RectangleShape m_back;
  std::shared_ptr<sf::Text> m_title;
  std::shared_ptr<Button> m_confirm;
  std::shared_ptr<Button> m_cancel;
  ConfirmType m_confirmType;
 };
}
