#include "SoundManager.h"

SoundManager::SoundManager() {}
SoundManager::~SoundManager() {}

void SoundManager::Play(const std::string &l_soundName, int l_volume, bool l_loop)
{
  if (m_buffers.find(l_soundName) == m_buffers.end())
  {
    m_buffers[l_soundName].loadFromFile("res/audio/" + l_soundName);
  }
  m_sound.setBuffer(m_buffers[l_soundName]);
  m_sound.setVolume(l_volume);
  m_sound.setLoop(l_loop);
  m_sound.play();
}