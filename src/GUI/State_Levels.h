#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Levels final : public BaseState
{
public:
  explicit State_Levels(StateManager *l_stateManager);
  ~State_Levels() override;

  void OnCreate() override;
  void OnDestroy() override;

  void Activate() override;
  void Deactivate() override;

  void MainMenu(EventDetails* l_details);

  void Update(const sf::Time &l_time) override;
  void Draw() override;

private:
};