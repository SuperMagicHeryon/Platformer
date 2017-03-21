#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game.hpp"

class GameState
{
   public:
      GameState(Game*, sf::RenderWindow&, ResourcesManager&);
      virtual ~GameState();

      virtual void resize() = 0;
      virtual void draw() const = 0;
      virtual void run() = 0;

   protected:
      virtual void loadData() = 0;

      Game* game;
      sf::RenderWindow& window;
      ResourcesManager& resources_manager;

      sf::Sprite background_sprite;
};

#endif //GAME_STATE_HPP
