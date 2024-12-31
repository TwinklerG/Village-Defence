#pragma once
#include "BaseState.h"
#include "../Utils/Map.h"

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
  std::unique_ptr<Map> m_map;
};
