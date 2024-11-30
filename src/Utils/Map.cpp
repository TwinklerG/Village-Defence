#include "Map.h"

int Map::m_XRange = 22;
int Map::m_YRange = 9;
float Map::m_FrameTime = 1.0f / 8.0f;

Map::Map(sf::RenderWindow *l_wind) { OnCreate(l_wind); }

Map::~Map() {}

void Map::OnCreate(sf::RenderWindow *l_wind)
{
  sf::Texture l_texture;
  l_texture.loadFromFile("res/land.png");
  m_textures.emplace("land", l_texture);
  l_texture.loadFromFile("res/mainland.png");
  m_textures.emplace("mainland", l_texture);

  m_places = std::vector<std::vector<Place *>>(m_XRange, std::vector<Place *>(m_YRange));
  for (int i = 0; i < m_XRange - 1; ++i)
  {
    for (int j = 0; j < m_YRange; ++j)
    {
      m_places[i][j] = new Land(m_textures["land"]);
      m_places[i][j]->GetSprite().setPosition(i * 80, l_wind->getSize().y / 3 + j * 80);
    }
  }
  for (int j = 0; j < m_YRange; j += 3)
  {
    m_places[m_XRange - 1][j] = new HomeLand(m_textures["mainland"]);
    m_places[m_XRange - 1][j]->GetSprite().setPosition((m_XRange - 1) * 80, l_wind->getSize().y / 3 + 80 * j);
  }

  m_figures.emplace_back(new Ordinary());
  // m_figures[0]->GetSprite().setPosition(0, 360);
}

void Map::Update()
{
  RestartClock();
  if (m_elapsed >= sf::seconds(m_FrameTime))
  {
    m_figures[0]->Update(m_elapsed);
    m_elapsed -= sf::seconds(m_FrameTime);
  }
}

void Map::Render(sf::RenderWindow *l_wind)
{
  for (int i = 0; i < m_XRange - 1; ++i)
  {
    for (int j = 0; j < m_YRange; ++j)
    {
      l_wind->draw(m_places[i][j]->GetSprite());
    }
  }
  for (int j = 0; j < m_YRange; j += 3)
  {
    l_wind->draw(m_places[m_XRange - 1][j]->GetSprite());
  }
  m_figures[0]->Render(l_wind);
  // l_wind->draw(m_figures[0]->GetSprite());
}

void Map::OnDestroy() {}

sf::Time Map::GetElapsed() { return m_elapsed; }

void Map::RestartClock() { m_elapsed += m_clock.restart(); }