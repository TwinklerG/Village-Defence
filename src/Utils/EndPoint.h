#include "Element.h"
class EndPoint : public Element
{
public:
  EndPoint();
  EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  EndPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const sf::Sprite &l_esp, const std::pair<int, int> &l_cor);
  void Render(sf::RenderWindow *l_wind) const override;
  void SetEndPointSprite(const sf::Sprite &l_eps);
  const sf::Sprite &GetEndPointSprite();
  const std::pair<int, int> GetCordinate() const;

private:
  sf::Sprite m_endPointSprite;
  std::pair<int, int> m_cordinate;
};