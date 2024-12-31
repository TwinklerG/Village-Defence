#pragma once
#include "State_MainMenu.h"
#include "StateManager.h"

class State_Save final : public State_MainMenu {
public:
  explicit State_Save(StateManager *l_stateManager);

  ~State_Save() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;
};
