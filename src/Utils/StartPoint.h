#pragma once
#include <fstream>
#include <unordered_map>
#include <numeric>
#include "Element.h"
#include "Figure.h"
class StartPoint : public Element
{
public:
  StartPoint();
  StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor);
  StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor, const sf::Time &l_tct, const std::vector<std::vector<std::pair<int, int>>> &l_invaderTurns);
  Figure *Update(const sf::Time &l_elapsed);
  void SetCalmTime(const sf::Time &l_time);
  const std::pair<int, int> GetCordinate() const;
  const sf::Time &GetCalmTime() const;
  void RestartCalmTime();
  void SetRoads(const std::vector<std::vector<Direction>> &l_roads);

private:
  sf::Time m_totalCalmTime;
  sf::Time m_calmTime;
  std::pair<int, int> m_cordinate;
  std::vector<std::vector<std::pair<int, int>>> m_invaderTurns;
  std::vector<Figure> m_figures;
  std::vector<std::vector<Direction>> m_roads;
  std::vector<FigureInfo> m_figureInfos;
  std::unordered_map<std::string, sf::Texture> m_textures;

  static sf::Time m_BreakTime;
};