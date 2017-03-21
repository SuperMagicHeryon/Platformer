#ifndef MAIN_MENU_GAME_STATE_HPP
#define MAIN_MENU_GAME_STATE_HPP

#include "game_state.hpp"
#include "button.hpp"

class MainMenuGameState : public GameState
{
   public:
      MainMenuGameState(Game*, sf::RenderWindow&, ResourcesManager&);
      ~MainMenuGameState();

      virtual void resize();
      virtual void draw() const;
      virtual void run();

   private:
      virtual void loadData();

      std::vector<Button*> buttons;
};

#endif //MAIN_MENU_GAME_STATE_HPP
