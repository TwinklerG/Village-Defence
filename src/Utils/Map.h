#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
class Map
{
public:
  Map(sf::RenderWindow *l_wind);
  ~Map();

  void OnCreate(sf::RenderWindow *l_wind);
  void Update(sf::RenderWindow* l_wind);
  void Render(sf::RenderWindow *l_wind);
  void OnDestroy();

  void LoadLogicMap(); // Load logic map from map.cfg
  sf::Time GetElapsed();
  void RestartClock();

private:
  sf::RenderWindow *m_wind;
  std::vector<std::pair<std::shared_ptr<sf::RectangleShape>, double>> m_figures;
  std::unordered_map<std::shared_ptr<sf::RectangleShape>,std::vector<int>> m_figureIncrementMap;
  std::unique_ptr<sf::RectangleShape> m_selected;
  std::vector<std::vector<int>> m_places;
  std::vector<std::vector<sf::RectangleShape>> m_placesSprite;
  sf::Clock m_clock;
  sf::Time m_elapsed;
  static int m_XRange;
  static int m_YRange;
  static float m_FrameTime;
};

class Figure {
  public:
  private:
};