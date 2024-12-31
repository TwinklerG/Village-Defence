#include "TextBox.h"

#include <nlohmann/json.hpp>
#include <utility>

namespace gl {
  TextBox::TextBox(const sf::Vector2f &l_pos, const sf::Vector2f &l_size, const int l_max, sf::Font l_font)
    : m_font(std::move(l_font)), m_max(l_max) {
    m_backup = sf::RectangleShape(l_size);
    m_backup.setOrigin({m_backup.getSize().x / 2.0f, m_backup.getSize().y / 2.0f});
    m_backup.setPosition(l_pos);
    m_backup.setFillColor(sf::Color(0, 0, 0, 50));
  }

  TextBox::TextBox(const sf::Vector2f &l_pos, const sf::Vector2f &l_size, const int l_max, sf::Font l_font,
                   const std::vector<std::string> &l_messages)
    : m_font(std::move(l_font)), m_max(l_max) {
    m_backup = sf::RectangleShape(l_size);
    m_backup.setOrigin({m_backup.getSize().x / 2.0f, m_backup.getSize().y / 2.0f});
    m_backup.setPosition(l_pos);
    m_backup.setFillColor(sf::Color(0, 0, 0, 50));
    for (const auto &l_message: l_messages) {
      AddText(l_message);
    }
  }

  void TextBox::AddText(const std::string &l_textString) {
    if (m_texts.size() == m_max) {
      for (int i = static_cast<int>(m_texts.size()) - 1; i > 0; --i) {
        m_texts[i].setPosition(m_texts[i - 1].getPosition());
      }
      m_texts.erase(m_texts.begin());
    }
    sf::Text l_text(m_font, l_textString,
                    static_cast<unsigned int>(m_backup.getSize().y / static_cast<float>(m_max + 1) * 0.9f));
    const auto l_lcb = l_text.getLocalBounds();
    l_text.setOrigin({l_lcb.position.x + l_lcb.size.x / 2.0f, l_lcb.position.y + l_lcb.size.y / 2.0f});
    l_text.setPosition({
      m_backup.getPosition().x,
      m_backup.getPosition().y - m_backup.getSize().y / 2.0f +
      m_backup.getSize().y / static_cast<float>(m_max + 1) * static_cast<float>(
        1 + 1 * m_texts.size())
    });
    m_texts.push_back(l_text);
  }

  void TextBox::Render(sf::RenderWindow &l_window) const {
    l_window.draw(m_backup);
    for (const auto &l_text: m_texts) {
      l_window.draw(l_text);
    }
  }

  std::vector<std::string> TextBox::GetMessages() const {
    std::vector<std::string> ret(m_texts.size());
    for (size_t i = 0; i < m_texts.size(); ++i) {
      ret[i] = m_texts[i].getString();
    }
    return ret;
  }
}
