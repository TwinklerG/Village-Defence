#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window {
public:
  Window();

  Window(const std::string &l_title, const sf::Vector2u &l_size);

  ~Window();

  void BeginDraw(); // Clear the window.
  void EndDraw(); // Display the changes.
  void Update();

  bool IsDone() const;

  bool IsFullscreen() const;

  bool IsFocused() const;

  void Draw(const sf::Drawable &l_drawable);

  void ToggleFullscreen(EventDetails *l_details);

  void Close(EventDetails *l_details = nullptr);

  EventManager *GetEventManager();

  sf::RenderWindow *GetRenderWindow();

  sf::Vector2u GetWindowSize() const;

private:
  void Setup(const std::string &l_title, const sf::Vector2u &l_size);

  void Destroy();

  void Create();

  sf::RenderWindow m_window;
  sf::Vector2u m_windowSize;
  std::string m_windowTitle;
  EventManager m_eventManager;
  bool m_isDone{};
  bool m_isFullscreen{};
  bool m_isFocused{};
};
