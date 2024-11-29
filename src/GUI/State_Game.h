#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "../Utils/Place.h"
#include "../Utils/Figure.h"

using Textures = std::unordered_map<std::string, sf::Texture>;

class State_Game : public BaseState
{
public:
  State_Game(StateManager *l_stateManager);
  ~State_Game();

  void OnCreate();
  void OnDestroy();

  void Activate();
  void Deactivate();

  void Update(const sf::Time &l_time);
  void MoveSprite(EventDetails *l_details);
  void Draw();

  void MainMenu(EventDetails *l_details);
  void Pause(EventDetails *l_details);

private:
  std::vector<std::vector<Place*>> m_places;
  Textures m_textures;
};