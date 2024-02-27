#ifndef POKUSAJ_POWERUP_H
#define POKUSAJ_POWERUP_H

#include "Global.h"

constexpr float POWERUP_DURATION = 5.0f; // PowerUp duration in seconds
constexpr float POWERUP_SPEED = 80.0f; // PowerUp speed in pixels per second
constexpr float POWERUP_SPAWN_TIME = 5.0f; // PowerUp spawn time in seconds
constexpr int POWERUP_ON_SCREEN = 2; // Number of PowerUps on screen at the same time

class PowerUp : public Entity {
    public:
        // PowerUp types
        enum class Type {
            SpeedBoost,
            FasterShooting,
            Shield,
        };

        // Returns a random PowerUp type
        static int getRandomType();

        // Constructor
        explicit PowerUp(sf::Vector2f direction = getRandomDirection(), sf::Vector2f position = getRandomPosition());

        // Updates the PowerUp
        void update(float deltaTime) override;

        // Renders the PowerUp
        void render(sf::RenderWindow& window) override;

        // Returns a random direction
        static sf::Vector2f getRandomDirection();
        // Returns a random position on the screen
        static sf::Vector2f getRandomPosition();
        // Returns the PowerUp's bounding box
        const sf::VertexArray& getVertexArray();

        // Returns the PowerUp's type
        Type getType() const {
            return type;
        }
    private:
        sf::VertexArray array; // PowerUp's bounding box
        sf::Vector2f direction; // PowerUp's direction

        Type type; // PowerUp's type
};

#endif //POKUSAJ_POWERUP_H
