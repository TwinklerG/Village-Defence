#include "Board.h"

Board::Board() {}
Board::Board(const sf::Sprite &l_sp, const sf::Vector2u &l_size) : Element(l_sp, l_size)
{
  m_font.loadFromFile("res/fonts/arial.ttf");
  m_moneyText.setFont(m_font);
  m_money = 100;
  m_moneyText.setColor(sf::Color::White);
  m_moneyText.setCharacterSize(20);
}
void Board::Render(sf::RenderWindow *l_wind)
{
  m_moneyText.setString(std::to_string(m_money));
  l_wind->draw(m_sprite);
  l_wind->draw(m_moneyText);
}
int Board::GetMoney() { return m_money; }
void Board::SetMoney(const int &l_money) { m_money = l_money; }
