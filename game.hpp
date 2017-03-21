#ifndef GAME_HPP
#define GAME_HPP

#include "resources_manager.hpp"

class GameState;

class Game
{
   public:
      Game(bool&);
      ~Game();

      void pushGameState(GameState*);
      void popGameState();
      void changeGameState(GameState*);

      const std::string& getLanguage() const;
      const std::string& getWindowMode() const;

      void setLanguage(const std::string&);
      void setWindowMode(const std::string&);

      void error();

      void resizeView();
      void run();

   private:
      GameState* currentGameState();

      void loadData();
      void writeData();

      void createWindow();

      bool success;

      std::string language;
      std::string window_mode;
      unsigned int window_width;
      unsigned int window_height;

      std::fstream config_file;

      std::stack<GameState*> game_states;

      sf::RenderWindow window;
      sf::View view;

      ResourcesManager resources_manager;
};

#endif //GAME_HPP
