#include <optional>
#include "Window.h"

Window::Window() { Setup("Window", sf::Vector2u(640, 480)); }
Window::Window(const std::string &l_title, const sf::Vector2u &l_size) { Setup(l_title, l_size); }
Window::~Window() { Destroy(); }

void Window::Setup(const std::string &l_title, const sf::Vector2u &l_size) {
  m_windowTitle = l_title;
  m_windowSize = l_size;
  m_isFullscreen = false;
  m_isDone = false;
  m_isFocused = true; // Default value for focused flag.
  Create();
}

void Window::Create() {
  m_window.create(sf::VideoMode{{m_windowSize.x, m_windowSize.y}, 32}, m_windowTitle, sf::Style::Close);
  m_window.setFramerateLimit(60);
}

void Window::Destroy() { m_window.close(); }

void Window::Update() {
  while (const std::optional event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      Close();
    }
  }
}

void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::EndDraw() { m_window.display(); }

bool Window::IsDone() const { return m_isDone; }
bool Window::IsFocused() const { return m_isFocused; }
sf::Vector2u Window::GetWindowSize() const { return m_windowSize; }
sf::RenderWindow *Window::GetRenderWindow() { return &m_window; }

void Window::Close() {
  m_isDone = true;
}

void Window::Draw(const sf::Drawable &l_drawable) {
  m_window.draw(l_drawable);
}
