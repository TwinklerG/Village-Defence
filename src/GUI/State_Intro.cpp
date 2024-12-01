#include "State_Intro.h"
#include "StateManager.h"
#include <random>

// Random Int Generator
std::random_device rd;
std::mt19937 gen(rd());
int randint(const int low, const int high)
{
  std::uniform_int_distribution<> dist(low, high);
  return dist(gen);
}

float State_Intro::m_AnimationTime = 1.0f;
int State_Intro::m_SpritesSum = 20;

State_Intro::State_Intro(StateManager *l_stateManager)
    : BaseState(l_stateManager) {}

State_Intro::~State_Intro() {}

void State_Intro::OnCreate()
{
  m_timePassed = 0.0f;
  sf::Vector2u windowSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_introTexture.loadFromFile("res/intro.png");
  m_introSprite.setTexture(m_introTexture);
  m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
  m_introSprite.setPosition(windowSize.x / 2.0f, 0);
  m_font.loadFromFile("res/arial.ttf");
  m_text.setFont(m_font);
  m_text.setString({"Press SPACE to continue"});
  m_text.setCharacterSize(20);
  sf::FloatRect textRect = m_text.getLocalBounds();
  m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 3.0f * 2);
  EventManager *evMgr = m_stateMgr->GetContext()->m_eventManager;
  evMgr->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);

  m_textures = std::vector<sf::Texture>(m_SpritesSum);
  m_increments = std::vector<sf::Vector2i>(m_SpritesSum);
  for (int i = 0; i < m_SpritesSum; ++i)
  {
    m_textures[i].loadFromFile("res/STATE_INTRO_file_1.png");
    m_sprites.emplace_back(sf::Sprite(m_textures[i]));
    m_increments[i] = sf::Vector2i(randint(100, 400), randint(100, 400));
  }
}

void State_Intro::OnDestroy()
{
  EventManager *evMgr = m_stateMgr->GetContext()->m_eventManager;
  evMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Update(const sf::Time &l_time)
{
  RestartClock();
  MoveSprites();
  if (m_timePassed < m_AnimationTime)
  { // Less than five seconds.
    m_timePassed += l_time.asSeconds();
    m_introSprite.setPosition(m_introSprite.getPosition().x, m_introSprite.getPosition().y + (m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().y / (m_AnimationTime * 2) * l_time.asSeconds()));
  }
}

void State_Intro::Draw()
{
  sf::RenderWindow *window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  for (const auto &l_sp : m_sprites)
  {
    window->draw(l_sp);
  }
  window->draw(m_introSprite);
  if (m_timePassed >= m_AnimationTime)
  {
    window->draw(m_text);
  }
}

void State_Intro::Continue(EventDetails *l_details)
{
  if (m_timePassed >= m_AnimationTime)
  {
    m_stateMgr->SwitchTo(StateType::MainMenu);
    m_stateMgr->Remove(StateType::Intro);
  }
}

void State_Intro::MoveSprites()
{
  for (int i = 0; i < m_SpritesSum; ++i)
  {
    sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
    sf::Vector2u l_spSize = m_textures[i].getSize();
    sf::Vector2f l_spPos = m_sprites[i].getPosition();
    if ((l_spPos.x + l_spSize.x > l_windSize.x && m_increments[i].x > 0) || (l_spPos.x < 0 && m_increments[i].x < 0))
    {
      m_increments[i].x = -m_increments[i].x;
    }
    if ((l_spPos.y + l_spSize.y > l_windSize.y && m_increments[i].y > 0) || (l_spPos.y < 0 && m_increments[i].y < 0))
    {
      m_increments[i].y = -m_increments[i].y;
    }
    m_sprites[i].setPosition(l_spPos.x + m_increments[i].x * m_elapsed.asSeconds(), l_spPos.y + m_increments[i].y * m_elapsed.asSeconds());
  }
}
void State_Intro::RestartClock() { m_elapsed = m_clock.restart(); }

void State_Intro::Activate() {}
void State_Intro::Deactivate() {}