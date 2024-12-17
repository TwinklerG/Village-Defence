#pragma once
#include <fstream>
#include <memory>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Element.h"
#include "Figure.h"

struct InvadeTurnInfo {
  double m_calmTime;
  double m_speedBuff;
  std::vector<std::pair<int, int> > m_infos;
};

class StartPoint final : public Element {
public:
  StartPoint();

  StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor);

  StartPoint(const sf::Sprite &l_sp, const sf::Vector2u &l_size, const std::pair<int, int> &l_cor,
             const std::vector<InvadeTurnInfo> &l_invaderTurns);

  void OnCreate();

  std::shared_ptr<Figure> Update(const sf::Time &l_elapsed);

  void SetCalmTime(const sf::Time &l_time);

  std::pair<int, int> GetCoordinate() const;

  const sf::Time &GetCalmTime() const;

  void RestartCalmTime();

  void SetRoads(const std::vector<std::vector<Direction> > &l_roads);

  int GetLeftTurns() const;

private:
  sf::Time m_totalCalmTime;
  sf::Time m_calmTime;
  std::pair<int, int> m_coordinate;
  std::vector<InvadeTurnInfo> m_invaderTurns;
  std::vector<Figure> m_figures;
  std::vector<std::vector<Direction> > m_roads;
  std::vector<FigureInfo> m_figureInfos;
  std::unordered_map<std::string, sf::Texture> m_textures;

  static sf::Time m_BreakTime;
};
