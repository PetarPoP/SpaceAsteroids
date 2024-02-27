#ifndef POKUSAJ_BULLET_H
#define POKUSAJ_BULLET_H

#include "Global.h"
#include "Physics.h"
#include <SFML/Audio.hpp>

// Speed of the bullet
constexpr float BULLET_SPEED = 500.0f;

// Life duration of the bullet
constexpr float BULLET_LIFE = 3.0f;

// Bullet class, inherits from Entity
class Bullet : public Entity{
    sf::CircleShape shape; // Shape of the bullet
    sf::Vector2f direction; // Direction of the bullet
    float lifeTime; // Lifetime of the bullet
public:
    // Constructor with position and direction parameters
    Bullet(sf::Vector2f position, sf::Vector2f direction);

    // Update function, overridden from Entity
    void update(float deltaTime) override;

    // Render function, overridden from Entity
    void render(sf::RenderWindow& window) override;
};

#endif //POKUSAJ_BULLET_H