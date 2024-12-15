#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "../Widgets/Button.h"

class State_MainMenu final : public BaseState {
public:
  explicit State_MainMenu(StateManager *l_stateManager);

  ~State_MainMenu() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

  void MouseClick(EventDetails *l_details);

private:
  sf::Font m_font;
  // sf::Text m_text;
  // sf::Vector2f m_buttonSize;
  // sf::Vector2f m_buttonPos;
  // unsigned int m_buttonPadding{};
  // std::vector<sf::RectangleShape> m_rects;
  // std::vector<sf::Text> m_labels;

  sf::Text m_title;
  std::vector<gl::Button> m_buttons;
};
