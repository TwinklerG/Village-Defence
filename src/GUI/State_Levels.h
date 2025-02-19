#pragma once
#include "BaseState.h"
#include "../Widgets/Button.h"

class State_Levels final : public BaseState {
public:
  explicit State_Levels(StateManager *l_stateManager);

  ~State_Levels() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

private:
  sf::Font m_font;
  std::unique_ptr<sf::Text> m_title;
  std::vector<gl::Button> m_buttons;
  std::vector<sf::RectangleShape> m_rects;
  std::vector<sf::Text> m_labels;

  static int m_LevelSum;
};
