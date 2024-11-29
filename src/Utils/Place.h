#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
enum class PlaceType
{
  Land,
  Water,
  Fire,
  Ice,
  Stone,
};

class Place
{
public:
  Place(const sf::Texture &l_texture);
  ~Place();

  virtual void OnCreate() = 0;
  virtual void Update() = 0;
  virtual void OnDestroy() = 0;

  sf::Sprite &GetSprite();
  void AddFigure(Figure *l_figure);
  bool RemoveFigure(Figure *l_figure);

private:
  sf::Sprite m_placeSprite;
  std::vector<Figure *> m_figures;
};

class HomeLand : public Place
{
  HomeLand(const sf::Texture &l_texture);

  void OnCreate() override;
  void Update() override;
  void OnDestroy() override;
};

class Land : public Place
{
public:
  Land(const sf::Texture &l_texture);

  void OnCreate() override;
  void Update() override;
  void OnDestroy() override;
};

class Water : public Place
{
public:
  void OnCreate() override;
  void Update() override;
  void OnDestroy() override;
};

class Fire : public Place
{
public:
  void OnCreate() override;
  void Update() override;
  void OnDestroy() override;
};

class Ice : public Place
{
public:
  void OnCreate() override;
  void Update() override;
  void OnDestroy() override;
};

class Stone : public Place
{
public:
  void OnCreate() override;
  void Update() override;
  void OnDestroy() override;
};