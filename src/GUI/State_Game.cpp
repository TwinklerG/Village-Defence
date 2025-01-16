#include "State_Game.h"
#include "StateManager.h"
#include <iostream>

State_Game::State_Game(StateManager *l_stateManager)
    : BaseState(l_stateManager), m_map(nullptr), m_settlement(nullptr) {
  if (m_stateMgr->GetContext()->m_mapData) {
    m_map = std::make_unique<Map>(
        m_stateMgr->GetContext()->m_wind->GetRenderWindow(),
        *m_stateMgr->GetContext()->m_mapData);
    std::cout << "Use Shared Context\n";
    m_stateMgr->GetContext()->m_mapData = nullptr;
    return;
  }
  m_map =
      std::make_unique<Map>(m_stateMgr->GetContext()->m_wind->GetRenderWindow(),
                            l_stateManager->GetContext()->m_level,
                            l_stateManager->GetContext()->m_resolution,
                            l_stateManager->GetContext()->m_atomResolution);
}

State_Game::~State_Game() = default;

void State_Game::OnCreate() {}

void State_Game::OnDestroy() {}

void State_Game::Update(const sf::Time &l_time) {
  if (m_map) {
    m_map->Update(m_stateMgr->GetContext()->m_wind->GetRenderWindow(), l_time);
    if (m_map->GetLives() <= 0) {
      m_stateMgr->GetContext()->m_soundManager.Play("you_lose.ogg", 100);
      m_map = nullptr;
      YouLose(m_stateMgr->GetContext()->m_level);
    } else if (m_map->IsWin()) {
      m_stateMgr->GetContext()->m_soundManager.Play("winner.ogg", 100);
      m_map = nullptr;
      Winner(m_stateMgr->GetContext()->m_level);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      m_stateMgr->SwitchTo(StateType::MainMenu);
    }
  }
  if (m_settlement) {
    m_settlement->Update(l_time);
  }
}

void State_Game::Draw() {
  const auto l_window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  if (m_map) {
    m_map->Render(l_window);
  }
  if (m_settlement) {
    m_settlement->Render(*l_window);
  }
}

void State_Game::Activate() {
  if (m_map) {
    m_map->Reload();
  }
  m_stateMgr->GetContext()->m_bgmManager.Play("battle.mp3", 20, true);
}

void State_Game::Deactivate() {
  if (m_map) {
    m_map->Save();
  }
  m_stateMgr->GetContext()->m_bgmManager.Play("loading.wav", 200, true);
}

void State_Game::Winner(int l_level) {
  std::fstream in("res/config/map" + std::to_string(l_level) + ".json");
  nlohmann::json data = nlohmann::json::parse(in);
  in.close();
  const auto invadeTurns = data["invaderTurns"];
  std::unordered_map<int, int> l_infos;
  for (const auto &invaderTurn : invadeTurns) {
    for (const auto &l_info : invaderTurn["invaders"]) {
      l_infos[l_info["type"]] += static_cast<int>(l_info["num"]);
    }
  }
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  m_settlement = std::make_shared<gl::Settlement>(
      sf::String(L"    胜利\n硬币+" +
                 sf::String(std::to_string((l_level + 1) * 10))),
      l_infos,
      sf::Vector2f(
          m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize()),
      m_stateMgr->GetContext()->m_resolution, m_font, [this]() {
        m_stateMgr->Remove(StateType::Game);
        m_stateMgr->SwitchTo(StateType::MainMenu);
      });
  std::ifstream inStore("res/config/store.json");
  nlohmann::json data_store = nlohmann::json::parse(inStore);
  inStore.close();
  data_store["coin"] =
      static_cast<int>(data_store["coin"]) + (l_level + 1) * 10;
  std::ofstream outStore("res/config/store.json");
  outStore << data_store;
  outStore.close();
}

void State_Game::YouLose(int l_level) {
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  std::unordered_map<int, int> l_infos;
  m_settlement = std::make_shared<gl::Settlement>(
      sf::String(L"      败北\n请多用道具"), l_infos,
      sf::Vector2f(
          m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize()),
      m_stateMgr->GetContext()->m_resolution, m_font, [this]() {
        m_stateMgr->Remove(StateType::Game);
        m_stateMgr->SwitchTo(StateType::MainMenu);
    });
}
