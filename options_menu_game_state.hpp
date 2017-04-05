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
      void changeKey(std::string&, const sf::Event&);

      void setControlsButtonsTexts();

      std::fstream config_file;

      std::string language;
      std::string window_mode;

      std::vector<std::string> keys;

      bool move_left_key_button_focus;
      bool move_right_key_button_focus;
      bool jump_key_button_focus;

      std::vector<Button*> buttons;
      std::vector<sf::Text*> options;
};

#endif //OPTIONS_MENU_GAME_STATE_HPP
