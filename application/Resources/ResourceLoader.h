#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <SFML/Graphics/Font.hpp>

namespace application {

class ResourceLoader {
public:
    ~ResourceLoader() = default;
    static ResourceLoader* getInstance();

    const sf::Font& getFont() const;
    const sf::Texture& getSpriteSheet() const;

private:
    ResourceLoader();
    static ResourceLoader* _instance;

    sf::Font _font;
    sf::Texture _spriteSheet;
};

} // namespace application

#endif // RESOURCELOADER_H
