#include "BgmManager.h"

BgmManager::BgmManager() = default;

BgmManager::~BgmManager() = default;

void BgmManager::Play(const std::string &l_bgmName, const float l_volume, const int l_loop) {
  m_music = sf::Music("res/audio/" + l_bgmName);
  m_music.setVolume(l_volume);
  m_music.setLooping(l_loop);
  m_music.play();
}

void BgmManager::Pause() { m_music.pause(); }

void BgmManager::Stop() {
  m_music.stop();
  m_bgmName = "";
}

std::string BgmManager::GetBgmName() const { return m_bgmName; }
