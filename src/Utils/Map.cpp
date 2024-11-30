#include "Map.h"

int Map::m_XRange = 22;
int Map::m_YRange = 9;
float Map::m_FrameTime = 1.0f / 8.0f;

Map::Map(sf::RenderWindow *l_wind) { OnCreate(l_wind); }

Map::~Map() = default;

void Map::OnCreate(sf::RenderWindow *l_wind)
{
  sf::Texture l_texture;
  l_texture.loadFromFile("res/land.png");
  m_textures.emplace("land", l_texture);
  l_texture.loadFromFile("res/mainland.png");
  m_textures.emplace("mainland", l_texture);
  l_texture.loadFromFile("res/stone.png");
  m_textures.emplace("stone", l_texture);
  m_places = std::vector<std::vector<Place *>>(m_XRange, std::vector<Place *>(m_YRange));
  LoadLogicMap(l_wind);
  for (int j = 0; j < m_YRange; j += 3)
  {
    m_places[m_XRange - 1][j] = new HomeLand(m_textures["mainland"]);
    m_places[m_XRange - 1][j]->GetSprite().setPosition((m_XRange - 1) * 80, l_wind->getSize().y / 3 + 80 * j);
  }
  // for (int i = 0; i < m_XRange - 1; ++i)
  // {
  //   for (int j = 0; j < m_YRange; ++j)
  //   {
  //     m_places[i][j] = new Land(m_textures["land"]);
  //     m_places[i][j]->GetSprite().setPosition(i * 80, l_wind->getSize().y / 3 + j * 80);
  //   }
  // }
  // for (int j = 0; j < m_YRange; j += 3)
  // {
  //   m_places[m_XRange - 1][j] = new HomeLand(m_textures["mainland"]);
  //   m_places[m_XRange - 1][j]->GetSprite().setPosition((m_XRange - 1) * 80, l_wind->getSize().y / 3 + 80 * j);
  // }
  for (int k = 0; k < 200; ++k)
  {
    m_figures.emplace_back(new Ordinary(this));
  }
  for (int k = 0; k < 10; ++k)
  {
    m_figures.emplace_back(new Guardian(this));
  }
}

void Map::Update()
{
  RestartClock();
  if (m_elapsed >= sf::seconds(m_FrameTime))
  {
    const int n = m_figures.size();
    for (int i = 0; i < m_figures.size(); ++i)
    {
      m_figures[i]->Update(m_elapsed);
    }
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
  for (auto &l_fig : m_figures)
  {
    l_fig->Render(l_wind);
  }
}

void Map::OnDestroy() {}

Map *Map::AddFigure(Figure *l_fig)
{
  m_figures.emplace_back(l_fig);
  return this;
}

void Map::LoadLogicMap(sf::RenderWindow *l_wind)
{
  std::ifstream map;
  map.open("res/map0.cfg");
  if (!map.is_open())
  {
    std::cout << "! Failed loading map.cfg" << std::endl;
  }
  for (int j = 0; j < m_YRange; ++j)
  {
    std::string line;
    if (!std::getline(map, line))
    {
      std::cout << "Load LogicMap Failed! Y" << std::endl;
      return;
    }
    std::stringstream placeStream(line);
    std::string l_placeType;
    for (int i = 0; i < m_XRange - 1; ++i)
    {
      // if (placeStream.eof())
      // {
      //   std::cout << "Load LogicMap Failed! X" << std::endl;
      //   return;
      // }
      placeStream >> l_placeType;
      if (std::stoi(l_placeType) == 0)
      {
        m_places[i][j] = new Land(m_textures["land"]);
      }
      else if (std::stoi(l_placeType) == 1)
      {
        m_places[i][j] = new Stone(m_textures["stone"]);
      }
      m_places[i][j]->GetSprite().setPosition(i * 80, l_wind->getSize().y / 3 + j * 80);
    }
  }
}

sf::Time Map::GetElapsed() { return m_elapsed; }

void Map::RestartClock() { m_elapsed += m_clock.restart(); }