#pragma once
#include <thread>

#include "BaseState.h"
#include "../Widgets/Button.h"
#include "../Widgets/Toast.h"

class State_MainMenu : public BaseState {
public:
  explicit State_MainMenu(StateManager *l_stateManager);

  ~State_MainMenu() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

protected:
  sf::Font m_font;

  std::unique_ptr<sf::Text> m_title;
  std::vector<gl::Button> m_buttons;

  std::shared_ptr<gl::Toast> m_toast;
};
