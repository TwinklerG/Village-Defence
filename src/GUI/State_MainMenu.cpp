#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager *l_stateManager) : BaseState(l_stateManager) {
}

State_MainMenu::~State_MainMenu() = default;

void State_MainMenu::OnCreate() {
  m_font.loadFromFile("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  const sf::Vector2u l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_title = sf::Text(L"主菜单", m_font, static_cast<unsigned int>(l_windowSize.y) / 10);
  m_title.setOrigin(m_title.getLocalBounds().width / 2.0f, m_title.getLocalBounds().height / 2.0f);
  m_title.setPosition(static_cast<float>(l_windowSize.x) / 2.0f, static_cast<float>(l_windowSize.y) / 10.0f * 2.0f);
  const auto l_size = sf::Vector2f(static_cast<float>(l_windowSize.x) / 3.0f,
                                   static_cast<float>(l_windowSize.y) / 10.2f);
  const auto l_pos = sf::Vector2f(static_cast<float>(l_windowSize.x) / 2.0f,
                                  static_cast<float>(l_windowSize.y) / 10.0f * 4.0f);
  const auto l_delta = sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 10.0f);
  const auto l_buttonInfos = std::vector<std::pair<sf::String, StateType> >({
    {L"新游戏", StateType::Game},
    {L"关卡", StateType::Levels},
    {L"读档", StateType::Load},
    {L"商店", StateType::Store},
    {L"关于", StateType::About},
  });
  for (int i = 0; i < l_buttonInfos.size(); ++i) {
    m_buttons.emplace_back(l_buttonInfos[i].first, l_pos + static_cast<float>(i) * l_delta, l_size, l_windowSize.y / 20,
                           m_font, [this, l_buttonInfos, i]() {
                             m_stateMgr->SwitchTo(l_buttonInfos[i].second);
                           });
  }
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
  if (m_stateMgr->HasState(StateType::Levels)) {
    m_stateMgr->Remove(StateType::Levels);
  }
  if (m_stateMgr->HasState(StateType::Game) && m_buttons[0].GetText().getString() == L"新游戏") {
    sf::Text l_text = m_buttons[0].GetText();
    l_text.setString(L"返回游戏");
    const auto l_lb = l_text.getLocalBounds();
    l_text.setOrigin(l_lb.left + l_lb.width / 2.0f, l_lb.top + l_lb.height / 2.0f);
    m_buttons[0].SetText(l_text);
    m_buttons.pop_back();
    m_buttons.insert(m_buttons.begin() + 1, gl::Button(L"存档", m_buttons[0].GetPosition(), m_buttons[0].GetSize(),
                                                       m_buttons[0].GetCharSize(), m_font, []() {
                                                       }));
    const auto l_windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    m_buttons[0].SetPosition(m_buttons[0].GetPosition() - sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 10.0f));
    m_title.setPosition(m_title.getPosition() - sf::Vector2f(0, static_cast<float>(l_windowSize.y) / 10.0f));
  }
}

void State_MainMenu::Draw() {
  sf::RenderWindow *window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  window->draw(m_title);
  for (auto &l_button: m_buttons) {
    l_button.UpdateRender(*window);
  }
}

void State_MainMenu::Update(const sf::Time &l_time) {
}

void State_MainMenu::Deactivate() {
}
