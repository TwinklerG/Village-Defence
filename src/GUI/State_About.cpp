#include "State_About.h"
#include "StateManager.h"

State_About::State_About(StateManager *l_stateManager)
    : BaseState(l_stateManager) {}

State_About::~State_About() {};

void State_About::OnCreate()
{
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::About, "Key_Escape", &State_About::MainMenu, this);

  m_font.loadFromFile("res/fonts/CONSOLAZ.TTF");
  m_content.setFont(m_font);
  m_content.setString("Vellege Defence\n\nCopyright GeLU & Powered by SFML\n");
  m_content.setCharacterSize(44);
  m_content.setColor(sf::Color::White);
  m_content.setPosition((1920 - m_content.getLocalBounds().width) / 2, 1080);
}

void State_About::OnDestroy()
{
}

void State_About::Update(const sf::Time &l_time)
{
  m_content.setPosition(m_content.getPosition().x, m_content.getPosition().y - l_time.asSeconds() * 80);
}

void State_About::Draw()
{
  m_stateMgr->GetContext()->m_wind->GetRenderWindow()->draw(m_content);
}

void State_About::MainMenu(EventDetails *l_details)
{
  m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_About::Activate() {}
void State_About::Deactivate() {}