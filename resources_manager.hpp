#ifndef RESOURCES_MANAGER_HPP
#define RESOURCES_MANAGER_HPP

#include "stl_includes.hpp"
#include "sfml_includes.hpp"
#include <Box2D/Box2D.h>

class ResourcesManager
{
   public:
      ResourcesManager();

      bool canLoadTexture(const std::string&);
      bool canLoadFont(const std::string&);
      bool canLoadSoundBuffer(const std::string&);

      const sf::Texture& requestTexture(const std::string&);
      const sf::Font& requestFont(const std::string&);
      const sf::SoundBuffer& requestSoundBuffer(const std::string&);

      void setTextureSmooth(const std::string&, const bool&);

      void clearResources();

   private:
      std::map<const std::string, sf::Texture> textures_map;
      std::map<const std::string, sf::Font> fonts_map;
      std::map<const std::string, sf::SoundBuffer> sound_buffers_map;
};

#endif //RESOURCES_MANAGER_HPP
