#include "game_state.hpp"

GameState::GameState(Game* _game, sf::RenderWindow& _window, ResourcesManager& _resources_manager) : game(_game), window(_window), resources_manager(_resources_manager)
{
   return;
}

GameState::~GameState()
{
   return;
}
