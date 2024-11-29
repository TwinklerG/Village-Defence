#include "Place.h"

sf::Sprite &Place::GetSprite() { return m_placeSprite; }

Place::Place(const sf::Texture &l_texture) : m_placeSprite(l_texture) {}

Place::~Place() {}

void Place::AddFigure(Figure *l_figure) { m_figures.emplace_back(l_figure); }

bool Place::RemoveFigure(Figure *l_figure)
{
  for (auto itr = m_figures.begin(); itr != m_figures.end(); ++itr)
  {
    if (*itr == l_figure)
    {
      m_figures.erase(itr);
      return true;
    }
  }
  return false;
}
Land::Land(const sf::Texture &l_texture) : Place(l_texture) { OnCreate(); }
void Land::OnCreate() {}
void Land::Update() {}
void Land::OnDestroy() {}

void Water::OnCreate() {}
void Water::Update() {}
void Water::OnDestroy() {}

void Fire::OnCreate() {}
void Fire::Update() {}
void Fire::OnDestroy() {}

void Ice::OnCreate() {}
void Ice::Update() {}
void Ice::OnDestroy() {}

void Stone::OnCreate() {}
void Stone::Update() {}
void Stone::OnDestroy() {}