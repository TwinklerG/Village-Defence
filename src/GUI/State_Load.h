#pragma once
#include "State_MainMenu.h"
#include "../Widgets/Confirm.h"

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

private:
  sf::Font m_font;

  std::unique_ptr<sf::Text> m_title;
  std::vector<gl::Button> m_buttons;

  std::shared_ptr<gl::Confirm> m_confirm;
  int m_toConfirm;
};
