#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Place.h"
class StateManager;
class Map
{
public:
  Map(StateManager *l_stateMgr);

private:
  StateManager *m_stateMgr;

  std::vector<std::vector<Place *>> m_places;
  std::unordered_map<std::string, sf::Texture> m_textures;
  static int m_XRange;
  static int m_YRange;

  std::vector<Figure *> m_figures;
};