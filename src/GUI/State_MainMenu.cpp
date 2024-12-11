#include "State_MainMenu.h"
#include "StateManager.h"

int State_MainMenu::m_ButtonSum = 5;

State_MainMenu::State_MainMenu(StateManager *l_stateManager) : BaseState(l_stateManager) {
}

State_MainMenu::~State_MainMenu() = default;

void State_MainMenu::OnCreate() {
  m_rects = std::vector<sf::RectangleShape>(State_MainMenu::m_ButtonSum);
  m_labels = std::vector<sf::Text>(State_MainMenu::m_ButtonSum);
  m_font.loadFromFile("res/fonts/CONSOLAB.TTF");
  m_text.setFont(m_font);
  m_text.setString(sf::String("MAIN MENU"));
  m_text.setCharacterSize(100);
  const sf::FloatRect textRect = m_text.getLocalBounds();
  m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
  m_text.setPosition(static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().x) / 2.0f,
                     static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().y) / 3.0f);
  m_buttonSize = sf::Vector2f(600.0f, 100.0f);
  m_buttonPos = sf::Vector2f(static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().x) / 2.0f,
                             static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().y) / 20.0f * 9.0f);
  m_buttonPadding = 4; // 4px.
  std::vector<std::string> str(m_ButtonSum);
  str[0] = "NEW GAME";
  str[1] = "LOAD SAVED";
  str[2] = "STORE";
  str[3] = "ABOUT";
  str[4] = "EXIT";
  for (int i = 0; i < m_ButtonSum; ++i) {
    sf::Vector2f buttonPosition(m_buttonPos.x,
                                m_buttonPos.y + static_cast<float>(i) * (
                                  m_buttonSize.y + static_cast<float>(m_buttonPadding)));
    m_rects[i].setSize(m_buttonSize);
    m_rects[i].setFillColor(sf::Color::Red);
    m_rects[i].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
    m_rects[i].setPosition(buttonPosition);
    m_labels[i].setFont(m_font);
    m_labels[i].setString(sf::String(str[i]));
    m_labels[i].setCharacterSize(40);
    const sf::FloatRect rect = m_labels[i].getLocalBounds();
    m_labels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    m_labels[i].setPosition(buttonPosition);
  }
  EventManager *evMgr = m_stateMgr->GetContext()->m_eventManager;
  evMgr->AddCallback(StateType::MainMenu, "Mouse_Left", &State_MainMenu::MouseClick, this);
}

void State_MainMenu::OnDestroy() {
  EventManager *evMgr = m_stateMgr->GetContext()->m_eventManager;
  evMgr->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::Activate() {
  if (m_stateMgr->HasState(StateType::Game) && m_labels[0].getString() == "NEW GAME") {
    m_labels[0].setString(sf::String("RESUME"));
    sf::FloatRect rect = m_labels[0].getLocalBounds();
    m_labels[0].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
  }
}

void State_MainMenu::MouseClick(EventDetails *l_details) {
  const sf::Vector2i mousePos = l_details->m_mouse;
  const float halfX = m_buttonSize.x / 2.0f;
  const float halfY = m_buttonSize.y / 2.0f;
  for (int i = 0; i < m_ButtonSum; ++i) {
    if (static_cast<float>(mousePos.x) >= m_rects[i].getPosition().x - halfX && static_cast<float>(mousePos.x) <=
        m_rects[i].getPosition().x + halfX && static_cast<float>(mousePos
          .y) >= m_rects[i].getPosition().y - halfY && static_cast<float>(mousePos.y) <= m_rects[i].getPosition().y +
        halfY) {
      if (i == 0) {
        m_stateMgr->SwitchTo(StateType::Game);
      } else if (i == 1) {
        m_stateMgr->SwitchTo(StateType::Levels);
      } else if (i == 2) {
        m_stateMgr->SwitchTo(StateType::Store);
      } else if (i == 3) {
        m_stateMgr->SwitchTo(StateType::About);
      } else if (i == 4) {
        m_stateMgr->GetContext()->m_wind->Close();
      }
    }
  }
}

void State_MainMenu::Draw() {
  sf::RenderWindow *window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  window->draw(m_text);
  for (int i = 0; i < m_ButtonSum; ++i) {
    window->draw(m_rects[i]);
    window->draw(m_labels[i]);
  }
}

void State_MainMenu::Update(const sf::Time &l_time) {
  for (int i = 0; i < m_ButtonSum; ++i) {
    const sf::Vector2i l_pos = sf::Mouse::getPosition(*m_stateMgr->GetContext()->m_wind->GetRenderWindow());
    if (static_cast<float>(l_pos.x) >= m_rects[i].getPosition().x - m_rects[i].getSize().x / 2 &&
        static_cast<float>(l_pos.x) <= m_rects[i].getPosition().x + m_rects[i].getSize().x / 2 &&
        static_cast<float>(l_pos.y) >= m_rects[i].getPosition().y - m_rects[i].getSize().y / 2 &&
        static_cast<float>(l_pos.y) <= m_rects[i].getPosition().y + m_rects[i].getSize().y / 2) {
      m_rects[i].setFillColor(sf::Color::White);
      m_labels[i].setFillColor(sf::Color::Black);
    } else {
      m_rects[i].setFillColor(sf::Color::Red);
      m_labels[i].setFillColor(sf::Color::White);
    }
  }
}

void State_MainMenu::Deactivate() {
}
