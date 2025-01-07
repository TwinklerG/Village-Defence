//
// Created by gl on 1/7/25.
//

#include "Toast.h"

namespace gl {
  float Toast::m_increment = 100;

  Toast::Toast(const sf::String &l_text, const sf::Font &l_font, const sf::Vector2f &l_windowSize): m_timeSum(0) {
    m_text = std::make_shared<sf::Text>(sf::Text(l_font, l_text, static_cast<unsigned int>(l_windowSize.y) / 30));
    m_text->setOrigin({m_text->getLocalBounds().size.x / 2, m_text->getLocalBounds().size.y / 2});
    m_text->setPosition({l_windowSize.x / 2.0f, l_windowSize.y});
    m_text->setFillColor(sf::Color::White);
    m_rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(l_windowSize.x / 5.0f, l_windowSize.y / 10.f));
    m_rect->setOrigin({m_rect->getSize().x / 2.0f, m_rect->getSize().y / 2.0f});
    m_rect->setPosition({l_windowSize.x / 2.0f, l_windowSize.y});
    m_rect->setFillColor(sf::Color(0, 0, 0, 160));
  }

  bool Toast::Update(const sf::Time &l_time) {
    m_timeSum += l_time.asSeconds();
    if (m_timeSum <= 1) {
      m_rect->setPosition({m_rect->getPosition().x, m_rect->getPosition().y - l_time.asSeconds() * m_increment});
      m_text->setPosition({m_text->getPosition().x, m_text->getPosition().y - l_time.asSeconds() * m_increment});
    } else if (m_timeSum > 1.5) {
      return true;
    }
    return false;
  }

  void Toast::Render(sf::RenderWindow &l_window) const {
    l_window.draw(*m_rect);
    l_window.draw(*m_text);
  }
}
