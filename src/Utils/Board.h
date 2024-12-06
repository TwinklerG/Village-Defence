#pragma once
#include "Element.h"

class Board 
{
public:
  Board();
  void Render(sf::RenderWindow *l_wind);
  int GetMoney() const;
  void SetMoney(const int &l_money);
  sf::Time GetCalmTime() const;
  void SetCalmTime(const sf::Time &l_calmTime);

private:
  sf::RectangleShape m_border;
  sf::Text m_tip;
  sf::Font m_font;
  sf::Text m_moneyText;
  int m_money;

  sf::Time m_calmTime;
  sf::Time m_totalCalmTime;
};