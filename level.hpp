#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "stl_includes.hpp"
#include "sfml_includes.hpp"
#include "game.hpp"
#include <Box2D/Box2D.h>

class Level
{
   public:
      Level(Game*, const std::string&, const sf::Texture&, const sf::Texture&, const sf::Texture&);

      void draw(sf::RenderWindow&) const;
      void update();

   private:
      void initializePlayer(const sf::Texture&);
      void loadLevel(Game*, const std::string&);
      void createBlocks();

      std::fstream level_file;

      b2Vec2 gravity;
      b2World world;

      int level[50];
      sf::Texture grass_texture;
      sf::Texture stone_texture;
      std::vector<sf::Sprite> blocks_sprites;

      sf::Sprite player_sprite;
};

#endif //LEVEL_HPP
