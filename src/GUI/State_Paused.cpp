#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager *l_stateManager) : BaseState(l_stateManager) {}

State_Paused::~State_Paused() = default;

void State_Paused::OnCreate() {
  SetTransparent(true); // Set our transparency flag.
  m_font = sf::Font("res/fonts/arial.ttf");
  m_text = std::make_unique<sf::Text>(m_font, "PAUSED", 14);
  m_text->setStyle(sf::Text::Bold);
  const sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_text->setOrigin({m_text->getLocalBounds().position.x +m_text->getLocalBounds().size.x / 2.0f, m_text->getLocalBounds().position.y + m_text->getLocalBounds().size.y / 2.0f});
  m_text->setPosition({static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f});
  m_rect.setSize(sf::Vector2f(windowSize));
  m_rect.setPosition({0, 0});
  m_rect.setFillColor(sf::Color(0, 0, 0, 150));
}

void State_Paused::OnDestroy()
{
}

void State_Paused::Draw()
{
  sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_wind->draw(m_rect);
  l_wind->draw(*m_text);
}

void State_Paused::Activate() {}
void State_Paused::Deactivate() {}
void State_Paused::Update(const sf::Time &l_time) {}