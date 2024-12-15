#pragma once
#include <vector>
#include <memory>
#include "../Widgets/Button.h"

namespace gl {
  class Select {
  public:
    Select(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size, unsigned int l_charSize,
           const sf::Font &l_font,
           std::vector<Button> l_choices);

    Select(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size, unsigned int l_charSize,
           const sf::Font &l_font,
           const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
           const sf::Color &l_textHoverColor, std::vector<Button> l_choices);

    void OnCreate(const std::string &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                  unsigned int l_charSize,
                  const sf::Font &l_font,
                  const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                  const sf::Color &l_textHoverColor, std::vector<Button> l_choices);

    void UpdateRender(sf::RenderWindow &l_window);

  private:
    std::unique_ptr<Button> m_label;
    std::vector<Button> m_options;
    bool m_isPressed;
  };
};
