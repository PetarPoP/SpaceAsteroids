#ifndef POKUSAJ_ENTITY_H
#define POKUSAJ_ENTITY_H

#include "Global.h"

// Entity class
class Entity{
public:
    sf::Vector2f position; // Position of the entity
    float angle; // Angle of the entity

    // Constructor with position and angle parameters
    Entity(sf::Vector2f position, float angle) : position(position), angle(angle) {}

    // Virtual destructor
    virtual ~Entity() = default;

    // Pure virtual update function to be overridden by derived classes
    virtual void update(float deltaTime) = 0;

    // Pure virtual render function to be overridden by derived classes
    virtual void render(sf::RenderWindow& window) = 0;
};

#endif //POKUSAJ_ENTITY_H