#include "button.hpp"

Button::Button(const std::string& _text, const sf::Texture& _texture, const sf::Font& _font, unsigned int _size) : button_texture(_texture), button_font(_font)
{
   button_sprite.setTexture(button_texture);

   button_text.setString(_text);
   button_text.setFont(button_font);
   button_text.setCharacterSize(_size);

   return;
}

const sf::Sprite& Button::getSprite() const
{
   return button_sprite;
}

const sf::Text& Button::getText() const
{
   return button_text;
}

void Button::setSpriteScale(float _horizontal_scale_factor, float _vertical_scale_factor)
{
   button_sprite.setScale(_horizontal_scale_factor, _vertical_scale_factor);

   return;
}

void Button::setSpritePosition(float _x, float _y)
{
   button_sprite.setPosition(_x, _y);

   return;
}

void Button::setTextScale(float _horizontal_scale_factor, float _vertical_scale_factor)
{
   button_text.setScale(_horizontal_scale_factor, _vertical_scale_factor);

   return;
}

void Button::setTextPosition(float _x, float _y)
{
   button_text.setPosition(_x, _y);

   return;
}

bool Button::contains(int _x, int _y)
{
   return button_sprite.getGlobalBounds().contains(_x, _y);
}
