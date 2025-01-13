#include "State_MainMenu.h"

#include <iostream>

#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager *l_stateManager) : BaseState(l_stateManager), m_title(nullptr) {
}

State_MainMenu::~State_MainMenu() = default;

void State_MainMenu::OnCreate() {
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const sf::Vector2u l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_title = std::make_unique<sf::Text>(m_font, L"主菜单", static_cast<unsigned int>(l_windowSize.y) / 10);
  m_title->setOrigin({m_title->getLocalBounds().size.x / 2.0f, m_title->getLocalBounds().size.y / 2.0f});
  m_title->setPosition({static_cast<float>(l_windowSize.x) / 2.0f, static_cast<float>(l_windowSize.y) / 10.0f * 2.0f});
  const auto l_size = sf::Vector2f(static_cast<float>(l_windowSize.x) / 3.0f,
                                   static_cast<float>(l_windowSize.y) / 10.2f);
  const auto l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                                  static_cast<float>(l_windowSize.y) / 10.0f * 4.0f);
  const auto l_delta = sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 10.0f);
  const auto l_buttonInfos = std::vector<std::pair<sf::String, StateType> >({
    {L"关卡", StateType::Levels},
    {L"存档", StateType::Save},
    {L"读档", StateType::Load},
    {L"商店", StateType::Store},
    {L"关于", StateType::About},
  });
  for (int i = 0; i < l_buttonInfos.size(); ++i) {
    m_buttons.emplace_back(l_buttonInfos[i].first, l_pos + static_cast<float>(i) * l_delta, l_size,
                           l_windowSize.y / 20,
                           m_font, [this, l_buttonInfos, i]() {
                             m_stateMgr->SwitchTo(l_buttonInfos[i].second);
                           });
  }
  m_buttons[1].SetCallBack([this, l_windowSize]() {
    if (m_stateMgr->HasState(StateType::Save)) {
      m_stateMgr->Remove(StateType::Save);
      m_stateMgr->ProcessRequests();
    }
    if (m_stateMgr->HasState(StateType::Game)) {
      m_stateMgr->SwitchTo(StateType::Save);
    } else {
      m_toast = std::make_shared<gl::Toast>(L"目前无游戏记录", m_font, sf::Vector2f(l_windowSize));
    }
  });
  m_buttons[2].SetCallBack([this]() {
    if (m_stateMgr->HasState(StateType::Load)) {
      m_stateMgr->Remove(StateType::Load);
      m_stateMgr->ProcessRequests();
    }
    m_stateMgr->SwitchTo(StateType::Load);
  });
  m_buttons.emplace_back(L"退出游戏", l_pos + static_cast<float>(l_buttonInfos.size()) * l_delta, l_size,
                         l_windowSize.y / 20, m_font, [this]() {
                           m_stateMgr->GetContext()->m_wind->Close();
                         });
  m_buttons.emplace_back(
    L"设置", sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f * 9, static_cast<float>(l_windowSize.y) / 10.0f),
    sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f, static_cast<float>(l_windowSize.y) / 10.0f),
    l_windowSize.y / 30, m_font, [
      this]() {
      this->m_stateMgr->SwitchTo(StateType::Setting);
    });
}

void State_MainMenu::OnDestroy() {
}

void State_MainMenu::Activate() {
  std::cout << (m_buttons.back().GetText().getString() == L"返回游戏" ? "exist" : "not-exist") << " " << m_stateMgr->
      HasState(StateType::Game) << "\n";
  if (m_buttons.back().GetText().getString() != L"返回游戏" && m_stateMgr->HasState(StateType::Game)) {
    m_buttons.pop_back();
    const auto l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    m_buttons.emplace_back(
      L"返回游戏", sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f, static_cast<float>(l_windowSize.y) / 10.0f),
      sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f, static_cast<float>(l_windowSize.y) / 10.0f),
      l_windowSize.y / 30, m_font, [
        this]() {
        this->m_stateMgr->SwitchTo(StateType::Game);
      });
  } else if (m_buttons.back().GetText().getString() == L"返回游戏" && !m_stateMgr->HasState(StateType::Game)) {
    m_buttons.pop_back();
    const auto l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    m_buttons.emplace_back(
      L"设置", sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f * 9, static_cast<float>(l_windowSize.y) / 10.0f),
      sf::Vector2f(static_cast<float>(l_windowSize.x) / 10.0f, static_cast<float>(l_windowSize.y) / 10.0f),
      l_windowSize.y / 30, m_font, [this]() {
        this->m_stateMgr->SwitchTo(StateType::Setting);
      });
  }
}

void State_MainMenu::Draw() {
  sf::RenderWindow *l_window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_window->draw(*m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*l_window);
  }
  if (m_toast) {
    m_toast->Render(*l_window);
  }
}

void State_MainMenu::Update(const sf::Time &l_time) {
  if (m_toast) {
    if (m_toast->Update(l_time)) {
      m_toast = nullptr;
    }
  }
}

void State_MainMenu::Deactivate() {
}
