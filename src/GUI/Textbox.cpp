#include "Textbox.h"

Textbox::Textbox() { Setup(5, 9, 200, sf::Vector2f(0, 0)); }
Textbox::Textbox(int l_visble, int l_charSize, int l_width, const sf::Vector2f &l_screenPos) { Setup(l_visble, l_charSize, l_width, l_screenPos); }
Textbox::~Textbox() { Clear(); }

void Textbox::Setup(int l_visible, int l_charSize, int l_width, const sf::Vector2f &l_screenPos)
{
  m_numVisible = l_visible;

  sf::Vector2f l_offset(0.2f, 0.2f);

  m_font.loadFromFile("res/fonts/arial.ttf");
  m_content.setFont(m_font);
  m_content.setString("");
  m_content.setCharacterSize(l_charSize);
  m_content.setColor(sf::Color::White);
  m_content.setPosition(l_screenPos + l_offset);

  m_backup.setSize(sf::Vector2f(l_width, (l_visible * l_charSize * 1.2f)));
  m_backup.setFillColor(sf::Color(90, 90, 90, 90));
  m_backup.setPosition(l_screenPos);
}

void Textbox::Add(const std::string &l_message)
{
  m_messages.emplace_back(l_message);
  if (m_messages.size() < m_numVisible)
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
  if (l_content != "")
  {
    m_content.setString(l_content);
    l_wind.draw(m_backup);
    l_wind.draw(m_content);
  }
}