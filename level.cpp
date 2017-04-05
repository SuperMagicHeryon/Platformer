#include "level.hpp"

Level::Level(Game* _game, const std::string& _level_path, const sf::Texture& _player_texture, const sf::Texture& _grass_texture, const sf::Texture& _stone_texture)
: gravity(0.f, 9.807f), world(gravity), grass_texture(_grass_texture), stone_texture(_stone_texture)
{
   loadLevel(_game, _level_path);
   initializePlayer(_player_texture);
   createBlocks();

   return;
}

void Level::initializePlayer(const sf::Texture& _player_texture)
{
   b2BodyDef player_body_def;
   player_body_def.position = b2Vec2(250.f, 50.f);
   player_body_def.type = b2_dynamicBody;

   b2Body* player_body = world.CreateBody(&player_body_def);

   b2PolygonShape player_shape;
   player_shape.SetAsBox(50.f, 50.f);

   b2FixtureDef player_fixture_def;
   player_fixture_def.density = 1.f;
   player_fixture_def.friction = 1.f;
   player_fixture_def.shape = &player_shape;

   player_body->CreateFixture(&player_fixture_def);

   player_sprite.setTexture(_player_texture);
   player_sprite.setOrigin(50.f, 50.f);

   return;
}

void Level::loadLevel(Game* _game, const std::string& _level_path)
{
   level_file.open(_level_path, std::fstream::in);

   if(!level_file)
   {
      _game->error();
      return;
   }

   else
   {
      for(int i = 0; i < 50; i++)
         level_file >> level[i];

      level_file.close();
   }

   return;
}

void Level::createBlocks()
{
   int j = 0;
   for(int i = 0; i < 50; i++)
   {
      if(level[i] != 0)
      {
         b2BodyDef block_body_def;
         block_body_def.position = b2Vec2(static_cast<float>(i % 10) * 50.f + 25.f, static_cast<float>(i / 10) * 50.f + 25.f);
         block_body_def.type = b2_staticBody;

         b2Body* stone_block_body = world.CreateBody(&block_body_def);

         b2PolygonShape block_shape;
         block_shape.SetAsBox(25.f, 25.f);

         b2FixtureDef block_fixture_def;
         block_fixture_def.density = 1.f;
         block_fixture_def.friction = 1.f;
         block_fixture_def.shape = &block_shape;

         stone_block_body->CreateFixture(&block_fixture_def);

         blocks_sprites.push_back(sf::Sprite());

         if(level[i] == 1)
            blocks_sprites[j].setTexture(grass_texture);

         else if(level[i] == 2)
            blocks_sprites[j].setTexture(stone_texture);

         blocks_sprites[j].setOrigin(25.f, 25.f);
         j++;
      }
   }

   return;
}

void Level::draw(sf::RenderWindow& _window) const
{
   _window.draw(player_sprite);

   for(size_t i = 0; i < blocks_sprites.size(); i++)
      _window.draw(blocks_sprites[i]);

   return;
}

void Level::update()
{
   world.Step(1.f, 8, 3);

   int i = 17;
   for(b2Body* body_iterator = world.GetBodyList(); body_iterator != 0; body_iterator = body_iterator->GetNext())
   {
      if(body_iterator->GetType() == b2_dynamicBody)
      {
         player_sprite.setPosition(body_iterator->GetPosition().x, body_iterator->GetPosition().y);
         player_sprite.setRotation(body_iterator->GetAngle());
      }

      else
      {
         blocks_sprites[i].setPosition(body_iterator->GetPosition().x, body_iterator->GetPosition().y);
         blocks_sprites[i].setRotation(body_iterator->GetAngle());
         i--;
      }
   }

   return;
}
