#include "Board.h"

Board::Board() {
  m_money = 150;
  m_font = sf::Font("res/fonts/arial.ttf");
  m_border = sf::RectangleShape(sf::Vector2f(90, 90));
  m_border.setFillColor(sf::Color(120, 120, 0));
  m_border.setOutlineColor(sf::Color::Green);
  m_border.setOutlineThickness(5);
  m_border.setOrigin({m_border.getSize().x / 2, m_border.getSize().y / 2});
  m_border.setPosition({
    m_border.getSize().x / 2 + m_border.getOutlineThickness(),
    m_border.getSize().y / 2 + m_border.getOutlineThickness()
  });
  m_tip = std::make_unique<sf::Text>(m_font, "Money", 30);
  m_tip->setFillColor(sf::Color::White);
  m_tip->setOrigin({m_tip->getLocalBounds().size.x / 2, m_tip->getLocalBounds().size.y / 2});
  m_tip->setPosition({m_border.getPosition().x, m_border.getSize().y / 3});
  m_moneyText = std::make_unique<sf::Text>(m_font, "", 30);
  m_moneyText->setFillColor(sf::Color::White);
  m_moneyText->setOrigin({m_moneyText->getLocalBounds().size.x / 2, m_moneyText->getLocalBounds().size.y / 2});
  m_moneyText->setPosition({m_border.getPosition().x, m_border.getSize().y / 3 * 2});
}

Board::Board(const sf::Vector2f &l_size) {
  m_money = 150;
  m_font = sf::Font("res/fonts/arial.ttf");
  m_border = sf::RectangleShape(l_size);
  m_border.setFillColor(sf::Color(120, 120, 0));
  m_border.setOutlineColor(sf::Color::Green);
  m_border.setOutlineThickness(5);
  m_border.setOrigin({m_border.getSize().x / 2, m_border.getSize().y / 2});
  m_border.setPosition({
    m_border.getSize().x / 2 + m_border.getOutlineThickness(),
    m_border.getSize().y / 2 + m_border.getOutlineThickness()
  });
  m_tip = std::make_unique<sf::Text>(m_font, "Money", 30);
  m_tip->setFillColor(sf::Color::White);
  m_tip->setOrigin({m_tip->getLocalBounds().size.x / 2, m_tip->getLocalBounds().size.y / 2});
  m_tip->setPosition({m_border.getPosition().x, m_border.getSize().y / 3});
  m_moneyText = std::make_unique<sf::Text>(m_font, "", 30);
  m_moneyText->setFillColor(sf::Color::White);
  m_moneyText->setOrigin({m_moneyText->getLocalBounds().size.x / 2, m_moneyText->getLocalBounds().size.y / 2});
  m_moneyText->setPosition({m_border.getPosition().x, m_border.getSize().y / 3 * 2});
}

void Board::Render(sf::RenderWindow *l_wind) const {
  m_moneyText->setString(std::to_string(m_money));
  m_moneyText->setOrigin({m_moneyText->getLocalBounds().size.x / 2, m_moneyText->getLocalBounds().size.y / 2});
  l_wind->draw(m_border);
  l_wind->draw(*m_moneyText);
  l_wind->draw(*m_tip);
}

int Board::GetMoney() const { return m_money; }
void Board::SetMoney(const int &l_money) { m_money = l_money; }
