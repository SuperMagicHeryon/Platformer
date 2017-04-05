#include "entity.hpp"

Entity::Entity(const sf::Texture& _entity_texture)
{
   entity_sprite.setTexture(_entity_texture);

   return;
}
