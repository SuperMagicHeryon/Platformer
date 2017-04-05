#include "options_menu_game_state.hpp"

#include "main_menu_game_state.hpp"

OptionsMenuGameState::OptionsMenuGameState(Game* _game, sf::RenderWindow& _window, ResourcesManager& _resources_manager) : GameState(_game, _window, _resources_manager)
{
   loadData();

   //Initializing variables
   language = game->getLanguage();
   window_mode = game->getWindowMode();

   move_left_key_button_focus = false;
   move_right_key_button_focus = false;
   jump_key_button_focus = false;

   //Initializing background
   resources_manager.setTextureSmooth("background.png", true);
   background_sprite.setTexture(resources_manager.requestTexture("background.png"));

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

   //Initializing movement options
   if(language == "english")
   {
      options.push_back(new sf::Text("Move Left", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 50));

      options.push_back(new sf::Text("Move Right", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 50));

      options.push_back(new sf::Text("Jump", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 50));
   }

   else if(language == "french")
   {
      options.push_back(new sf::Text("Aller à Gauche", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 50));

      options.push_back(new sf::Text("Aller à Droite", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 50));

      options.push_back(new sf::Text("Sauter", resources_manager.requestFont("Ubuntu-C.ttf"), 70));
      buttons.push_back(new Button("", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 50));
   }

   //Initializing apply changes button
   if(language == "english")
      buttons.push_back(new Button("Apply", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));

   else if(language == "french")
      buttons.push_back(new Button("Appliquer", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));

   //Initializing main menu button
   if(language == "english")
      buttons.push_back(new Button("Main Menu", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));

   else if(language == "french")
      buttons.push_back(new Button("Menu", resources_manager.requestTexture("button.png"), resources_manager.requestFont("Ubuntu-C.ttf"), 70));

   setControlsButtonsTexts();
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
   if(!(resources_manager.canLoadTexture("background.png") &&
        resources_manager.canLoadTexture("button.png") &&
		  resources_manager.canLoadTexture("left_button.png") &&
		  resources_manager.canLoadTexture("right_button.png") &&
        resources_manager.canLoadFont("Ubuntu-C.ttf")))
   {
      game->error();
      return;
   }

   config_file.open("data/config/controls.config", std::fstream::in);

   if(!config_file)
   {
      game->error();
      return;
   }

   else
   {
      keys.push_back("");
      keys.push_back("");
      keys.push_back("");

      getline(config_file, keys[0]);
      getline(config_file, keys[1]);
      getline(config_file, keys[2]);

      config_file.close();
   }


   return;
}

void OptionsMenuGameState::writeData()
{
   game->setLanguage(language);
   game->setWindowMode(window_mode);

   config_file.open("data/config/controls.config", std::fstream::out);

   if(!config_file)
   {
      game->error();
      return;
   }

   else
   {
      config_file << keys[0] << std::endl << keys[1] << std::endl << keys[2];
      config_file.close();
   }

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

	   options[2]->setString("Move Left");
	   options[3]->setString("Move Right");
	   options[4]->setString("Jump");

	   buttons[7]->setTextString("Apply");
	   buttons[8]->setTextString("Main Menu");
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

	   options[2]->setString("Aller à Gauche");
      options[3]->setString("Aller à Droite");
      options[4]->setString("Sauter");

      buttons[7]->setTextString("Appliquer");
	   buttons[8]->setTextString("Menu");
	}

	setControlsButtonsTexts();
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

void OptionsMenuGameState::changeKey(std::string& _key, const sf::Event& _event)
{
   if(_event.type == sf::Event::KeyPressed)
   {
      if(_event.key.code == sf::Keyboard::A)
         _key = "a";

      else if(_event.key.code == sf::Keyboard::B)
         _key = "b";

      else if(_event.key.code == sf::Keyboard::C)
         _key = "c";

      else if(_event.key.code == sf::Keyboard::D)
         _key = "d";

      else if(_event.key.code == sf::Keyboard::E)
         _key = "e";

      else if(_event.key.code == sf::Keyboard::F)
         _key = "f";

      else if(_event.key.code == sf::Keyboard::G)
         _key = "g";

      else if(_event.key.code == sf::Keyboard::H)
         _key = "h";

      else if(_event.key.code == sf::Keyboard::I)
         _key = "i";

      else if(_event.key.code == sf::Keyboard::J)
         _key = "j";

      else if(_event.key.code == sf::Keyboard::K)
         _key = "k";

      else if(_event.key.code == sf::Keyboard::L)
         _key = "l";

      else if(_event.key.code == sf::Keyboard::M)
         _key = "m";

      else if(_event.key.code == sf::Keyboard::N)
         _key = "n";

      else if(_event.key.code == sf::Keyboard::O)
         _key = "o";

      else if(_event.key.code == sf::Keyboard::P)
         _key = "p";

      else if(_event.key.code == sf::Keyboard::Q)
         _key = "q";

      else if(_event.key.code == sf::Keyboard::R)
         _key = "r";

      else if(_event.key.code == sf::Keyboard::S)
         _key = "s";

      else if(_event.key.code == sf::Keyboard::T)
         _key = "t";

      else if(_event.key.code == sf::Keyboard::U)
         _key = "u";

      else if(_event.key.code == sf::Keyboard::V)
         _key = "v";

      else if(_event.key.code == sf::Keyboard::W)
         _key = "w";

      else if(_event.key.code == sf::Keyboard::X)
         _key = "x";

      else if(_event.key.code == sf::Keyboard::Y)
         _key = "y";

      else if(_event.key.code == sf::Keyboard::Z)
         _key = "z";

      else if(_event.key.code == sf::Keyboard::Left)
         _key = "left";

      else if(_event.key.code == sf::Keyboard::Right)
         _key = "right";

      else if(_event.key.code == sf::Keyboard::Up)
         _key = "up";

      else if(_event.key.code == sf::Keyboard::Down)
         _key = "down";

      else if(_event.key.code == sf::Keyboard::Space)
         _key = "space";

      else if(_event.key.code == sf::Keyboard::Num0)
         _key = "0";

      else if(_event.key.code == sf::Keyboard::Num1)
         _key = "1";

      else if(_event.key.code == sf::Keyboard::Num2)
         _key = "2";

      else if(_event.key.code == sf::Keyboard::Num3)
         _key = "3";

      else if(_event.key.code == sf::Keyboard::Num4)
         _key = "4";

      else if(_event.key.code == sf::Keyboard::Num5)
         _key = "5";

      else if(_event.key.code == sf::Keyboard::Num6)
         _key = "6";

      else if(_event.key.code == sf::Keyboard::Num7)
         _key = "7";

      else if(_event.key.code == sf::Keyboard::Num8)
         _key = "8";

      else if(_event.key.code == sf::Keyboard::Num9)
         _key = "9";

      else if(_event.key.code == sf::Keyboard::Numpad0)
         _key = "0(num)";

      else if(_event.key.code == sf::Keyboard::Numpad1)
         _key = "1(num)";

      else if(_event.key.code == sf::Keyboard::Numpad2)
         _key = "2(num)";

      else if(_event.key.code == sf::Keyboard::Numpad3)
         _key = "3(num)";

      else if(_event.key.code == sf::Keyboard::Numpad4)
         _key = "4(num)";

      else if(_event.key.code == sf::Keyboard::Numpad5)
         _key = "5(num)";

      else if(_event.key.code == sf::Keyboard::Numpad6)
         _key = "6(num)";

      else if(_event.key.code == sf::Keyboard::Numpad7)
         _key = "7(num)";

      else if(_event.key.code == sf::Keyboard::Numpad8)
         _key = "8(num)";

      else if(_event.key.code == sf::Keyboard::Numpad9)
         _key = "9(num)";
   }

   return;
}

void OptionsMenuGameState::setControlsButtonsTexts()
{
   for(size_t i = 0; i < keys.size(); i++)
   {
      std::string text;
      bool nextToUpper = true;

      for(size_t j = 0; j < keys[i].size(); j++)
      {
         if(keys[i][j] == '(')
         {
            nextToUpper = true;
            text += keys[i][j];
         }

         else if(nextToUpper)
         {
            nextToUpper = false;
            text += toupper(keys[i][j]);
         }

         else
            text += keys[i][j];
      }

      if(language == "french")
      {
         if(text == "Space")
            text = "Espace";

         else if(text == "Left")
            text = "Gauche";

         else if(text == "Right")
            text = "Droite";

         else if(text == "Up")
            text = "Haut";

         else if(text == "Down")
            text = "Bas";
      }

      buttons[i + 4]->setTextString(text);
   }

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
   for(size_t i = 0; i < 4; i++)
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
   for(size_t i = 0; i < 2; i++)
   {
	   options[i]->setScale(horizontal_scale_factor, vertical_scale_factor);
	   options[i]->setPosition((window_width - options[i]->getGlobalBounds().width) / 2.f - options[i]->getLocalBounds().left * horizontal_scale_factor,
			   	   	   	    buttons[i * 2]->getSprite().getPosition().y + (buttons[i * 2]->getSprite().getGlobalBounds().height - options[i]->getGlobalBounds().height) / 2.f - options[i]->getLocalBounds().top * vertical_scale_factor);
   }


   //Resizing controls buttons
   for(size_t i = 4; i < buttons.size() - 2; i++)
   {
      buttons[i]->setSpriteScale(horizontal_scale_factor, vertical_scale_factor);
      buttons[i]->setSpritePosition(window_width - buttons[i]->getSprite().getGlobalBounds().width - 40.f * horizontal_scale_factor,
                                    buttons[3]->getSprite().getPosition().y + buttons[3]->getSprite().getGlobalBounds().height + 40.f * vertical_scale_factor + (buttons[i]->getSprite().getGlobalBounds().height + 40.f * vertical_scale_factor) * (i - 4));

      buttons[i]->setTextScale(horizontal_scale_factor, vertical_scale_factor);
      buttons[i]->setTextPosition(buttons[i]->getSprite().getPosition().x + (buttons[i]->getSprite().getGlobalBounds().width - buttons[i]->getText().getGlobalBounds().width) / 2.f - buttons[i]->getText().getLocalBounds().left * horizontal_scale_factor,
                                  buttons[i]->getSprite().getPosition().y + (buttons[i]->getSprite().getGlobalBounds().height - buttons[i]->getText().getGlobalBounds().height) / 2.f - buttons[i]->getText().getLocalBounds().top * vertical_scale_factor);
   }

   //Resizing controls texts
   for(size_t i = 2; i < options.size(); i++)
   {
      options[i]->setScale(horizontal_scale_factor, vertical_scale_factor);
      options[i]->setPosition(40.f * horizontal_scale_factor,
                              buttons[i + 2]->getSprite().getPosition().y + (buttons[i + 2]->getSprite().getGlobalBounds().height - options[i]->getGlobalBounds().height) / 2.f - options[i]->getLocalBounds().top * vertical_scale_factor);
   }

   //Resizing apply changes button
   buttons[7]->setSpriteScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[7]->setSpritePosition(40.f * horizontal_scale_factor, window_height - buttons[7]->getSprite().getGlobalBounds().height - 40.f * vertical_scale_factor);

   buttons[7]->setTextScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[7]->setTextPosition(buttons[7]->getSprite().getPosition().x + (buttons[7]->getSprite().getGlobalBounds().width - buttons[7]->getText().getGlobalBounds().width) / 2.f - buttons[7]->getText().getLocalBounds().left * horizontal_scale_factor,
                               buttons[7]->getSprite().getPosition().y + (buttons[7]->getSprite().getGlobalBounds().height - buttons[7]->getText().getGlobalBounds().height) / 2.f - buttons[7]->getText().getLocalBounds().top * vertical_scale_factor);

   //Resizing main menu button
   buttons[8]->setSpriteScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[8]->setSpritePosition(window_width - buttons[8]->getSprite().getGlobalBounds().width - 40.f * horizontal_scale_factor,
                                 window_height - buttons[8]->getSprite().getGlobalBounds().height - 40.f * vertical_scale_factor);

   buttons[8]->setTextScale(horizontal_scale_factor, vertical_scale_factor);
   buttons[8]->setTextPosition(buttons[8]->getSprite().getPosition().x + (buttons[8]->getSprite().getGlobalBounds().width - buttons[8]->getText().getGlobalBounds().width) / 2.f - buttons[8]->getText().getLocalBounds().left * horizontal_scale_factor,
		   	   	   	   	 buttons[8]->getSprite().getPosition().y + (buttons[8]->getSprite().getGlobalBounds().height - buttons[8]->getText().getGlobalBounds().height) / 2.f - buttons[8]->getText().getLocalBounds().top * vertical_scale_factor);

   return;
}

void OptionsMenuGameState::draw() const
{
   window.draw(background_sprite);

   for(size_t i = 0; i < 4; i++)
      window.draw(buttons[i]->getSprite());

   for(size_t i = 4; i < buttons.size(); i++)
   {
         window.draw(buttons[i]->getSprite());
         window.draw(buttons[i]->getText());
   }

   for(size_t i = 0; i < options.size(); i++)
      window.draw(*options[i]);

   return;
}

void OptionsMenuGameState::run()
{
   sf::Event event;
   while(window.pollEvent(event))
   {
      if(move_left_key_button_focus || move_right_key_button_focus || jump_key_button_focus)
      {
         if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
         {
            if(move_left_key_button_focus)
            {
               changeKey(keys[0], event);
               move_left_key_button_focus = false;
               setControlsButtonsTexts();
               resize();
            }

            else if(move_right_key_button_focus)
            {
               changeKey(keys[1], event);
               move_right_key_button_focus = false;
               setControlsButtonsTexts();
               resize();
            }

            else if(jump_key_button_focus)
            {
               changeKey(keys[2], event);
               jump_key_button_focus = false;
               setControlsButtonsTexts();
               resize();
            }
         }
      }

      else
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
               move_left_key_button_focus = true;
               buttons[4]->setTextString("...");
               resize();
            }

            else if(buttons[5]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            {
               move_right_key_button_focus = true;
               buttons[5]->setTextString("...");
               resize();
            }

            else if(buttons[6]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            {
               jump_key_button_focus = true;
               buttons[6]->setTextString("...");
               resize();
            }

            else if(buttons[7]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            {
               writeData();
               game->resizeView();
               resize();
            }

            else if(buttons[8]->contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
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
