#include "resources_manager.hpp"

ResourcesManager::ResourcesManager() : textures_map(), fonts_map(), sound_buffers_map()
{
   return;
}

bool ResourcesManager::canLoadTexture(const std::string& _path)
{
   return textures_map[_path].loadFromFile("data/media/textures/" + _path);
}

bool ResourcesManager::canLoadFont(const std::string& _path)
{
   return fonts_map[_path].loadFromFile("data/media/fonts/" + _path);
}

bool ResourcesManager::canLoadSoundBuffer(const std::string& _path)
{
   return sound_buffers_map[_path].loadFromFile("data/media/sounds/" + _path);
}

const sf::Texture& ResourcesManager::requestTexture(const std::string& _path)
{
   return textures_map[_path];
}

const sf::Font& ResourcesManager::requestFont(const std::string& _path)
{
   return fonts_map[_path];
}

const sf::SoundBuffer& ResourcesManager::requestSoundBuffer(const std::string& _path)
{
   return sound_buffers_map[_path];
}

void ResourcesManager::setTextureSmooth(const std::string& _path, const bool& _smooth)
{
   textures_map[_path].setSmooth(_smooth);

   return;
}

void ResourcesManager::clearResources()
{
   textures_map.clear();
   fonts_map.clear();
   sound_buffers_map.clear();

   return;
}
