#include "ResourceLoader.h"

#include <stdexcept>

namespace application {

ResourceLoader& ResourceLoader::getInstance() {
    static ResourceLoader instance;
    return instance;
}

const sf::Font& ResourceLoader::getFont() const { return _font; }

const sf::Texture& ResourceLoader::getSpriteSheet() const { return _spriteSheet; }

ResourceLoader::ResourceLoader() {
    if (!_font.loadFromFile("Assets/arial.ttf")) {
        throw std::runtime_error("Error loading font");
    }

    if (!_spriteSheet.loadFromFile("Assets/sprite.png")) {
        throw std::runtime_error("Error loading spritesheet");
    }
}

} // namespace application