#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

class SoundManager {
public:
  SoundManager();

  ~SoundManager();

  void Play(const std::string &l_soundName, float l_volume = 100, bool l_loop = false);

private:
  std::unordered_map<std::string, sf::SoundBuffer> m_buffers;
  std::shared_ptr<sf::Sound> m_sound;
};
