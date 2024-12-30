#include "Select.h"
#include "../Utils/Utils.hpp"

namespace gl {
  Select::Select(const sf::String &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                 const unsigned int l_charSize, const sf::Font &l_font,
                 std::vector<Button> l_choices)
    : m_isPressed(false) {
    OnCreate(l_text, l_pos, l_size, l_charSize, l_font, sf::Color::Red, sf::Color::White, sf::Color::White,
             sf::Color::Black,
             std::move(l_choices));
  }

  Select::Select(const sf::String &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                 const unsigned int l_charSize, const sf::Font &l_font,
                 const sf::Color &l_backColor, const sf::Color &l_textColor, const sf::Color &l_backHoverColor,
                 const sf::Color &l_textHoverColor, std::vector<Button> l_choices)
    : m_isPressed(false) {
    OnCreate(l_text, l_pos, l_size, l_charSize, l_font, l_backColor, l_textColor, l_backHoverColor, l_textHoverColor,
             std::move(l_choices));
  }

  void Select::OnCreate(const sf::String &l_text, const sf::Vector2f &l_pos, const sf::Vector2f &l_size,
                        unsigned int l_charSize,
                        const sf::Font &l_font, const sf::Color &l_backColor, const sf::Color &l_textColor,
                        const sf::Color &l_backHoverColor, const sf::Color &l_textHoverColor,
                        std::vector<Button> l_choices) {
    m_label = std::make_unique<Button>(l_text, l_pos, l_size, l_charSize, l_font, l_backColor, l_textColor,
                                       l_backHoverColor,
                                       l_textHoverColor, [this]() {
                                         this->m_isPressed = !this->m_isPressed;
                                       });
    m_options = std::move(l_choices);
  }

  void Select::UpdateRender(sf::RenderWindow &l_window) {
    m_label->UpdateRender(l_window);
    if (m_isPressed) {
      for (auto &option: m_options) {
        if (option.UpdateRender(l_window)) {
          this->m_isPressed = !this->m_isPressed;
          break;
        }
      }
    }
  }
};
