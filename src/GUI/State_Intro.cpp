#include "State_Intro.h"
#include "StateManager.h"
#include "../Utils/Utils.hpp"
#include <random>

float State_Intro::m_AnimationTime = 1.0f;
int State_Intro::m_SpritesSum = 20;

State_Intro::State_Intro(StateManager *l_stateManager)
  : BaseState(l_stateManager) {
}

State_Intro::~State_Intro() = default;

void State_Intro::OnCreate() {
  m_timePassed = 0.0f;
  const sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_font.loadFromFile("res/fonts/CONSOLAZ.TTF");
  m_text.setFont(m_font);
  m_text.setString({"Press SPACE to continue"});
  m_text.setCharacterSize(windowSize.y / 50);
  const sf::FloatRect textRect = m_text.getLocalBounds();
  m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  m_text.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 3.0f * 2);
  m_title.setFont(m_font);
  m_title.setString("Village Defence");
  m_title.setCharacterSize(windowSize.y / 6);
  m_title.setOrigin(m_title.getLocalBounds().width / 2, m_title.getLocalBounds().height);
  m_title.setPosition(static_cast<float>(windowSize.x) / 2.0f, 0);
  EventManager *evMgr = m_stateMgr->GetContext()->m_eventManager;
  evMgr->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);

  m_textures = std::vector<sf::Texture>(m_SpritesSum);
  m_increments = std::vector<sf::Vector2i>(m_SpritesSum);
  for (int i = 0; i < m_SpritesSum; ++i) {
    m_textures[i].loadFromFile("res/img/states/" + m_stateMgr->GetContext()->m_resolution + "/intro_figure.png");
    m_sprites.emplace_back(m_textures[i]);
    m_increments[i] = sf::Vector2i(Utils::RandInt(100, 400), Utils::RandInt(100, 400));
  }
}

void State_Intro::OnDestroy() {
  EventManager *evMgr = m_stateMgr->GetContext()->m_eventManager;
  evMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Update(const sf::Time &l_time) {
  RestartClock();
  MoveSprites();
  if (m_timePassed < m_AnimationTime) {
    // Less than five seconds.
    m_timePassed += l_time.asSeconds();
    m_title.setPosition(m_title.getPosition().x,
                        m_title.getPosition().y + static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()
                          ->getSize().y) / (m_AnimationTime * 2.0f) *
                        l_time.asSeconds());
  }
}

void State_Intro::Draw() {
  sf::RenderWindow *window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  for (const auto &l_sp: m_sprites) {
    window->draw(l_sp);
  }
  window->draw(m_title);
  if (m_timePassed >= m_AnimationTime) {
    window->draw(m_text);
  }
}

void State_Intro::Continue(EventDetails *l_details) {
  if (m_timePassed >= m_AnimationTime) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
    m_stateMgr->Remove(StateType::Intro);
  }
}

void State_Intro::MoveSprites() {
  for (int i = 0; i < m_SpritesSum; ++i) {
    const sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    const sf::Vector2u l_spSize = m_textures[i].getSize();
    const sf::Vector2f l_spPos = m_sprites[i].getPosition();
    if ((l_spPos.x + static_cast<float>(l_spSize.x) > static_cast<float>(l_windSize.x) && m_increments[i].x > 0) || (
          l_spPos.x < 0 && m_increments[i].x < 0)) {
      m_increments[i].x = -m_increments[i].x;
    }
    if ((l_spPos.y + static_cast<float>(l_spSize.y) > static_cast<float>(l_windSize.y) && m_increments[i].y > 0) || (
          l_spPos.y < 0 && m_increments[i].y < 0)) {
      m_increments[i].y = -m_increments[i].y;
    }
    m_sprites[i].setPosition(l_spPos.x + static_cast<float>(m_increments[i].x) * m_elapsed.asSeconds(),
                             l_spPos.y + static_cast<float>(m_increments[i].y) * m_elapsed.asSeconds());
  }
}

void State_Intro::RestartClock() { m_elapsed = m_clock.restart(); }

void State_Intro::Activate() {
}

void State_Intro::Deactivate() {
}
