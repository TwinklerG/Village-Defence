#include "State_Levels.h"
#include "StateManager.h"

int State_Levels::m_LevelSum = 4;

State_Levels::State_Levels(StateManager *l_stateManager) : BaseState(l_stateManager) {
}

State_Levels::~State_Levels() = default;

void State_Levels::OnCreate() {
  m_font.loadFromFile("res/fonts/CONSOLAB.TTF");
  m_title.setFont(m_font);
  m_title.setString("Levels");
  m_title.setCharacterSize(120);
  m_title.setOrigin(m_title.getLocalBounds().width / 2, m_title.getLocalBounds().height / 2);
  m_title.setPosition(static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().x) / 2.0f,
                      static_cast<float>(m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize().y) / 10.0f);
  m_rects = std::vector<sf::RectangleShape>(m_LevelSum);
  m_labels = std::vector<sf::Text>(m_LevelSum);
  const auto l_buttonSize = sf::Vector2f(600.0f, 100.0f);
  auto l_buttonPos = sf::Vector2f(static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().x) / 2.0f,
                                  static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().y) / 3.0f);
  for (int i = 0; i < m_LevelSum; ++i) {
    constexpr auto l_buttonPadding = 4;
    m_rects[i].setSize(l_buttonSize);
    m_rects[i].setFillColor(sf::Color::Red);
    m_rects[i].setOrigin(l_buttonSize.x / 2.0f, l_buttonSize.y / 2.0f);
    m_rects[i].setPosition(l_buttonPos);
    m_labels[i].setFont(m_font);
    m_labels[i].setString("Level " + std::to_string(i));
    m_labels[i].setCharacterSize(40);
    sf::FloatRect rect = m_labels[i].getLocalBounds();
    m_labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    m_labels[i].setPosition(l_buttonPos);
    l_buttonPos.y += (l_buttonSize.y + l_buttonPadding);
  }

  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Levels, "Key_Escape", &State_Levels::MainMenu, this);
}

void State_Levels::OnDestroy() {
  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->RemoveCallback(StateType::Levels, "Key_Escape");
}

void State_Levels::Update(const sf::Time &l_time) {
  if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    m_isMouseLeft = false;
  }
  for (int i = 0; i < m_LevelSum; ++i) {
    if (const sf::Vector2i l_pos = sf::Mouse::getPosition(*m_stateMgr->GetContext()->m_wind->GetRenderWindow());
      static_cast<float>(l_pos.x) >= m_rects[i].getPosition().x - m_rects[i].getSize().x / 2.0f &&
      static_cast<float>(l_pos.x) <= m_rects[i].getPosition().x + m_rects[i].getSize().x / 2.0f &&
      static_cast<float>(l_pos.y) >= m_rects[i].getPosition().y - m_rects[i].getSize().y / 2.0f &&
      static_cast<float>(l_pos.y) <= m_rects[i].getPosition().y + m_rects[i].getSize().y / 2.0f) {
      m_rects[i].setFillColor(sf::Color::White);
      m_labels[i].setFillColor(sf::Color::Black);
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_isMouseLeft) {
        // std::cout << "Mouse Left Clicked\n";
        if (m_stateMgr->HasState(StateType::Game)) {
          m_stateMgr->Remove(StateType::Game);
          m_stateMgr->ProcessRequests();
        }
        m_stateMgr->GetContext()->m_level = i;
        m_stateMgr->SwitchTo(StateType::Game);
        m_isMouseLeft = true;
      }
    } else {
      m_rects[i].setFillColor(sf::Color::Red);
      m_labels[i].setFillColor(sf::Color::White);
    }
  }
}

void State_Levels::Draw() {
  sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_wind->draw(m_title);
  for (int i = 0; i < m_LevelSum; ++i) {
    l_wind->draw(m_rects[i]);
    l_wind->draw(m_labels[i]);
  }
}

void State_Levels::MainMenu(EventDetails *l_details) {
  m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Levels::Activate() {
  m_isMouseLeft = true;
}

void State_Levels::Deactivate() {
}
