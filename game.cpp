#include "game.hpp"
#include "main_menu_game_state.hpp"

Game::Game(bool& _success) : success(_success)
{
   loadData();
   createWindow();

   pushGameState(new MainMenuGameState(this, window, resources_manager));

   return;
}

Game::~Game()
{
   while(!game_states.empty())
      popGameState();

   writeData();

   return;
}

void Game::pushGameState(GameState* _game_state)
{
   game_states.push(_game_state);

   return;
}

void Game::popGameState()
{
   delete game_states.top();
   game_states.pop();

   return;
}

void Game::changeGameState(GameState* _game_state)
{
   popGameState();
   pushGameState(_game_state);

   return;
}

GameState* Game::currentGameState()
{
   return game_states.top();
}

const std::string& Game::getLanguage() const
{
   return language;
}

const std::string& Game::getWindowMode() const
{
   return window_mode;
}

void Game::setLanguage(const std::string& _language)
{
   if(language != _language)
      language = _language;

   return;
}

void Game::setWindowMode(const std::string& _window_mode)
{
   if(window_mode != _window_mode)
   {
      window_mode = _window_mode;
      createWindow();
   }

   return;
}

void Game::loadData()
{
   config_file.open("data/platformer.config", std::fstream::in);

   if(!config_file)
   {
      error();
      return;
   }

   else
   {
      getline(config_file, language);
      getline(config_file, window_mode);
      config_file >> window_width >> window_height;

      config_file.close();
   }

   return;
}

void Game::writeData()
{
   config_file.open("data/platformer.config", std::fstream::out);

   if(!config_file)
   {
      error();
      return;
   }

   else
   {
      config_file << language << std::endl << window_mode << std::endl << window_width << " " << window_height;
      config_file.close();
   }

   return;
}

void Game::createWindow()
{
   if(window_mode == "windowed")
   {
      window.create(sf::VideoMode(window_width, window_height, sf::VideoMode::getDesktopMode().bitsPerPixel), "Platformer", sf::Style::Default);
      window.setMouseCursorGrabbed(false);
   }

   else if(window_mode == "fullscreen")
   {
      sf::VideoMode fullscreen_mode = sf::VideoMode::getFullscreenModes()[0];
      window.create(sf::VideoMode(fullscreen_mode.width, fullscreen_mode.height, fullscreen_mode.bitsPerPixel), "Platformer", sf::Style::Fullscreen);
      window.setMouseCursorGrabbed(true);
   }

   else if(window_mode == "borderless_windowed")
   {
      sf::VideoMode fullscreen_mode = sf::VideoMode::getFullscreenModes()[0];
      window.create(sf::VideoMode(fullscreen_mode.width, fullscreen_mode.height, fullscreen_mode.bitsPerPixel), "Platformer", sf::Style::None);
      window.setMouseCursorGrabbed(false);
   }

   else
   {
      error();
      return;
   }

   window.setFramerateLimit(60);
   window.setPosition(sf::Vector2i(0, 0));
   resizeView();

   return;
}

void Game::resizeView()
{
   if(window_mode == "windowed")
   {
      window_width = window.getSize().x;
      window_height = window.getSize().y;
   }

   view.reset(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
   window.setView(view);

   return;
}

void Game::error()
{
   success = false;
   window.close();

   return;
}

void Game::run()
{
   while(window.isOpen())
   {
      currentGameState()->run();

      window.clear();
      currentGameState()->draw();
      window.display();
   }

   return;
}
