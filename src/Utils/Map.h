#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Place.h"
class Map
{
public:
  Map(sf::RenderWindow* l_wind);
  ~Map();

  void OnCreate(sf::RenderWindow* l_wind);
  void Update();
  void Render(sf::RenderWindow* l_wind);
  void OnDestroy();

  void LoadLogicMap(sf::RenderWindow* l_wind); // Load logic map from map.cfg
  sf::Time GetElapsed();
  void RestartClock();

private:
  std::vector<std::vector<Place *>> m_places;
  std::unordered_map<std::string, sf::Texture> m_textures;
  std::vector<std::vector<int>> m_logicMap;

  std::vector<Figure *> m_figures;

  sf::Clock m_clock;
  sf::Time m_elapsed;

  static int m_XRange;
  static int m_YRange;
  static float m_FrameTime;
};