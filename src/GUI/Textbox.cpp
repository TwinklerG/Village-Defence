#include "Textbox.h"

Textbox::Textbox() { Setup(5, 9, 200, sf::Vector2f(0, 0)); }
Textbox::Textbox(const int l_visible, const int l_charSize, const int l_width, const sf::Vector2f &l_screenPos) { Setup(l_visible, l_charSize, l_width, l_screenPos); }
Textbox::~Textbox() { Clear(); }

void Textbox::Setup(const int l_visible, const int l_charSize, const int l_width, const sf::Vector2f &l_screenPos)
{
  m_numVisible = l_visible;

  const sf::Vector2f l_offset(0.2f, 0.2f);

  m_font.loadFromFile("res/fonts/arial.ttf");
  m_content.setFont(m_font);
  m_content.setString("");
  m_content.setCharacterSize(l_charSize);
  m_content.setFillColor(sf::Color::White);
  m_content.setPosition(sf::Vector2f(l_screenPos.x + l_offset.x - static_cast<float>(l_width), l_offset.y));

  m_backup.setOrigin(static_cast<float>(l_width), 0);
  m_backup.setSize(sf::Vector2f(static_cast<float>(l_width), static_cast<float>(l_visible * l_charSize) * 1.2f));
  m_backup.setFillColor(sf::Color(90, 90, 90, 90));
  m_backup.setPosition(l_screenPos);
}

void Textbox::Add(const std::string &l_message)
{
  m_messages.emplace_back(l_message);
  if (m_messages.size() <= m_numVisible)
  {
    return;
  }
  m_messages.erase(m_messages.begin());
}

void Textbox::Clear() { m_messages.clear(); }

void Textbox::Render(sf::RenderWindow &l_wind)
{
  std::string l_content;
  for (const auto &itr : m_messages)
  {
    l_content.append(itr + "\n");
  }
  if (!l_content.empty())
  {
    m_content.setString(l_content);
    l_wind.draw(m_backup);
    l_wind.draw(m_content);
  }
}