#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <SFML/Graphics/Font.hpp>

namespace application {

/**
 * @brief Handles loading game assets and provides methods other classes can use to retrieve these assets.
 *
 * When the resource loader is constructed it tries loading the font and sprite sheet for the game.
 *
 * Implements Scott Meyers' Singleton design pattern.
 */
class ResourceLoader {
public:
    static ResourceLoader& getInstance();

    ResourceLoader(const ResourceLoader&) = delete;
    ResourceLoader(ResourceLoader&&) = delete;
    ResourceLoader& operator=(ResourceLoader&&) = delete;
    ResourceLoader& operator=(const ResourceLoader&) = delete;

    /**
     * @brief Returns the loaded font.
     */
    const sf::Font& getFont() const;

    /**
     * @brief Returns the loaded sprite sheet.
     */
    const sf::Texture& getSpriteSheet() const;

private:
    ResourceLoader();
    ~ResourceLoader() = default;

    sf::Font _font;
    sf::Texture _spriteSheet;
};

} // namespace application

#endif // RESOURCELOADER_H
