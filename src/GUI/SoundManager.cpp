#include "SoundManager.h"

SoundManager::SoundManager() {
  m_buffers["winner.ogg"] = sf::SoundBuffer("res/audio/winner.ogg");
  m_sound = std::make_shared<sf::Sound>(m_buffers["winner.ogg"]);
}

SoundManager::~SoundManager() = default;

void SoundManager::Play(const std::string &l_soundName, const float l_volume, const bool l_loop) {
  if (m_buffers.find(l_soundName) == m_buffers.end()) {
    m_buffers[l_soundName] = sf::SoundBuffer("res/audio/" + l_soundName);
  }
  m_sound->setBuffer(m_buffers[l_soundName]);
  m_sound->setVolume(l_volume);
  m_sound->setLooping(l_loop);
  m_sound->play();
}
