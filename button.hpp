#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "sfml_includes.hpp"
#include "resources_manager.hpp"

class Button
{
   public:
      Button(const std::string&, const sf::Texture&, const sf::Font&, unsigned int);

      const sf::Sprite& getSprite() const;
      const sf::Text& getText() const;

      void setSpriteScale(float, float);
      void setSpritePosition(float, float);

      void setTextScale(float, float);
      void setTextPosition(float, float);

      bool contains(int, int);

   private:
      const sf::Texture& button_texture;
      sf::Sprite button_sprite;

      sf::Text button_text;
      const sf::Font& button_font;
};

#endif //BUTTON_HPP
