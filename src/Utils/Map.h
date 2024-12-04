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
#include "EndPoint.h"
#include "Board.h"
#include "../GUI/Textbox.h"

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
  std::unique_ptr<Board> m_board;
  sf::RenderWindow *m_wind;
  std::vector<Figure *> m_figures;
  Tower *m_selectedItem;
  std::vector<std::vector<Place>> m_places;
  std::vector<StartPoint> m_startPoints;
  std::vector<EndPoint> m_endPoints;
  std::vector<std::pair<std::pair<int, int>, std::vector<Direction>>> m_roads;
  std::vector<std::pair<sf::CircleShape, Figure *>> m_bullets;
  Textbox m_textbox;
  std::unordered_map<std::string, sf::Texture> m_textures;
  sf::Clock m_clock;
  sf::Time m_elapsed;
  static int m_XRange;
  static int m_YRange;
  static float m_FrameTime;
};