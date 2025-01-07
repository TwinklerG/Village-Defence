#pragma once
#include "BaseState.h"
#include "../Utils/Map.h"
#include "../Widgets/Settlement.h"

class State_Game final : public BaseState {
public:
  explicit State_Game(StateManager *l_stateManager);

  ~State_Game() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

private:
  void Winner(int l_level);

  void YouLose(int l_level);

  std::unique_ptr<Map> m_map;

  std::shared_ptr<gl::Settlement> m_settlement;
  sf::Font m_font;
};
