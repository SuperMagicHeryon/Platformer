#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "stl_includes.hpp"
#include "sfml_includes.hpp"
#include <Box2D/Box2D.h>

class Entity
{
   public:
      Entity(const sf::Texture&);

   protected:
      sf::Sprite entity_sprite;
};

#endif //ENTITY_HPP
