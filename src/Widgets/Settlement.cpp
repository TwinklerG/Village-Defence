#include "Settlement.h"
#include "../Utils/Utils.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace gl {
  Settlement::Settlement(const sf::String &l_title, const std::unordered_map<int, int> &l_infos,
                         const sf::Vector2f &l_windowSize, const std::string &l_resolution, const sf::Font &l_font,
                         const std::function<void()> &l_callback)
    : m_callback(l_callback), m_windowSize(l_windowSize) {
    OnCreate(l_title, l_infos, l_resolution, l_font);
  }

  void Settlement::OnCreate(const sf::String &l_title, const std::unordered_map<int, int> &l_infos,
                            const std::string &l_resolution, const sf::Font &l_font) {
    m_title = std::make_unique<sf::Text>(l_font, l_title, m_windowSize.y / 5);
    m_title->setOrigin({m_title->getLocalBounds().size.x / 2, m_title->getLocalBounds().size.y / 2});
    m_title->setPosition({m_windowSize.x / 2.0f, m_windowSize.y / 3.0f});
    m_exitTip = std::make_unique<sf::Text>(l_font, L"敲击空格退出", m_windowSize.y / 40);
    m_exitTip->setOrigin({m_exitTip->getLocalBounds().size.x / 2, m_exitTip->getLocalBounds().size.y / 2});
    m_exitTip->setPosition({m_windowSize.x / 2.0f, m_windowSize.y / 3.0f * 2.0f});
    LoadFigures(l_infos, l_resolution);
  }

  void Settlement::Update(const sf::Time &l_time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      m_callback();
    }
    MoveSprite(l_time);
  }

  void Settlement::Render(sf::RenderWindow &l_window) const {
    for (const auto &l_sprite: m_sprites) {
      l_window.draw(l_sprite);
    }
    l_window.draw(*m_title);
    l_window.draw(*m_exitTip);
  }

  void Settlement::LoadFigures(const std::unordered_map<int, int> &l_infos, const std::string &l_resolution) {
    std::ifstream in("res/config/invader.json");
    nlohmann::json figures = nlohmann::json::parse(in);
    in.close();
    // Load Figures
    for (const auto [tag, cnt]: l_infos) {
      for (int i = 0; i < cnt; ++i) {
        const std::string l_figureName = "invader" + std::to_string(tag);
        if (m_textures.find(l_figureName) == m_textures.end()) {
          m_textures[l_figureName] = sf::Texture("res/img/invader/" + l_resolution + "/" + l_figureName + ".png");
        }
        sf::Sprite l_sprite(m_textures[l_figureName]);
        l_sprite.setPosition({m_windowSize.x, 0});
        m_sprites.emplace_back(l_sprite);
        m_increments.emplace_back(gl::RandInt(100, 400), gl::RandInt(100, 400));
      }
    }
  }

  void Settlement::MoveSprite(const sf::Time &l_elapsed) {
    for (int i = 0; i < m_sprites.size(); ++i) {
      const sf::Vector2u l_spSize = m_sprites[i].getTexture().getSize();
      const sf::Vector2f l_spPos = m_sprites[i].getPosition();
      if ((l_spPos.x + static_cast<float>(l_spSize.x) > m_windowSize.x && m_increments[i].x > 0) ||
          (l_spPos.x < 0 && m_increments[i].x < 0)) {
        m_increments[i].x = -m_increments[i].x;
      }
      if ((l_spPos.y + static_cast<float>(l_spSize.y) > m_windowSize.y && m_increments[i].y > 0) ||
          (l_spPos.y < 0 && m_increments[i].y < 0)) {
        m_increments[i].y = -m_increments[i].y;
      }
      m_sprites[i].setPosition({
        l_spPos.x + static_cast<float>(m_increments[i].x) * l_elapsed.asSeconds(),
        l_spPos.y + static_cast<float>(m_increments[i].y) * l_elapsed.asSeconds()
      });
    }
  }
}
