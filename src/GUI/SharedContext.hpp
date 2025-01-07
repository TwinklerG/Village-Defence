#pragma once
#include <memory>
#include <nlohmann/json.hpp>

#include "Window.h"
#include "BgmManager.h"
#include "SoundManager.h"

struct SharedContext {
  SharedContext() : m_wind(nullptr), m_level(0), m_mapData(nullptr) {
  }

  std::shared_ptr<Window> m_wind;
  int m_level;
  BgmManager m_bgmManager;
  SoundManager m_soundManager;
  std::string m_resolution;
  sf::Vector2f m_atomResolution; // Support Square only
  std::unique_ptr<nlohmann::json> m_mapData;
};
