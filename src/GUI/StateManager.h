#pragma once
#include <vector>
#include "BaseState.h"
#include "SharedContext.hpp"
#include "State_Game.h"

enum class StateType {
  Intro = 1,
  MainMenu,
  Levels,
  Game,
  Paused,
  GameOver,
  Credits,
  About,
  Store,
  Setting,
  Load,
  Save,
};

using StateContainer = std::vector<std::pair<StateType, BaseState *> >;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState *(void)> >;

class StateManager {
public:
  explicit StateManager(SharedContext *l_shared);

  ~StateManager();

  void Update(const sf::Time &l_time);

  void Draw();

  void ProcessRequests();

  [[nodiscard]] SharedContext *GetContext() const;

  bool HasState(const StateType &l_type);

  void SwitchTo(const StateType &l_type);

  void Remove(const StateType &l_type);

  void RemoveAll();

private:
  // Methods.
  void CreateState(const StateType &l_type);

  void RemoveState(const StateType &l_type);

  template<class T>
  void RegisterState(const StateType &l_type) {
    m_stateFactory[l_type] = [this]() -> BaseState *{
      return new T(this);
    };
  }

  // Members.
  SharedContext *m_shared;
  TypeContainer m_toRemove;
  StateFactory m_stateFactory;

public:
  StateContainer m_states;
};
