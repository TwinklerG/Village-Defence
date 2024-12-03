#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <functional>
#include "Place.h"
#include "Figure.h"
#include "StartPoint.h"

// enum class Direction
// {
//   Up = 0,
//   Down,
//   Right,
//   Left,
// };

class Map
{
public:
  Map(sf::RenderWindow *l_wind);
  ~Map();

  void OnCreate(sf::RenderWindow *l_wind);
  void Update(sf::RenderWindow *l_wind);
  void Render(sf::RenderWindow *l_wind);
  void OnDestroy();

  void LoadMap();
  sf::Time GetElapsed();
  void RestartClock();

private:
  sf::RenderWindow *m_wind;
  std::vector<Figure*> m_figures;
  Tower *m_selectedItem;
  std::vector<std::vector<Place>> m_places;
  std::vector<std::pair<int, int>> m_startPointss;
  std::vector<StartPoint> m_startPoints;
  std::vector<std::pair<int, int>> m_endPoints;
  std::vector<std::pair<std::pair<int, int>, std::vector<Direction>>> m_roads;
  std::vector<std::pair<sf::CircleShape, Figure *>> m_bullets;
  std::unordered_map<std::string, sf::Texture> m_textures;
  sf::Clock m_clock;
  sf::Time m_elapsed;
  static int m_XRange;
  static int m_YRange;
  static float m_FrameTime;
};