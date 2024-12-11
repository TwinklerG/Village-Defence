#pragma once
#include "BaseState.h"
#include "EventManager.h"

enum class PropType {
  SLOW,
  ACCELERATE,
  TROPHY,
};

PropType sToPropType(const std::string &s);

class StoreChoice {
public:
  StoreChoice(const std::string &l_name, const std::string &l_description, int l_price,
              const sf::Vector2f &l_size, const sf::Vector2f &l_pos,
              const sf::Font &l_font, int l_cnt = 0);

  ~StoreChoice();

  bool Update(const sf::RenderWindow *l_wind);

  void Draw(sf::RenderWindow *l_wind) const;

  int GetPrice() const;

  sf::RectangleShape &GetRect();

  void SetIsMouseLeft(bool l_mouseLeft);

  std::string GetPropName() const;

private:
  sf::RectangleShape m_rect{};
  sf::Text m_name;
  sf::Text m_description;
  int m_cnt;
  sf::Text m_cntText;
  sf::Text m_priceText;
  int m_price;
  bool m_isMouseLeft{true};
};

class State_Store final : public BaseState {
public:
  explicit State_Store(StateManager *l_stateManager);

  ~State_Store() override;

  void OnCreate() override;

  void OnDestroy() override;

  void Activate() override;

  void Deactivate() override;

  void Update(const sf::Time &l_time) override;

  void Draw() override;

  void MainMenu(EventDetails *l_details);

private:
  void LoadGoods();

  void LoadProps();

  void SaveProps();

  sf::Font m_font;
  sf::Text m_title;
  int m_coin{};
  sf::Text m_coinText;
  std::vector<StoreChoice> m_choices;
  std::unordered_map<PropType, int> m_props;
};
