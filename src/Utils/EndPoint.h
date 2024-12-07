#include "Element.h"
class EndPoint : public Element
{
public:
  EndPoint();
  EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor);
  void Render(sf::RenderWindow *l_wind) const override;

private:
  std::pair<int, int> m_cordinate;
};