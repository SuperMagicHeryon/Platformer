#include "saves_menu_game_state.hpp"

#include "main_menu_game_state.hpp"
#include "play_game_state.hpp"

SavesMenuGameState::SavesMenuGameState(Game* _game, sf::RenderWindow& _window, ResourcesManager& _resources_manager) : GameState(_game, _window, _resources_manager)
{
   loadData();

   //Initializing background
   resources_manager.setTextureSmooth("background.png", true);
   background_sprite.setTexture(resources_manager.requestTexture("background.png"));

   //Initializing buttons
   if(game->getLanguage() == "english")
   {
      buttons.push_back(new Button("Save 1", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("Save 2", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("Save 3", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));

      buttons.push_back(new Button("Back", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));
   }

   else if(game->getLanguage() == "french")
   {
      buttons.push_back(new Button("Fichier 1", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("Fichier 2", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("Fichier 3", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));

      buttons.push_back(new Button("Retour", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));
   }

   resize();

   return;
}

SavesMenuGameState::~SavesMenuGameState()
{
   while(!buttons.empty())
   {
      delete buttons.back();
      buttons.pop_back();
   }

   return;
}

void SavesMenuGameState::loadData()
{
   if(!(resources_manager.canLoadTexture("background.png") &&
        resources_manager.canLoadTexture("button.png") &&
        resources_manager.canLoadFont("Ubuntu-C.ttf")))
   {
      game->error();
      return;
   }

   return;
}

void SavesMenuGameState::resize()
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

   //Resizing buttons
   for(size_t i = 0; i < buttons.size() - 1; i++)
   {
      buttons[i]->setSpriteScale(horizontal_scale_factor, vertical_scale_factor);
      buttons[i]->setSpritePosition(40.f * horizontal_scale_factor,(buttons[i]->getSprite().getGlobalBounds().height + 40.f * vertical_scale_factor) * i + 40.f * vertical_scale_factor);

      buttons[i]->setTextScale(horizontal_scale_factor, vertical_scale_factor);
      buttons[i]->setTextPosition(buttons[i]->getSprite().getPosition().x + (buttons[i]->getSprite().getGlobalBounds().width - buttons[i]->getText().getGlobalBounds().width) / 2.f - buttons[i]->getText().getLocalBounds().left * horizontal_scale_factor,
                                  buttons[i]->getSprite().getPosition().y + (buttons[i]->getSprite().getGlobalBounds().height - buttons[i]->getText().getGlobalBounds().height) / 2.f - buttons[i]->getText().getLocalBounds().top * vertical_scale_factor);
   }

   buttons[3]->setSpriteScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[3]->setSpritePosition(window_width - buttons[3]->getSprite().getGlobalBounds().width - 40.f * horizontal_scale_factor,
		   	   	   	   	   	   	 window_height - buttons[3]->getSprite().getGlobalBounds().height - 40.f * vertical_scale_factor);

   buttons[3]->setTextScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[3]->setTextPosition(buttons[3]->getSprite().getPosition().x + (buttons[3]->getSprite().getGlobalBounds().width - buttons[3]->getText().getGlobalBounds().width) / 2.f - buttons[3]->getText().getLocalBounds().left * horizontal_scale_factor,
                               buttons[3]->getSprite().getPosition().y + (buttons[3]->getSprite().getGlobalBounds().height - buttons[3]->getText().getGlobalBounds().height) / 2.f - buttons[3]->getText().getLocalBounds().top * vertical_scale_factor);

   return;
}

void SavesMenuGameState::draw() const
{
   window.draw(background_sprite);

   for(size_t i = 0; i < buttons.size(); i++)
   {
      window.draw(buttons[i]->getSprite());
      window.draw(buttons[i]->getText());
   }

   return;
}

void SavesMenuGameState::run()
{
   sf::Event event;
   while(window.pollEvent(event))
   {
      if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
      {
         if(buttons[0]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) ||
            buttons[1]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) ||
            buttons[2]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
         {
            resources_manager.clearResources();
            game->changeGameState(new PlayGameState(game, window, resources_manager));
            return;
         }

         else if(buttons[3]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
         {
        	 resources_manager.clearResources();
        	 game->changeGameState(new MainMenuGameState(game, window, resources_manager));
        	 return;
         }
      }

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
