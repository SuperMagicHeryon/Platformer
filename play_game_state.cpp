#include "play_game_state.hpp"

#include "main_menu_game_state.hpp"

PlayGameState::PlayGameState(Game* _game, sf::RenderWindow& _window, ResourcesManager& _resources_manager) : GameState(_game, _window, _resources_manager)
{
   loadData();

   resources_manager.setTextureSmooth("background.jpg", true);
   background_sprite.setTexture(resources_manager.requestTexture("background.jpg"));

   resize();

   return;
}

void PlayGameState::loadData()
{
   if(!resources_manager.canLoadTexture("background.jpg"))
   {
      game->error();
      return;
   }

   return;
}

void PlayGameState::resize()
{
   //Window dimensions
   float window_width = static_cast<float>(window.getSize().x);
   float window_height = static_cast<float>(window.getSize().y);

   //Scale factors
   float horizontal_scale_factor = window_width / 1920.f;
   float vertical_scale_factor = window_height / 1080.f;

   //Resizing background
   background_sprite.setScale(horizontal_scale_factor, vertical_scale_factor);
   background_sprite.setPosition(0.f, 0.f);

   return;
}

void PlayGameState::draw() const
{
   window.draw(background_sprite);

   return;
}

void PlayGameState::run()
{
   sf::Event event;
   while(window.pollEvent(event))
   {
      if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
      {
         resources_manager.clearResources();
         game->changeGameState(new MainMenuGameState(game, window, resources_manager));
         return;
      }

      if(event.type == sf::Event::Resized)
      {
         game->resizeView();
         resize();
      }

      if(event.type == sf::Event::Closed)
      {
         window.close();
         return;
      }
   }

   return;
}
