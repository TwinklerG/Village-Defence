#pragma once
#include "BaseState.h"
#include "../Widgets/Button.h"

class State_Intro final : public BaseState {
public:
  explicit State_Intro(StateManager *l_stateManager);

  ~State_Intro() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

private:
  sf::Font m_font;
  std::unique_ptr<sf::Text> m_text;
  std::unique_ptr<sf::Text> m_title;

  float m_timePassed{};

  std::vector<sf::Texture> m_textures;
  std::vector<sf::Sprite> m_sprites;
  std::vector<sf::Vector2i> m_increments;
  sf::Time m_elapsed;
  sf::Clock m_clock;

  void MoveSprites();

  void RestartClock();

  static float m_AnimationTime;
  static int m_SpritesSum;
};
