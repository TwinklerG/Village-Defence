#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "../Widgets/Select.h"

class State_Setting final : public BaseState {
public:
  explicit State_Setting(StateManager *l_stateManager);

  ~State_Setting() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

private:
  void SaveResolution(int width, int height) const;

  void MainMenu(EventDetails *l_details);

  std::unique_ptr<gl::Select> m_select;

  sf::Font m_font;
};
