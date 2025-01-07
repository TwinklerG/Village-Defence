#pragma once
#include "StateManager.h"
#include "../Widgets/Button.h"
#include "../Widgets/Confirm.h"

class State_Save final : public BaseState {
public:
  explicit State_Save(StateManager *l_stateManager);

  ~State_Save() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

private:
  std::shared_ptr<sf::Text> m_title;
  std::vector<gl::Button> m_buttons;
  sf::Font m_font;
  std::shared_ptr<gl::Confirm> m_confirm;
  int m_toConfirm;
};
