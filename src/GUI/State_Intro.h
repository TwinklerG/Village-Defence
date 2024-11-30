#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState
{
public:
  State_Intro(StateManager *l_stateManager);
  ~State_Intro();

  void OnCreate();
  void OnDestroy();

  void Activate();
  void Deactivate();

  void Update(const sf::Time &l_time);
  void Draw();

  void Continue(EventDetails *l_details);

private:
  sf::Texture m_introTexture;
  sf::Sprite m_introSprite;
  sf::Font m_font;
  sf::Text m_text;

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