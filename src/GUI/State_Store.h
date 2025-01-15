#pragma once
#include <nlohmann/json.hpp>
#include "BaseState.h"
#include "../Widgets/Toast.h"
#include "../Widgets/Confirm.h"

namespace gl {
  class Confirm;
}

enum class PropType {
  DECELERATE,
  ACCELERATE,
  TROPHY,
};

PropType sToPropType(const std::string &s);

class StoreChoice {
public:
  StoreChoice(const sf::String &l_name, const sf::Vector2f &l_size, const sf::Vector2f &l_pos, const sf::Font &l_font);

  StoreChoice(const sf::String &l_name, const sf::String &l_description, int l_price,
              const sf::Vector2f &l_size, const sf::Vector2f &l_pos,
              const sf::Font &l_font, int l_cnt = 0);

  ~StoreChoice();

  void OnCreate(const sf::String &l_name, const sf::String &l_description, const sf::Vector2f &l_size,
                const sf::Vector2f &l_pos, const sf::Font &l_font);

  bool Update(const sf::RenderWindow *l_wind);

  void Draw(sf::RenderWindow *l_wind) const;

  int GetPrice() const;

  sf::RectangleShape &GetRect();

  void SetIsMouseLeft(bool l_mouseLeft);

  sf::String GetPropName() const;

  void SetCnt(int l_cnt);

private:
  sf::RectangleShape m_rect{};
  std::shared_ptr<sf::Text> m_name;
  std::shared_ptr<sf::Text> m_description;
  int m_cnt;
  std::shared_ptr<sf::Text> m_cntText;
  std::shared_ptr<sf::Text> m_priceText;
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

private:
  void LoadJson();

  void SaveJson();

  sf::Font m_font;
  std::unique_ptr<sf::Text> m_title;
  int m_coin{};
  std::unique_ptr<sf::Text> m_coinText;
  std::vector<StoreChoice> m_choices;
  std::unordered_map<PropType, int> m_props;
  std::shared_ptr<gl::Toast> m_toast;
  std::shared_ptr<gl::Confirm> m_confirm;
};
