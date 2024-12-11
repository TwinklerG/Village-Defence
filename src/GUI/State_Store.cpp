#include "State_Store.h"
#include <cassert>
#include "StateManager.h"

PropType sToPropType(const std::string &s) {
  if (s == "SLOW") {
    return PropType::SLOW;
  }
  if (s == "ACCELERATE") {
    return PropType::ACCELERATE;
  }
  if (s == "TROPHY") {
    return PropType::TROPHY;
  }
  throw std::invalid_argument("Invalid PropType");
}


State_Store::State_Store(StateManager *l_stateManager) : BaseState(l_stateManager) {
}

State_Store::~State_Store() = default;

void State_Store::OnCreate() {
  m_font.loadFromFile("res/fonts/CONSOLAB.TTF");
  m_title.setFont(m_font);
  m_title.setString("STORE");
  m_title.setCharacterSize(100);
  m_title.setOrigin(m_title.getLocalBounds().width / 2.0f, m_title.getLocalBounds().height / 2.0f);
  m_title.setPosition(static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().x) / 2.0f,
                      static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().y) / 10.0f);
  LoadProps();
  LoadGoods();


  EventManager *envMgr = m_stateMgr->GetContext()->m_eventManager;
  envMgr->AddCallback(StateType::Store, "Key_Escape", &State_Store::MainMenu, this);
}

void State_Store::LoadGoods() {
  const sf::Vector2u l_windSize = m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  std::fstream inCoin, in;
  inCoin.open("res/config/coin.cfg");
  inCoin >> m_coin;
  inCoin.close();
  m_coinText.setFont(m_font);
  m_coinText.setString("Coin: " + std::to_string(m_coin));
  m_coinText.setCharacterSize(40);
  m_coinText.setOrigin(m_coinText.getLocalBounds().width, 0);
  m_coinText.setPosition(static_cast<float>(l_windSize.x) - m_coinText.getLocalBounds().width / 2.0f,
                         m_coinText.getLocalBounds().height / 2.0f);
  in.open("res/config/store.cfg");
  std::string line{};
  std::getline(in, line);
  const int choiceSum = std::stoi(line);
  for (int i = 0; i < choiceSum; ++i) {
    std::string l_title, l_description;
    std::getline(in, l_title);
    std::getline(in, l_description);
    std::getline(in, line);
    const int cost = std::stoi(line);
    m_choices.emplace_back(l_title, l_description, cost,
                           sf::Vector2f(static_cast<float>(l_windSize.x) / 13.0f * 3.0f,
                                        static_cast<float>(l_windSize.y) / 3.0f * 2.0f)
                           , sf::Vector2f(static_cast<float>(l_windSize.x) / 13.0f * static_cast<float>(2.5f + 4.0 * i),
                                          static_cast<float>(l_windSize.y) / 5.0f * 3.0f),
                           m_font, m_props[sToPropType(l_title)]);
  }
  in.close();
}

void State_Store::LoadProps() {
  std::fstream in;
  in.open("res/config/prop.cfg");
  int l_propSum;
  in >> l_propSum;
  for (int i = 0; i < l_propSum; ++i) {
    std::string l_propTypeStr;
    int l_propCnt;
    in >> l_propTypeStr >> l_propCnt;
    m_props[sToPropType(l_propTypeStr)] = l_propCnt;
  }
  in.close();
}

void State_Store::MainMenu(EventDetails *l_details) { m_stateMgr->SwitchTo(StateType::MainMenu); }

void State_Store::Update(const sf::Time &l_time) {
  for (auto &l_choice: m_choices) {
    if (l_choice.Update(m_stateMgr->GetContext()->m_wind->GetRenderWindow())) {
      if (m_coin < l_choice.GetPrice()) {
        std::cout << "Coin NOT Enough\n";
      } else {
        m_coin -= l_choice.GetPrice();
        m_coinText.setString("Coin: " + std::to_string(m_coin));
        ++m_props[sToPropType(l_choice.GetPropName())];
      }
    }
  }
}

void State_Store::Draw() {
  sf::RenderWindow *l_wind = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_wind->draw(m_title);
  for (const auto &l_choice: m_choices) {
    l_choice.Draw(l_wind);
  }
  l_wind->draw(m_coinText);
}

void State_Store::Activate() {
  for (auto &l_choice: m_choices) {
    l_choice.SetIsMouseLeft(true);
  }
}

void State_Store::Deactivate() {
  SaveProps();
}

void State_Store::OnDestroy() {
  SaveProps();
}

void State_Store::SaveProps() {
  std::ofstream out;
  out.open("res/config/prop.cfg", std::ios::out);
  const size_t l_propSum = m_props.size();
  out << l_propSum << "\n";
  for (auto &[l_propType, l_propCnt]: m_props) {
    if (l_propType == PropType::SLOW) {
      out << "SLOW " + std::to_string(l_propCnt) + "\n";
    } else if (l_propType == PropType::ACCELERATE) {
      out << "ACCELERATE " + std::to_string(l_propCnt) + "\n";
    } else if (l_propType == PropType::TROPHY) {
      out << "TROPHY " + std::to_string(l_propCnt) + "\n";
    } else {
      throw std::invalid_argument("Illegal Prop Type");
    }
  }
  out.close();
  out.open("res/config/coin.cfg", std::ios::out);
  out << m_coin;
  out.close();
}

StoreChoice::StoreChoice(const std::string &l_name, const std::string &l_description, const int l_price,
                         const sf::Vector2f &l_size, const sf::Vector2f &l_pos,
                         const sf::Font &l_font, const int l_cnt) {
  m_rect.setSize(l_size);
  m_rect.setOrigin(l_size.x / 2.0f, l_size.y / 2.0f);
  m_rect.setPosition(l_pos);
  m_rect.setFillColor(sf::Color::Red);
  m_name.setFont(l_font);
  m_name.setString(l_name);
  m_name.setCharacterSize(50);
  m_name.setOrigin(m_name.getLocalBounds().width / 2.0f, m_name.getLocalBounds().height / 2.0f);
  m_name.setPosition(l_pos.x, l_pos.y - l_size.y / 2.0f + m_name.getLocalBounds().height);
  m_description.setFont(l_font);
  std::string tmp;
  for (int i = 0; i < l_description.size(); ++i) {
    if (i > 0 && l_description[i] == '\\' && l_description[i + 1] == 'n') {
      tmp += '\n';
      ++i;
      continue;
    }
    tmp += l_description[i];
  }
  m_description.setString(tmp);
  m_description.setCharacterSize(50);
  m_description.setOrigin(m_description.getLocalBounds().width / 2, m_description.getLocalBounds().height / 2);
  m_description.setPosition(l_pos.x, l_pos.y + 35);
  m_description.setLineSpacing(1.0f);
  m_cnt = l_cnt;
  m_cntText.setFont(l_font);
  m_cntText.setString("Left: " + std::to_string(l_cnt));
  m_cntText.setCharacterSize(40);
  m_cntText.setOrigin(m_cntText.getLocalBounds().width / 2.0f, m_cntText.getLocalBounds().height / 2.0f);
  m_cntText.setPosition(l_pos.x, l_pos.y + l_size.y / 4.0f - m_cntText.getLocalBounds().height / 2.0f);
  m_price = l_price;
  m_priceText.setFont(l_font);
  m_priceText.setString("price: " + std::to_string(l_price));
  m_priceText.setCharacterSize(50);
  m_priceText.setOrigin(m_priceText.getLocalBounds().width / 2, m_priceText.getLocalBounds().height / 2);
  m_priceText.setPosition(l_pos.x, l_pos.y + l_size.y / 2.0f - m_priceText.getLocalBounds().height);
}

StoreChoice::~StoreChoice() = default;

bool StoreChoice::Update(const sf::RenderWindow *l_wind) {
  if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    m_isMouseLeft = false;
  }
  bool ret = false;
  if (const sf::Vector2i l_mousePos = sf::Mouse::getPosition(*l_wind);
    static_cast<float>(l_mousePos.x) >= m_rect.getPosition().x - m_rect.getSize().x / 2.0f &&
    static_cast<float>(l_mousePos.x) <= m_rect.getPosition().x + m_rect.getSize().x / 2.0f &&
    static_cast<float>(l_mousePos.y) >= m_rect.getPosition().y - m_rect.getSize().y / 2.0f &&
    static_cast<float>(l_mousePos.y) <= m_rect.getPosition().y + m_rect.getSize().y / 2.0f) {
    if (!m_isMouseLeft && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      // std::cout << "MouseLeft Clicked!\n";
      m_isMouseLeft = true;
      ret = true;
      ++m_cnt;
      m_cntText.setString("Left: " + std::to_string(m_cnt));
    }
    m_rect.setFillColor(sf::Color::White);
    m_name.setFillColor(sf::Color::Black);
    m_description.setFillColor(sf::Color::Black);
    m_cntText.setFillColor(sf::Color::Black);
    m_priceText.setFillColor(sf::Color::Black);
  } else {
    m_rect.setFillColor(sf::Color::Red);
    m_name.setFillColor(sf::Color::White);
    m_description.setFillColor(sf::Color::White);
    m_cntText.setFillColor(sf::Color::White);
    m_priceText.setFillColor(sf::Color::White);
  }
  return ret;
}


void StoreChoice::Draw(sf::RenderWindow *l_wind) const {
  l_wind->draw(m_rect);
  l_wind->draw(m_name);
  l_wind->draw(m_description);
  l_wind->draw(m_cntText);
  l_wind->draw(m_priceText);
}

int StoreChoice::GetPrice() const {
  return m_price;
}

sf::RectangleShape &StoreChoice::GetRect() { return m_rect; }

void StoreChoice::SetIsMouseLeft(const bool l_mouseLeft) {
  m_isMouseLeft = l_mouseLeft;
}

std::string StoreChoice::GetPropName() const {
  return m_name.getString();
}
