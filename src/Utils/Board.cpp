#include "Board.h"

Board::Board()
{
  m_money = 100;
  m_calmTime = sf::seconds(3);
  m_font.loadFromFile("res/fonts/arial.ttf");
  m_border = sf::RectangleShape(sf::Vector2f(90, 90));
  m_border.setFillColor(sf::Color(120, 120, 0));
  m_border.setOutlineColor(sf::Color::Green);
  m_border.setOutlineThickness(5);
  m_border.setOrigin(m_border.getSize().x / 2, m_border.getSize().y / 2);
  m_border.setPosition(m_border.getSize().x / 2 + m_border.getOutlineThickness(), m_border.getSize().y / 2 + m_border.getOutlineThickness());
  m_tip.setString("Money");
  m_tip.setFont(m_font);
  m_tip.setFillColor(sf::Color::White);
  m_tip.setCharacterSize(30);
  m_tip.setOrigin(m_tip.getLocalBounds().width / 2, m_tip.getLocalBounds().height / 2);
  m_tip.setPosition(m_border.getPosition().x, m_border.getSize().y / 3);
  m_moneyText.setFont(m_font);
  m_moneyText.setFillColor(sf::Color::White);
  m_moneyText.setCharacterSize(30);
  m_moneyText.setOrigin(m_moneyText.getLocalBounds().width / 2, m_moneyText.getLocalBounds().height / 2);
  m_moneyText.setPosition(m_border.getPosition().x, m_border.getSize().y / 3 * 2);
}
void Board::Render(sf::RenderWindow *l_wind)
{
  m_moneyText.setString(std::to_string(m_money));
  m_moneyText.setOrigin(m_moneyText.getLocalBounds().width / 2, m_moneyText.getLocalBounds().height / 2);
  // l_wind->draw(m_sprite);
  l_wind->draw(m_border);
  l_wind->draw(m_moneyText);
  l_wind->draw(m_tip);
}
int Board::GetMoney() const { return m_money; }
void Board::SetMoney(const int &l_money) { m_money = l_money; }
sf::Time Board::GetCalmTime() const { return m_calmTime; }
void Board::SetCalmTime(const sf::Time &l_calmTime) { m_calmTime = l_calmTime; }
