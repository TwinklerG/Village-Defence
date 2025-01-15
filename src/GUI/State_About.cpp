#include "State_About.h"
#include "StateManager.h"

State_About::State_About(StateManager *l_stateManager)
  : BaseState(l_stateManager), m_content(nullptr) {
}

State_About::~State_About() = default;

void State_About::OnCreate() {
  const sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  m_content = std::make_unique<sf::Text>(
    m_font,
    L"村庄保卫战\n\n龚亮创建 & SFML赋能\n\n除欢迎和菜单界面，你都可以通过敲击Escape键返回上一级\n\n本游戏提供四个关卡，难度递增\n\n"
    "提供四种防御塔，它们的攻击伤害、攻击范围、子弹速度各异\n\n提供三种入侵者，它们的血量和移速各异\n\n提供两种道具，分别能减速入侵者和提速防御塔\n\n欢迎各种形式的探索，你可以通过修改JSON实现深度自定义\n\n"
    "现在，你可以敲击Escape进入主菜单",
    static_cast<unsigned int>(m_stateMgr->GetContext()->m_atomResolution.x) / 3 * 2);
  m_content->setFillColor(sf::Color::White);
  m_content->setOrigin({m_content->getLocalBounds().size.x / 2.0f, m_content->getLocalBounds().size.y / 2.0f});
  m_content->setPosition({
    static_cast<float>(l_wind->getSize().x) / 2.0f,
    static_cast<float>(l_wind->getSize().y) + m_content->getLocalBounds().size.y / 2.0f
  });
}

void State_About::OnDestroy() {
}

void State_About::Update(const sf::Time &l_time) {
  m_content->setPosition({m_content->getPosition().x, m_content->getPosition().y - l_time.asSeconds() * 80});
  if (m_content->getPosition().y + m_content->getLocalBounds().size.y / 2 < 0
      || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_About::Draw() {
  m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(*m_content);
}

void State_About::Activate() {
}

void State_About::Deactivate() {
}
