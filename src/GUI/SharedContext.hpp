#pragma once
#include <SFML/Audio.hpp>
#include "Window.h"
#include "EventManager.h"
#include "BgmManager.h"
#include "SoundManager.h"
struct SharedContext
{
  SharedContext() : m_wind(nullptr), m_eventManager(nullptr), m_level(0) {}
  Window *m_wind;
  EventManager *m_eventManager;
  int m_level;
  BgmManager m_bgmManager;
  SoundManager m_soundManager;
};
