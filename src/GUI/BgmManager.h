#pragma once
#include <string>
#include <SFML/Audio.hpp>
class BgmManager
{
public:
  BgmManager();
  ~BgmManager();
  void Play(const std::string &l_bgmName, int l_volume = 100, int l_loop = true);
  void Pause();
  void Stop();

  const std::string GetBgmName() const;

private:
  sf::Music m_music;
  std::string m_bgmName;
};