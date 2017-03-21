#include "options_menu_game_state.hpp"

#include "main_menu_game_state.hpp"

OptionsMenuGameState::OptionsMenuGameState(Game* _game, sf::RenderWindow& _window, ResourcesManager& _resources_manager) : GameState(_game, _window, _resources_manager)
{
   loadData();

   //Initializing variables
   language = game->getLanguage();
   window_mode = game->getWindowMode();

   //Initializing background
   resources_manager.setTextureSmooth("background.jpg", true);
   background_sprite.setTexture(resources_manager.requestTexture("background.jpg"));

   //Initializing language option
   buttons.push_back(new Button("", resources_manager.requestTexture("left_button.png"), sf::Font(), 0));
   buttons.push_back(new Button("", resources_manager.requestTexture("right_button.png"), sf::Font(), 0));

   if(language == "english")
      options.push_back(new sf::Text("English", resources_manager.requestFont("Ubuntu-C.ttf"), 70));

   else if(language == "french")
      options.push_back(new sf::Text("Français", resources_manager.requestFont("Ubuntu-C.ttf"), 70));

   //Initializing window mode option
   buttons.push_back(new Button("", resources_manager.requestTexture("left_button.png"), sf::Font(), 0));
   buttons.push_back(new Button("", resources_manager.requestTexture("right_button.png"), sf::Font(), 0));

   if(language == "english")
   {
      if(window_mode == "windowed")
         options.push_back(new sf::Text("Windowed", resources_manager.requestFont("Ubuntu-C.ttf"), 70));

      else if(window_mode == "fullscreen")
         options.push_back(new sf::Text("Fullscreen", resources_manager.requestFont("Ubuntu-C.ttf"), 70));

      else if(window_mode == "borderless_windowed")
         options.push_back(new sf::Text("Borderless Windowed", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
   }

   else if(language == "french")
   {
      if(window_mode == "windowed")
         options.push_back(new sf::Text("Fenêtré", resources_manager.requestFont("Ubuntu-C.ttf"), 70));

      else if(window_mode == "fullscreen")
         options.push_back(new sf::Text("Plein Écran", resources_manager.requestFont("Ubuntu-C.ttf"), 70));

      else if(window_mode == "borderless_windowed")
         options.push_back(new sf::Text("Fenêtré Plein Écran", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
   }

   //Initializing main menu button
   buttons.push_back(new Button("Main Menu", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));

   resize();

   return;
}

OptionsMenuGameState::~OptionsMenuGameState()
{
   while(!buttons.empty())
   {
	   delete buttons.back();
	   buttons.pop_back();
   }

   while(!options.empty())
   {
	   delete options.back();
	   options.pop_back();
   }

   return;
}

void OptionsMenuGameState::loadData()
{
   if(!(resources_manager.canLoadTexture("background.jpg") &&
        resources_manager.canLoadTexture("button.png") &&
		resources_manager.canLoadTexture("left_button.png") &&
		resources_manager.canLoadTexture("right_button.png") &&
        resources_manager.canLoadFont("Ubuntu-C.ttf")))
   {
      game->error();
      return;
   }

   return;
}

void OptionsMenuGameState::writeData()
{
   game->setLanguage(language);
   game->setWindowMode(window_mode);

   return;
}

void OptionsMenuGameState::changeLanguage(int _direction)
{
	if(_direction == -1)
	{
		if(language == "english")
			language = "french";

		else if(language == "french")
			language = "english";
	}

	else
	{
		if(language == "english")
			language = "french";

		else if(language == "french")
			language = "english";
	}

	if(language == "english")
	{
	   options[0]->setString("English");

	   if(window_mode == "windowed")
	      options[1]->setString("Windowed");

	   else if(window_mode == "fullscreen")
	      options[1]->setString("Fullscreen");

	   else if(window_mode == "borderless_windowed")
	      options[1]->setString("Borderless Windowed");
   }

	else if(language == "french")
	{
	   options[0]->setString("Français");

	   if(window_mode == "windowed")
         options[1]->setString("Fenêtré");

      else if(window_mode == "fullscreen")
         options[1]->setString("Plein Écran");

      else if(window_mode == "borderless_windowed")
         options[1]->setString("Fenêtré Plein Écran");
	}

	resize();

	return;
}

void OptionsMenuGameState::changeWindowMode(int _direction)
{
	if(_direction == -1)
	{
      if(window_mode == "windowed")
         window_mode = "borderless_windowed";

      else if(window_mode == "fullscreen")
         window_mode = "windowed";

      else if(window_mode == "borderless_windowed")
         window_mode = "fullscreen";
	}

	else
	{
	   if(window_mode == "windowed")
         window_mode = "fullscreen";

      else if(window_mode == "fullscreen")
         window_mode = "borderless_windowed";

      else if(window_mode == "borderless_windowed")
         window_mode = "windowed";
	}

	if(language == "english")
   {
      if(window_mode == "windowed")
         options[1]->setString("Windowed");

      else if(window_mode == "fullscreen")
         options[1]->setString("Fullscreen");

      else if(window_mode == "borderless_windowed")
         options[1]->setString("Borderless Windowed");
   }

   else if(language == "french")
   {
      if(window_mode == "windowed")
         options[1]->setString("Fenêtré");

      else if(window_mode == "fullscreen")
         options[1]->setString("Plein Écran");

      else if(window_mode == "borderless_windowed")
         options[1]->setString("Fenêtré Plein Écran");
   }

	resize();

	return;
}

void OptionsMenuGameState::resize()
{
   //Window dimensions
   float window_width = static_cast<float>(window.getSize().x);
   float window_height = static_cast<float>(window.getSize().y);

   //Scale factors
   float horizontal_scale_factor =  window_width / 1920.f;
   float vertical_scale_factor = window_height / 1080.f;

   background_sprite.setScale(horizontal_scale_factor, vertical_scale_factor);
   background_sprite.setPosition(0.f, 0.f);

   //Resizing buttons
   for(size_t i = 0; i < buttons.size() - 1; i++)
   {
	   buttons[i]->setSpriteScale(horizontal_scale_factor, vertical_scale_factor);
	   if(i % 2 == 0)
		   buttons[i]->setSpritePosition(horizontal_scale_factor * 40.f,
				   	   	   	   	   	   	 static_cast<float>(i / 2) * (40.f * vertical_scale_factor + buttons[i]->getSprite().getGlobalBounds().height) + 40.f * vertical_scale_factor);

	   else
		   buttons[i]->setSpritePosition(window_width - buttons[i]->getSprite().getGlobalBounds().width - horizontal_scale_factor * 40.f,
				   	   	   	   	   	   	 static_cast<float>(i / 2) * (40.f * vertical_scale_factor + buttons[i]->getSprite().getGlobalBounds().height) + 40.f * vertical_scale_factor);
   }

   //Resizing texts
   for(size_t i = 0; i < options.size(); i++)
   {
	   options[i]->setScale(horizontal_scale_factor, vertical_scale_factor);
	   options[i]->setPosition((window_width - options[i]->getGlobalBounds().width) / 2.f - options[i]->getLocalBounds().left * horizontal_scale_factor,
			   	   	   	   	   buttons[i * 2]->getSprite().getPosition().y + (buttons[i * 2]->getSprite().getGlobalBounds().height - options[i]->getGlobalBounds().height) / 2.f - options[i]->getLocalBounds().top * vertical_scale_factor);
   }

   //Resizing main menu button
   buttons[4]->setSpriteScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[4]->setSpritePosition(window_width - buttons[4]->getSprite().getGlobalBounds().width - 40.f * horizontal_scale_factor,
                                 window_height - buttons[4]->getSprite().getGlobalBounds().height - 40.f * vertical_scale_factor);
   buttons[4]->setTextScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[4]->setTextPosition(buttons[4]->getSprite().getPosition().x + (buttons[4]->getSprite().getGlobalBounds().width - buttons[4]->getText().getGlobalBounds().width) / 2.f - buttons[4]->getText().getLocalBounds().left * horizontal_scale_factor,
		   	   	   	   	   	   buttons[4]->getSprite().getPosition().y + (buttons[4]->getSprite().getGlobalBounds().height - buttons[4]->getText().getGlobalBounds().height) / 2.f - buttons[4]->getText().getLocalBounds().top * vertical_scale_factor);

   return;
}

void OptionsMenuGameState::draw() const
{
   window.draw(background_sprite);

   for(size_t i = 0; i < buttons.size() - 1; i++)
   {
	   window.draw(buttons[i]->getSprite());
   }

   for(size_t i = 0; i < options.size(); i++)
   {
	   window.draw(*options[i]);
   }

   window.draw(buttons[4]->getSprite());
   window.draw(buttons[4]->getText());

   return;
}

void OptionsMenuGameState::run()
{
   sf::Event event;
   while(window.pollEvent(event))
   {
      if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
      {
    	 if(buttons[0]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
    		 changeLanguage(-1);

    	 else if(buttons[1]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			 changeLanguage(1);

    	 else if(buttons[2]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			 changeWindowMode(-1);

    	 else if(buttons[3]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			 changeWindowMode(1);

    	 else if(buttons[4]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
         {
    	      writeData();
            resources_manager.clearResources();
            game->changeGameState(new MainMenuGameState(game, window, resources_manager));
            return;
         }
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
