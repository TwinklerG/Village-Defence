#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Place.h"
#include "StartPoint.h"
#include "EndPoint.h"
#include "Board.h"
#include "Bullet.h"
#include "../Widgets/TextBox.h"
#include "../Widgets/Label.h"

enum class SelectType {
  Choice,
  Existence,
};

struct SelectInfo {
  SelectInfo(): m_selectType(SelectType::Choice), m_tower(nullptr), x(0), y(0) {
  }

  SelectType m_selectType;
  std::shared_ptr<Tower> m_tower;
  int x, y;
};

struct PropBuff {
  PropBuff(): m_accelerate(1), m_decelerate(1), m_countDownSum(3) {
  }

  PropBuff(const double l_accelerate, const double l_decelerate, const float l_countDown) : m_accelerate(l_accelerate),
    m_decelerate(l_decelerate),
    m_countDown(l_countDown), m_countDownSum(3) {
  }

  void Reset() {
    m_accelerate = 1.0;
    m_decelerate = 1.0;
    m_countDown = 0;
  }

  double m_accelerate; // accelerate Tower
  double m_decelerate; // decelerate Invader
  float m_countDown = 0;

  const float m_countDownSum;
};

class Map {
public:
  explicit Map(sf::RenderWindow *l_wind, int l_level = 0,
               std::string l_resolutions = "1600_1000", sf::Vector2f l_resolution = {80, 80});

  explicit Map(sf::RenderWindow *l_wind, const nlohmann::json &l_gameState);

  ~Map();

  void OnCreate(sf::RenderWindow *l_wind);

  void Update(const sf::RenderWindow *l_wind, const sf::Time &l_time);

  void Render(sf::RenderWindow *l_wind);

  void Reload();

  void Save();

  int GetLives() const;

  bool IsWin() const;

private:
  void LoadMap();

  void LoadProp();

  static std::vector<TowerInfo> LoadTowerInfo();

  int m_lives{};
  bool m_isWin;
  sf::RectangleShape m_backup;
  std::unique_ptr<Board> m_board;
  std::vector<std::pair<std::pair<std::shared_ptr<sf::Sprite>, std::shared_ptr<sf::Text> >, TowerInfo> > m_choices;
  sf::RenderWindow *m_wind{};
  std::vector<std::pair<std::pair<int, int>, std::vector<Direction> > > m_roads;
  SelectInfo m_selected;

  // Main Objects
  std::vector<std::vector<std::shared_ptr<Place> > > m_places;
  std::vector<std::shared_ptr<Figure> > m_figures;
  std::vector<Bullet> m_bullets;

  // Props
  PropBuff m_propBuff;
  std::vector<gl::Label> m_labels;

  // Widgets
  std::vector<StartPoint> m_startPoints;
  std::vector<EndPoint> m_endPoints;
  std::unique_ptr<gl::TextBox> m_textBox;

  // Resources
  std::unordered_map<std::string, sf::Font> m_fonts;
  std::unordered_map<std::string, sf::Texture> m_textures;

  // Configurations
  std::string m_resolution;
  sf::Vector2f m_atomResolution;
  const int m_level;
  static int m_XRange;
  static int m_YRange;
};
