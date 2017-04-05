#include "play_game_state.hpp"

#include "main_menu_game_state.hpp"

PlayGameState::PlayGameState(Game* _game, sf::RenderWindow& _window, ResourcesManager& _resources_manager) : GameState(_game, _window, _resources_manager)
{
   loadData();

   //Initializing background
   resources_manager.setTextureSmooth("background.png", true);
   background_sprite.setTexture(resources_manager.requestTexture("background.png"));

   level = new Level(game, "data/levels/1-1.lvl", resources_manager.requestTexture("little_blue_thing.png"), resources_manager.requestTexture("grass.png"), resources_manager.requestTexture("stone.png"));

   resize();

   return;
}

PlayGameState::~PlayGameState()
{
   delete level;

   return;
}

void PlayGameState::loadData()
{
   if(!(resources_manager.canLoadTexture("background.png") &&
        resources_manager.canLoadTexture("little_blue_thing.png") &&
        resources_manager.canLoadTexture("grass.png") &&
        resources_manager.canLoadTexture("stone.png")))
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
      std::string key;

      for(int i = 0; i < 3; i++)
      {
         getline(config_file, key);

         if(key == "a")
            keys.push_back(sf::Keyboard::A);

         else if(key == "b")
            keys.push_back(sf::Keyboard::B);

         else if(key == "c")
            keys.push_back(sf::Keyboard::C);

         else if(key == "d")
            keys.push_back(sf::Keyboard::D);

         else if(key == "e")
            keys.push_back(sf::Keyboard::E);

         else if(key == "f")
            keys.push_back(sf::Keyboard::F);

         else if(key == "g")
            keys.push_back(sf::Keyboard::G);

         else if(key == "h")
            keys.push_back(sf::Keyboard::H);

         else if(key == "i")
            keys.push_back(sf::Keyboard::I);

         else if(key == "j")
            keys.push_back(sf::Keyboard::J);

         else if(key == "k")
            keys.push_back(sf::Keyboard::K);

         else if(key == "l")
            keys.push_back(sf::Keyboard::L);

         else if(key == "m")
            keys.push_back(sf::Keyboard::M);

         else if(key == "n")
            keys.push_back(sf::Keyboard::N);

         else if(key == "o")
            keys.push_back(sf::Keyboard::O);

         else if(key == "p")
            keys.push_back(sf::Keyboard::P);

         else if(key == "q")
            keys.push_back(sf::Keyboard::Q);

         else if(key == "r")
            keys.push_back(sf::Keyboard::R);

         else if(key == "s")
            keys.push_back(sf::Keyboard::S);

         else if(key == "t")
            keys.push_back(sf::Keyboard::T);

         else if(key == "u")
            keys.push_back(sf::Keyboard::U);

         else if(key == "v")
            keys.push_back(sf::Keyboard::V);

         else if(key == "w")
            keys.push_back(sf::Keyboard::W);

         else if(key == "x")
            keys.push_back(sf::Keyboard::X);

         else if(key == "y")
            keys.push_back(sf::Keyboard::Y);

         else if(key == "z")
            keys.push_back(sf::Keyboard::Z);

         else if(key == "space")
            keys.push_back(sf::Keyboard::Space);

         else if(key == "left")
            keys.push_back(sf::Keyboard::Left);

         else if(key == "right")
            keys.push_back(sf::Keyboard::Right);

         else if(key == "up")
            keys.push_back(sf::Keyboard::Up);

         else if(key == "down")
            keys.push_back(sf::Keyboard::Down);

         else if(key == "0")
            keys.push_back(sf::Keyboard::Num0);

         else if(key == "1")
            keys.push_back(sf::Keyboard::Num1);

         else if(key == "2")
            keys.push_back(sf::Keyboard::Num2);

         else if(key == "3")
            keys.push_back(sf::Keyboard::Num3);

         else if(key == "4")
            keys.push_back(sf::Keyboard::Num4);

         else if(key == "5")
            keys.push_back(sf::Keyboard::Num5);

         else if(key == "6")
            keys.push_back(sf::Keyboard::Num6);

         else if(key == "7")
            keys.push_back(sf::Keyboard::Num7);

         else if(key == "8")
            keys.push_back(sf::Keyboard::Num8);

         else if(key == "9")
            keys.push_back(sf::Keyboard::Num9);

         else if(key == "0(num)")
            keys.push_back(sf::Keyboard::Numpad0);

         else if(key == "1(num)")
            keys.push_back(sf::Keyboard::Numpad1);

         else if(key == "2(num)")
            keys.push_back(sf::Keyboard::Numpad2);

         else if(key == "3(num)")
            keys.push_back(sf::Keyboard::Numpad3);

         else if(key == "4(num)")
            keys.push_back(sf::Keyboard::Numpad4);

         else if(key == "5(num)")
            keys.push_back(sf::Keyboard::Numpad5);

         else if(key == "6(num)")
            keys.push_back(sf::Keyboard::Numpad6);

         else if(key == "7(num)")
            keys.push_back(sf::Keyboard::Numpad7);

         else if(key == "8(num)")
            keys.push_back(sf::Keyboard::Numpad8);

         else if(key == "9(num)")
            keys.push_back(sf::Keyboard::Numpad9);
      }

      config_file.close();
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

   level->draw(window);

   return;
}

void PlayGameState::run()
{
   level->update();

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
