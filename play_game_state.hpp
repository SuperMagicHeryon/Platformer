#ifndef PLAY_GAME_STATE_HPP
#define PLAY_GAME_STATE_HPP

#include "game_state.hpp"
#include "level.hpp"

class PlayGameState : public GameState
{
   public:
      PlayGameState(Game*, sf::RenderWindow&, ResourcesManager&);

      virtual void resize();
      virtual void draw() const;
      virtual void run();

   private:
      virtual void loadData();

      Level level;
};

#endif //PLAY_GAME_STATE_HPP
