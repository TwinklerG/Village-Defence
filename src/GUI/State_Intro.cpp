#include "State_Intro.h"
#include "StateManager.h"
#include "../Utils/Utils.hpp"

float State_Intro::m_AnimationTime = 1.0f;
int State_Intro::m_SpritesSum = 20;

State_Intro::State_Intro(StateManager *l_stateManager)
  : BaseState(l_stateManager), m_text(nullptr), m_title(nullptr) {
}

State_Intro::~State_Intro() = default;

void State_Intro::OnCreate() {
  m_timePassed = 0.0f;
  const sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  m_text = std::make_unique<sf::Text>(m_font, L"点击空格继续", windowSize.y / 50);
  const sf::FloatRect textRect = m_text->getLocalBounds();
  m_text->setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
  m_text->setPosition({static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 3.0f * 2});
  m_title = std::make_unique<sf::Text>(m_font, L"村庄保卫战", windowSize.y / 6);
  m_title->setOrigin({m_title->getLocalBounds().size.x / 2, m_title->getLocalBounds().size.y});
  m_title->setPosition({static_cast<float>(windowSize.x) / 2.0f, 0});
  m_textures = std::vector<sf::Texture>(m_SpritesSum);
  m_increments = std::vector<sf::Vector2i>(m_SpritesSum);
  for (int i = 0; i < m_SpritesSum; ++i) {
    m_textures[i] = sf::Texture("res/img/states/" + m_stateMgr->GetContext()->m_resolution + "/intro_figure.png");
    m_sprites.emplace_back(m_textures[i]);
    m_increments[i] = sf::Vector2i(gl::RandInt(100, 400), gl::RandInt(100, 400));
  }
}

void State_Intro::OnDestroy() {
}

void State_Intro::Update(const sf::Time &l_time) {
  RestartClock();
  MoveSprites();
  if (m_timePassed < m_AnimationTime) {
    // Less than five seconds.
    m_timePassed += l_time.asSeconds();
    m_title->setPosition({
      m_title->getPosition().x,
      m_title->getPosition().y + static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().y) /
      (
        m_AnimationTime * 2.0f) * l_time.asSeconds()
    });
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    m_stateMgr->SwitchTo(StateType::MainMenu);
  }
}

void State_Intro::Draw() {
  sf::RenderWindow *window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  for (const auto &l_sp: m_sprites) {
    window->draw(l_sp);
  }
  window->draw(*m_title);
  if (m_timePassed >= m_AnimationTime) {
    window->draw(*m_text);
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
    m_sprites[i].setPosition({
      l_spPos.x + static_cast<float>(m_increments[i].x) * m_elapsed.asSeconds(),
      l_spPos.y + static_cast<float>(m_increments[i].y) * m_elapsed.asSeconds()
    });
  }
}

void State_Intro::RestartClock() {
  m_elapsed = m_clock.restart();
}

void State_Intro::Activate() {
}

void State_Intro::Deactivate() {
}
