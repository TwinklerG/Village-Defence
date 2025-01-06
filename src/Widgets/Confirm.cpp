#include "Confirm.h"

namespace gl {
  Confirm::Confirm(const sf::Vector2f &l_windowSize, const sf::Font &l_font)
    : m_confirmType(ConfirmType::SUSPEND) {
    OnCreate(L"你确定吗", l_windowSize, l_font);
  }

  Confirm::Confirm(const sf::String &l_title, const sf::Vector2f &l_windowSize, const sf::Font &l_font)
    : m_confirmType(ConfirmType::SUSPEND) {
    OnCreate(l_title, l_windowSize, l_font);
  }

  void Confirm::OnCreate(const sf::String &l_title, const sf::Vector2f &l_windowSize, const sf::Font &l_font) {
    m_back = sf::RectangleShape(sf::Vector2(l_windowSize.x, l_windowSize.y));
    m_back.setOrigin({m_back.getSize().x / 2.0f, m_back.getSize().y / 2.0f});
    m_back.setPosition({l_windowSize.x / 2.0f, l_windowSize.y / 2.0f});
    m_back.setFillColor(sf::Color::Black);
    m_title = std::make_shared<sf::Text>(l_font, l_title, l_windowSize.y / 8);
    m_title->setOrigin({m_title->getLocalBounds().size.x / 2.0f, m_title->getLocalBounds().size.y / 2.0f});
    m_title->setPosition({l_windowSize.x / 2.0f, l_windowSize.y / 3.0f});
    m_title->setFillColor(sf::Color::White);
    const auto l_buttonSize = sf::Vector2f(l_windowSize.x / 4.0f, l_windowSize.y / 4.0f);
    m_confirm = std::make_shared<gl::Button>(
      L"确认", sf::Vector2f(l_windowSize.x / 4.0f, l_windowSize.y / 3.0f * 2.0f),
      l_buttonSize, l_windowSize.y / 10, l_font, [this]() {
        m_confirmType = ConfirmType::CONFIRM;
      });
    m_cancel = std::make_shared<gl::Button>(
      L"取消", sf::Vector2f(l_windowSize.x / 4.0f * 3.0f, l_windowSize.y / 3.0f * 2.0f),
      l_buttonSize, l_windowSize.y / 10, l_font, [this]() {
        m_confirmType = ConfirmType::CANCEL;
      });
  }

  ConfirmType Confirm::UpdateRender(sf::RenderWindow &l_window) const {
    l_window.draw(m_back);
    l_window.draw(*m_title);
    m_confirm->UpdateRender(l_window);
    m_cancel->UpdateRender(l_window);
    return m_confirmType;
  }
}
