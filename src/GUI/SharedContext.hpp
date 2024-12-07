#pragma once
#include "Window.h"
#include "EventManager.h"
struct SharedContext
{
  SharedContext() : m_wind(nullptr), m_eventManager(nullptr), m_level(0) {}
  Window *m_wind;
  EventManager *m_eventManager;
  int m_level;
};
