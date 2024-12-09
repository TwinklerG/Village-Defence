#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

class SoundManager
{
public:
  SoundManager();
  ~SoundManager();

  void Play(const std::string &l_soundName, int l_volume = 100, bool l_loop = false);

private:
  std::unordered_map<std::string, sf::SoundBuffer> m_buffers;
  sf::Sound m_sound;
};