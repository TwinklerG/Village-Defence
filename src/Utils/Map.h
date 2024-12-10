#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Place.h"
#include "StartPoint.h"
#include "EndPoint.h"
#include "Board.h"
#include "Bullet.h"
#include "../GUI/Textbox.h"

enum class SelectType
{
  Choice,
  Existence,
};

struct SelectInfo
{
  SelectType m_selectType;
  std::shared_ptr<Tower> m_tower;
  int x, y;
};

class Map
{
public:
  explicit Map(sf::RenderWindow *l_wind, int l_level = 0);
  ~Map();

  void OnCreate(sf::RenderWindow *l_wind);
  void Update(sf::RenderWindow *l_wind, const sf::Time &l_time);
  void Render(sf::RenderWindow *l_wind);

  void LoadMap();
  int GetLives() const;
  bool IsWin() const;

private:
  const int m_level;
  int m_lives{};
  bool m_isWin;
  sf::RectangleShape m_backup;
  std::unique_ptr<Board> m_board;
  std::vector<std::pair<std::pair<sf::Sprite, sf::Text>, TowerInfo>> m_choices;
  sf::RenderWindow *m_wind{};
  std::vector<std::shared_ptr<Figure>> m_figures;
  SelectInfo m_selected;
  std::vector<std::vector<Place>> m_places;
  std::vector<StartPoint> m_startPoints;
  std::vector<EndPoint> m_endPoints;
  std::vector<std::pair<std::pair<int, int>, std::vector<Direction>>> m_roads;
  std::vector<Bullet> m_bullets;
  Textbox m_textbox;
  std::unordered_map<std::string, sf::Font> m_fonts;
  std::unordered_map<std::string, sf::Texture> m_textures;
  sf::Clock m_clock;
  static int m_XRange;
  static int m_YRange;
};