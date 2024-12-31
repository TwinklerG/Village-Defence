#pragma once
#include <memory>

#include "Element.h"

class Tower final : public Element {
public:
  explicit Tower(const sf::Sprite &, const sf::Vector2u &, const sf::Time &, int = 1, float = 90, double range = 400,
                 int = 50,
                 int red = 255, int green = 255, int blue = 0, double radius = 10, int l_tag = 0);

  void Render(sf::RenderWindow *l_wind) const override;

  void SetCalmTime(const sf::Time &l_time);

  sf::Time GetCalmTime() const;

  std::shared_ptr<sf::CircleShape> GetCircle() const;

  void SetCircle(const std::shared_ptr<sf::CircleShape> &l_circle);

  const int &GetAttackPoint() const;

  const float &GetBulletSpeed() const;

  const int &GetCost() const;

  const double &GetRange() const;

  const sf::Color &GetBulletColor() const;

  const double &GetBulletRadius() const;

  int GetTag() const;

  static sf::Time m_totalClickCalmTime;
  const sf::Time m_totalCalmTime;

private:
  sf::Time m_clamTime;
  int m_attackPoint;
  std::shared_ptr<sf::CircleShape> m_circle;
  double m_bulletRadius{};
  sf::Color m_bulletColor;
  float m_bulletSpeed{};
  double m_range{};
  int m_cost{};

  int m_tag;
};

enum class PlaceType {
  Land,
  Road,
  Tower,
  Begin,
  End,
};

class Place final : public Element {
public:
  Place();

  Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size);

  Place(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const PlaceType &l_placeType);

  void Render(sf::RenderWindow *l_wind) const override;

  void SetTower(std::shared_ptr<Tower> l_tower);

  std::shared_ptr<Tower> GetTower();

  const PlaceType &GetPlaceType() const;

  void SetPlaceType(const PlaceType &);

private:
  std::shared_ptr<Tower> m_tower;
  PlaceType m_placeType;
};

struct TowerInfo {
  int m_tag;
  int m_cost;
  int m_attackPoint;
  double m_range;
  double m_calmTime;
  double m_speed;
  int m_red, m_green, m_blue;
  double m_bulletRadius;
};
