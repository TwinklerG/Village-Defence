#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *l_stateManager) : BaseState(l_stateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate()
{
  sf::Texture l_texture;
  l_texture.loadFromFile("res/Mushroom.png");
  m_textures.emplace("Ordinary", l_texture);
  m_places = std::vector<std::vector<Place *>>(3, std::vector<Place *>(3));
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      m_places[i][j] = new Land(m_textures["Ordinary"]);
      m_places[i][j]->GetSprite().setPosition(i * 200, j * 200);
    }
  }
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
  envMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
}

void State_Game::Update(const sf::Time &l_time)
{
}

void State_Game::MoveSprite(EventDetails *l_details)
{
}

void State_Game::Draw()
{
  sf::RenderWindow &l_wind = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      l_wind.draw(m_places[i][j]->GetSprite());
    }
  }
}

void State_Game::MainMenu(EventDetails *l_details)
{
  m_stateMgr->SwitchTo(StateType::MainMenu);
}
void State_Game::Pause(EventDetails *l_details)
{
  m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}