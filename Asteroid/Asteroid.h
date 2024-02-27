#ifndef POKUSAJ_ASTEROID_H
#define POKUSAJ_ASTEROID_H

#include "Global.h"
#include "Entity.h"

// Constants for asteroid properties
constexpr float ASTEROID_W = 100.0f; // Width of the asteroid
constexpr float ASTEROID_H = 90.0f; // Height of the asteroid
constexpr float ASTEROID_SPIN = 25.0f; // Spin speed of the asteroid
constexpr float ASTEROID_SPEED = 180.0f; // Movement speed of the asteroid
constexpr float ASTEROID_HIT_TIME = 1.0f; // Time after asteroid hit
constexpr float ASTEROID_SPAWN_TIME = 3.0f; // Time between asteroid spawns

constexpr float SAFE_DISTANCE = 200.0f; // Safe distance from the player

constexpr int ASTEROID_HIT_POINT = 3; // Hit points of the asteroid

// Asteroid class, inherits from Entity
class Asteroid : public Entity{
    sf::VertexArray array; // Vertex array for the asteroid shape
    sf::Vector2f direction; // Direction of the asteroid

    int size; // Size of the asteroid
    int hitCount; // Number of hits the asteroid can take
    float life; // Lifetime of the asteroid
    public:
        // Constructor with default parameters
        explicit Asteroid(sf::Vector2f direction = Asteroid::getRandomDirection(),
                 sf::Vector2f position = Asteroid::getRandomPosition(), int size = 2);

        // Update function, overridden from Entity
        void update(float deltaTime) override;

        // Render function, overridden from Entity
        void render(sf::RenderWindow& window) override;

        // Getter for the vertex array
        const sf::VertexArray& getVertexArray() const;

        // Static function to get a random direction
        static sf::Vector2f getRandomDirection();

        // Static function to get a random position
        static sf::Vector2f getRandomPosition();

        // Setter for the vertex array
        void setVertexArray(const sf::VertexArray& newArray) {
            array = newArray;
        }

        // Getter for the lifetime
        float getLife() const {
            return life;
        }

        // Getter for the hit count
        int getHitCount() const {
            return hitCount;
        }

        // Function to decrement the hit count
        void decrementHitCount() {
            --hitCount;
        }

        // Getter for the size
        int getSize() const {
            return size;
        }
};

#endif //POKUSAJ_ASTEROID_H