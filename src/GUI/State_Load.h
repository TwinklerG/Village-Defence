#pragma once
#include "State_MainMenu.h"

class State_Load final : public State_MainMenu {
public:
  explicit State_Load(StateManager *l_stateManager);

  ~State_Load() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Update(const sf::Time &l_time) override;

  void MainMenu(EventDetails *l_details);
};
