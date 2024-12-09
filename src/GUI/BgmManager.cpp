#include "BgmManager.h"
BgmManager::BgmManager() : m_bgmName("") {}
BgmManager::~BgmManager() {}

void BgmManager::Play(const std::string &l_bgmName, int l_volume, int l_loop)
{
  m_music.openFromFile("res/audio/" + l_bgmName);
  m_music.setVolume(l_volume);
  m_music.setLoop(l_loop);
  m_music.play();
}

void BgmManager::Pause() { m_music.pause(); }

void BgmManager::Stop()
{
  m_music.stop();
  m_bgmName = "";
}

const std::string BgmManager::GetBgmName() const { return m_bgmName; }
