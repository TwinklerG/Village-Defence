#pragma once
#include "BaseState.h"
#include "../Widgets/Confirm.h"
#include "../Widgets/Select.h"

struct WindowConfig {
  sf::Vector2u m_windowSize;
  int m_framerateLimit{};

  WindowConfig() = default;

  WindowConfig(const sf::Vector2u &l_windowSize, const int l_framerateLimit)
    : m_windowSize(l_windowSize),
      m_framerateLimit(l_framerateLimit) {
  }
};

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
  void LoadConfig();

  void SaveResolution() const;

  std::vector<gl::Select> m_select;
  WindowConfig m_config;
  std::shared_ptr<gl::Confirm> m_confirm;
  sf::Font m_font;
};
