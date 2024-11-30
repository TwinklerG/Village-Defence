#include "Place.h"

sf::Sprite &Place::GetSprite() { return m_placeSprite; }
Place::Place(const sf::Texture &l_texture) : m_placeSprite(l_texture) {}
Place::~Place() {}

HomeLand::HomeLand(const sf::Texture &l_texture) : Place(l_texture) { OnCreate(); }
void HomeLand::OnCreate() {}
void HomeLand::Update() {}
void HomeLand::OnDestroy() {}

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

Stone::Stone(const sf::Texture &l_texture) : Place(l_texture) { OnCreate(); }
void Stone::OnCreate() {}
void Stone::Update() {}
void Stone::OnDestroy() {}