#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_About final : public BaseState
{
public:
  explicit State_About(StateManager *l_stateManager);
  ~State_About() override;

  void OnCreate() override;
  void OnDestroy() override;

  void Activate() override;
  void Deactivate() override;

  void Update(const sf::Time &l_time) override;
  void Draw() override;

  void MainMenu(EventDetails *l_details);

private:
  sf::Font m_font;
  sf::Text m_content;
};