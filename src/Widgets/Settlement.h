#pragma once
#include <functional>
#include <SFML/Graphics.hpp>

namespace gl {
  class Settlement {
  public:
    explicit Settlement(const sf::String &l_title, const std::unordered_map<int, int> &l_infos,
                        const sf::Vector2f &l_windowSize, const std::string &l_resolution, const sf::Font &l_font,
                        const std::function<void()> &l_callback);

    void OnCreate(const sf::String &l_title, const std::unordered_map<int, int> &l_infos,
                  const std::string &l_resolution, const sf::Font &l_font);

    void Update(const sf::Time &l_time);

    void Render(sf::RenderWindow &l_window) const;

  private:
    void LoadFigures(const std::unordered_map<int, int> &l_infos, const std::string &l_resolution);

    void MoveSprite(const sf::Time &l_elapsed);

    std::shared_ptr<sf::Text> m_title;
    std::shared_ptr<sf::Text> m_exitTip;
    std::function<void()> m_callback;

    std::unordered_map<std::string, sf::Texture> m_textures;
    std::vector<sf::Sprite> m_sprites;
    std::vector<sf::Vector2i> m_increments;
    sf::Vector2f m_windowSize;
  };
}
