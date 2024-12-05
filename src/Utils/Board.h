#pragma once
#include "Element.h"

class Board : public Element
{
public:
  Board();
  Board(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  void Render(sf::RenderWindow *l_wind);
  int GetMoney() const;
  void SetMoney(const int &l_money);
  sf::Time GetCalmTime() const;
  void SetCalmTime(const sf::Time& l_calmTime);

private:
  sf::Font m_font;
  int m_money;
  sf::Text m_moneyText;

  sf::Time m_calmTime;
  sf::Time m_totalCalmTime;
};