#include "Element.h"
class StartPoint : public Element
{
public:
  StartPoint();
  StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size);
  StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor, const sf::Time &l_tct);
  void SetCalmTime(const sf::Time &l_time);
  const std::pair<int, int> GetCordinate() const;
  const sf::Time &GetCalmTime() const;
  void RestartCalmTime();

private:
  sf::Time m_totalCalmTime;
  sf::Time m_calmTime;
  std::pair<int, int> m_cordinate;
};