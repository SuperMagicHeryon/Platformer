#ifndef OPTIONS_MENU_GAME_STATE_HPP
#define OPTIONS_MENU_GAME_STATE_HPP

#include "game_state.hpp"
#include "button.hpp"

class OptionsMenuGameState : public GameState
{
   public:
      OptionsMenuGameState(Game*, sf::RenderWindow&, ResourcesManager&);
      ~OptionsMenuGameState();

      virtual void resize();
      virtual void draw() const;
      virtual void run();

   private:
      virtual void loadData();
      void writeData();

      void changeLanguage(int);
      void changeWindowMode(int);

      std::string language;
      std::string window_mode;

      std::vector<Button*> buttons;
      std::vector<sf::Text*> options;
};

#endif //OPTIONS_MENU_GAME_STATE_HPP
