#pragma once
#include "State_MainMenu.h"

class State_Load final : public BaseState {
public:
  explicit State_Load(StateManager *l_stateManager);

  ~State_Load() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

  void Activate() override;

  void Deactivate() override;

  void MainMenu(EventDetails *l_details);

private:
  sf::Font m_font;

  sf::Text m_title;
  std::vector<gl::Button> m_buttons;
};
