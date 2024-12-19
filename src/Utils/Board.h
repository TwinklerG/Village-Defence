#pragma once
#include <SFML/Graphics.hpp>

class Board {
public:
  Board();

  explicit Board(const sf::Vector2f &l_size);

  void Render(sf::RenderWindow *);

  int GetMoney() const;

  void SetMoney(const int &l_money);

private:
  sf::RectangleShape m_border;
  sf::Text m_tip;
  sf::Font m_font;
  sf::Text m_moneyText;
  int m_money;
};
