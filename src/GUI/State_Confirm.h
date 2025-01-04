#pragma once
#include "BaseState.h"

class State_Confirm final : public BaseState {
public:
  explicit State_Confirm(StateManager *l_stateManager);

  ~State_Confirm() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;
};
