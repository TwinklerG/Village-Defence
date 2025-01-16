#include "State_Store.h"

#include <iostream>

#include "StateManager.h"

PropType sToPropType(const std::string &s) {
  if (s == "DECELERATE") {
    return PropType::DECELERATE;
  }
  if (s == "ACCELERATE") {
    return PropType::ACCELERATE;
  }
  if (s == "TROPHY") {
    return PropType::TROPHY;
  }
  throw std::invalid_argument("Invalid PropType");
}

State_Store::State_Store(StateManager *l_stateManager)
  : BaseState(l_stateManager), m_title(nullptr), m_coinText(nullptr) {
}

State_Store::~State_Store() = default;

void State_Store::OnCreate() {
  m_font = sf::Font("res/fonts/YeZiGongChangShanHaiMingChao-2.ttf");
  m_title = std::make_unique<sf::Text>(m_font, L"商店", 100);
  m_title->setOrigin({
    m_title->getLocalBounds().size.x / 2.0f,
    m_title->getLocalBounds().size.y / 2.0f
  });
  m_title->setPosition(
    {
      static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().x) /
      2.0f,
      static_cast<float>(m_stateMgr->GetContext()->m_wind->GetWindowSize().y) /
      10.0f
    });
}

void State_Store::LoadJson() {
  std::ifstream in("res/config/store.json");
  nlohmann::json data = nlohmann::json::parse(in);
  in.close();
  m_coin = data["coin"];
  const sf::Vector2u l_windSize =
      m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize();
  m_coinText = std::make_unique<sf::Text>(
    m_font, sf::String(L"硬币: ") + sf::String(std::to_string(m_coin)), 40);
  m_coinText->setOrigin({m_coinText->getLocalBounds().size.x, 0});
  m_coinText->setPosition({
    static_cast<float>(l_windSize.x) -
    m_coinText->getLocalBounds().size.x / 2.0f,
    m_coinText->getLocalBounds().size.y / 2.0f
  });
  auto goods = data["goods"];
  auto props = data["props"];
  for (auto &prop: props) {
    m_props[sToPropType(prop["name"])] =
        prop["stock"] == nullptr ? 0 : static_cast<int>(prop["stock"]);
  }
  m_choices.clear();
  for (int i = 0; i < goods.size(); ++i) {
    auto &good = goods[i];
    m_choices.emplace_back(
      std::string(good["name"]), std::string(good["description"]),
      good["price"],
      sf::Vector2f(static_cast<float>(l_windSize.x) / 13.0f * 3.0f,
                   static_cast<float>(l_windSize.y) / 3.0f * 2.0f),
      sf::Vector2f(static_cast<float>(l_windSize.x) / 13.0f *
                   static_cast<float>(2.5f + 4.0 * i),
                   static_cast<float>(l_windSize.y) / 5.0f * 3.0f),
      m_font, m_props[sToPropType(good["name"])]);
  }
  m_choices.emplace_back(
    L"敬请期待",
    sf::Vector2f(static_cast<float>(l_windSize.x) / 13.0f * 3.0f,
                 static_cast<float>(l_windSize.y) / 3.0f * 2.0f),
    sf::Vector2f(static_cast<float>(l_windSize.x) / 13.0f *
                 static_cast<float>(2.5f + 4.0 * 2),
                 static_cast<float>(l_windSize.y) / 5.0f * 3.0f),
    m_font);
}

void State_Store::Update(const sf::Time &l_time) {
  if (!m_confirm && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
    m_confirm = std::make_shared<gl::Confirm>(
      L"确定购买吗",
      sf::Vector2f(
        m_stateMgr->GetContext()->m_wind->GetRenderWindow()->getSize()),
      m_font);
  }
  for (auto &l_choice: m_choices) {
    if (l_choice.GetPropName() != L"敬请期待" &&
        l_choice.Update(m_stateMgr->GetContext()->m_wind->GetRenderWindow())) {
      if (m_coin < l_choice.GetPrice()) {
        m_toast = std::make_shared<gl::Toast>(
          L"硬币不足", m_font,
          sf::Vector2f(m_stateMgr->GetContext()
            ->m_wind->GetRenderWindow()
            ->getSize()));
      } else {
        m_coin -= l_choice.GetPrice();
        m_coinText->setString(L"硬币: " + sf::String(std::to_string(m_coin)));
        ++m_props[sToPropType(l_choice.GetPropName())];
        l_choice.SetCnt(m_props[sToPropType(l_choice.GetPropName())]);
      }
    }
  }
  if (m_toast && m_toast->Update(l_time)) {
    m_toast = nullptr;
  }
}

void State_Store::Draw() {
  sf::RenderWindow *l_wind =
      m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  l_wind->draw(*m_title);
  for (const auto &l_choice: m_choices) {
    l_choice.Draw(l_wind);
  }
  l_wind->draw(*m_coinText);
  if (m_toast) {
    m_toast->Render(*l_wind);
  }
  auto &l_window = *m_stateMgr->GetContext()->m_wind->GetRenderWindow();
  if (m_confirm) {
    if (const gl::ConfirmType l_confirmType = m_confirm->UpdateRender(l_window);
      l_confirmType == gl::ConfirmType::CONFIRM) {
      m_stateMgr->GetContext()->m_soundManager.Play("coins.ogg", 100);
      m_stateMgr->Remove(StateType::Store);
      m_stateMgr->SwitchTo(StateType::MainMenu);
      m_confirm = nullptr;
      SaveJson();
    } else if (l_confirmType == gl::ConfirmType::CANCEL) {
      m_confirm = nullptr;
      m_stateMgr->SwitchTo(StateType::MainMenu);
    }
  }
}

void State_Store::Activate() {
  LoadJson();
  for (auto &l_choice: m_choices) {
    l_choice.SetIsMouseLeft(true);
  }
}

void State_Store::Deactivate() {
}

void State_Store::OnDestroy() {
}

void State_Store::SaveJson() {
  nlohmann::json data;
  data["coin"] = m_coin;
  std::ifstream in("res/config/store.json");
  nlohmann::json tmp = nlohmann::json::parse(in);
  data["goods"] = tmp["goods"];
  in.close();
  for (const auto &[l_propType, l_propCnt]: m_props) {
    if (l_propType == PropType::DECELERATE) {
      data["props"].push_back({{"name", "DECELERATE"}, {"stock", l_propCnt}});
    } else if (l_propType == PropType::ACCELERATE) {
      data["props"].push_back({{"name", "ACCELERATE"}, {"stock", l_propCnt}});
    } else if (l_propType == PropType::TROPHY) {
      data["props"].push_back({{"name", "TROPHY"}, {"stock", l_propCnt}});
    } else {
      throw std::invalid_argument("Illegal Prop Type");
    }
  }
  std::ofstream out("res/config/store.json");
  out << data << std::endl;
  out.close();
}

StoreChoice::StoreChoice(const sf::String &l_name, const sf::Vector2f &l_size,
                         const sf::Vector2f &l_pos, const sf::Font &l_font)
  : m_name(nullptr), m_description(nullptr), m_cnt(-1), m_cntText(nullptr),
    m_priceText(nullptr), m_price(-1) {
  OnCreate(l_name, "", l_size, l_pos, l_font);
}

StoreChoice::StoreChoice(const sf::String &l_name,
                         const sf::String &l_description, const int l_price,
                         const sf::Vector2f &l_size, const sf::Vector2f &l_pos,
                         const sf::Font &l_font, const int l_cnt)
  : m_name(nullptr), m_description(nullptr), m_cnt(l_cnt), m_cntText(nullptr),
    m_priceText(nullptr), m_price(l_price) {
  OnCreate(l_name, l_description, l_size, l_pos, l_font);
}

StoreChoice::~StoreChoice() = default;

void StoreChoice::OnCreate(const sf::String &l_name,
                           const sf::String &l_description,
                           const sf::Vector2f &l_size,
                           const sf::Vector2f &l_pos, const sf::Font &l_font) {
  m_rect.setSize(l_size);
  m_rect.setOrigin({l_size.x / 2.0f, l_size.y / 2.0f});
  m_rect.setPosition(l_pos);
  m_rect.setFillColor(sf::Color::Red);
  m_name = std::make_shared<sf::Text>(l_font, l_name, 50);
  m_name->setOrigin({
    m_name->getLocalBounds().size.x / 2.0f,
    m_name->getLocalBounds().size.y / 2.0f
  });
  m_name->setPosition(
    {l_pos.x, l_pos.y - l_size.y / 2.0f + m_name->getLocalBounds().size.y});
  m_description = std::make_shared<sf::Text>(l_font, l_description, 50);
  m_description->setOrigin({
    m_description->getLocalBounds().size.x / 2,
    m_description->getLocalBounds().size.y / 2
  });
  m_description->setPosition({l_pos.x, l_pos.y + 35});
  m_description->setLineSpacing(1.0f);
  if (m_cnt >= 0) {
    m_cntText = std::make_shared<sf::Text>(
      l_font, sf::String(L"剩余: ") + sf::String(std::to_string(m_cnt)), 40);
    m_cntText->setOrigin({
      m_cntText->getLocalBounds().size.x / 2.0f,
      m_cntText->getLocalBounds().size.y / 2.0f
    });
    m_cntText->setPosition(
      {
        l_pos.x, l_pos.y + l_size.y / 4.0f -
                 m_cntText->getLocalBounds().size.y / 2.0f
      });
  }
  if (m_price >= 0) {
    m_priceText = std::make_shared<sf::Text>(
      l_font, sf::String(L"价格: ") + sf::String(std::to_string(m_price)),
      50);
    m_priceText->setOrigin({
      m_priceText->getLocalBounds().size.x / 2,
      m_priceText->getLocalBounds().size.y / 2
    });
    m_priceText->setPosition(
      {
        l_pos.x,
        l_pos.y + l_size.y / 2.0f - m_priceText->getLocalBounds().size.y
      });
  }
}

bool StoreChoice::Update(const sf::RenderWindow *l_wind) {
  if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    m_isMouseLeft = false;
  }
  bool ret = false;
  if (const sf::Vector2i l_mousePos = sf::Mouse::getPosition(*l_wind);
    static_cast<float>(l_mousePos.x) >=
    m_rect.getPosition().x - m_rect.getSize().x / 2.0f &&
    static_cast<float>(l_mousePos.x) <=
    m_rect.getPosition().x + m_rect.getSize().x / 2.0f &&
    static_cast<float>(l_mousePos.y) >=
    m_rect.getPosition().y - m_rect.getSize().y / 2.0f &&
    static_cast<float>(l_mousePos.y) <=
    m_rect.getPosition().y + m_rect.getSize().y / 2.0f) {
    if (!m_isMouseLeft && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      m_isMouseLeft = true;
      ret = true;
    }
    m_rect.setFillColor(sf::Color::White);
    m_name->setFillColor(sf::Color::Black);
    m_description->setFillColor(sf::Color::Black);
    if (m_cntText) {
      m_cntText->setFillColor(sf::Color::Black);
    }
    if (m_priceText) {
      m_priceText->setFillColor(sf::Color::Black);
    }
  } else {
    m_rect.setFillColor(sf::Color::Red);
    m_name->setFillColor(sf::Color::White);
    m_description->setFillColor(sf::Color::White);
    if (m_cntText) {
      m_cntText->setFillColor(sf::Color::White);
    }
    if (m_priceText) {
      m_priceText->setFillColor(sf::Color::White);
    }
  }
  return ret;
}

void StoreChoice::Draw(sf::RenderWindow *l_wind) const {
  l_wind->draw(m_rect);
  l_wind->draw(*m_name);
  l_wind->draw(*m_description);
  if (m_cntText) {
    l_wind->draw(*m_cntText);
  }
  if (m_priceText) {
    l_wind->draw(*m_priceText);
  }
}

int StoreChoice::GetPrice() const { return m_price; }

sf::RectangleShape &StoreChoice::GetRect() { return m_rect; }

void StoreChoice::SetIsMouseLeft(const bool l_mouseLeft) {
  m_isMouseLeft = l_mouseLeft;
}

sf::String StoreChoice::GetPropName() const { return m_name->getString(); }

void StoreChoice::SetCnt(const int l_cnt) {
  m_cnt = l_cnt;
  m_cntText->setString(sf::String(L"剩余: ") +
                       sf::String(std::to_string(m_cnt)));
}
