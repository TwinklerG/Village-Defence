#pragma once
#include "BaseState.h"

class State_Paused final : public BaseState {
public:
  explicit State_Paused(StateManager *l_stateManager);

  ~State_Paused() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

private:
  sf::Font m_font;
  std::unique_ptr<sf::Text> m_text;
  sf::RectangleShape m_rect;
};
