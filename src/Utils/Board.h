#pragma once
#include "Element.h"

class Board : public Element
{
public:
  Board();
  Board(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  void Render(sf::RenderWindow *l_wind);
  int GetMoney();
  void SetMoney(const int &l_money);

private:
  sf::Font m_font;
  int m_money;
  sf::Text m_moneyText;
};