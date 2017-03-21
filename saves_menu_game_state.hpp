#ifndef SAVES_MENU_GAME_STATE_HPP
#define SAVES_MENU_GAME_STATE_HPP

#include "game_state.hpp"
#include "button.hpp"

class SavesMenuGameState : public GameState
{
   public:
      SavesMenuGameState(Game*, sf::RenderWindow&, ResourcesManager&);
      ~SavesMenuGameState();

      virtual void resize();
      virtual void draw() const;
      virtual void run();

   private:
      virtual void loadData();

      std::vector<Button*> buttons;
};

#endif //SAVES_MENU_GAME_STATE_HPP
