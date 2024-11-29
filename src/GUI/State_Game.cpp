#include "State_Game.h"
#include "StateManager.h"

int State_Game::m_XRange = 22;
int State_Game::m_YRange = 9;

State_Game::State_Game(StateManager *l_stateManager) : BaseState(l_stateManager), m_map(l_stateManager) {}

State_Game::~State_Game() {}

void State_Game::OnCreate()
{
  sf::Texture l_texture;
  l_texture.loadFromFile("res/land.png");
  m_textures.emplace("land", l_texture);
  l_texture.loadFromFile("res/mainland.png");
  m_textures.emplace("mainland", l_texture);
  sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  m_places = std::vector<std::vector<Place *>>(m_XRange, std::vector<Place *>(m_YRange));
  for (int i = 0; i < m_XRange - 1; ++i)
  {
    for (int j = 0; j < m_YRange; ++j)
    {
      m_places[i][j] = new Land(m_textures["land"]);
      m_places[i][j]->GetSprite().setPosition(i * 80, l_wind->getSize().y / 3 + j * 80);
    }
  }
  for (int j = 0; j < m_YRange; j += 3)
  {
    m_places[m_XRange - 1][j] = new Land(m_textures["mainland"]);
    m_places[m_XRange - 1][j]->GetSprite().setPosition((m_XRange - 1) * 80, l_wind->getSize().y / 3 + j * 80);
  }

  m_figures.emplace_back(new Ordinary());

  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
  envMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
}

void State_Game::Update(const sf::Time &l_time)
{
  m_figures[0]->Update(l_time);
}

void State_Game::MoveSprite(EventDetails *l_details) {}

void State_Game::Draw()
{
  sf::RenderWindow &l_wind = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  for (int i = 0; i < m_XRange - 1; ++i)
  {
    for (int j = 0; j < m_YRange; ++j)
    {
      l_wind.draw(m_places[i][j]->GetSprite());
    }
  }
  for (int j = 0; j < m_YRange; j += 3)
  {
    l_wind.draw(m_places[m_XRange - 1][j]->GetSprite());
  }

  l_wind.draw(m_figures[0]->GetSprite());
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