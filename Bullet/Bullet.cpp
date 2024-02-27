#include "Bullet.h"

// Constructor for the Bullet class
Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
: shape(1.0f), direction(direction), Entity(position, 0.0f), lifeTime(BULLET_LIFE) {} // Initialize the bullet with given position and direction

// Update the state of the bullet
void Bullet::update(float deltaTime) {
    // Update the position of the bullet
    position += direction * BULLET_SPEED * deltaTime;

    // Decrease the lifetime of the bullet and remove it if it's lifetime is over
    if ((lifeTime -= deltaTime) <= 0.0f) {
        Game::toRemoveList.push_back(std::find(Game::entities.begin(), Game::entities.end(), this));
    }

    // Check for collision with asteroids
    for (auto & entity : Game::entities) {
        if (typeid(*entity) == typeid(Asteroid)) {
            auto* asteroid = dynamic_cast<Asteroid*>(entity);
            sf::Transform transform = sf::Transform()
                    .translate(asteroid->position)
                    .rotate(asteroid->angle);

            // If the bullet intersects with an asteroid
            if (physics::intersects(position,physics::getTransformed(asteroid->getVertexArray() , transform))) {
                lifeTime = 0.0f; // Bullet is destroyed
                asteroid->decrementHitCount(); // Decrease the hit count of the asteroid

                // If the asteroid is destroyed
                if (asteroid->getHitCount() <= 0) {
                    // Remove the asteroid
                    Game::toRemoveList.push_back(std::find(Game::entities.begin(), Game::entities.end(), asteroid));
                    Game::score += 10; // Increase the score

                    // If the asteroid's size is greater than 1, create two new smaller asteroids
                    if (asteroid->getSize() > 1) {
                        sf::Vector2f newDirection1 = Asteroid::getRandomDirection();
                        sf::Vector2f newDirection2 = Asteroid::getRandomDirection();
                        auto* newAsteroid1 = new Asteroid(newDirection1, asteroid->position, asteroid->getSize() - 1);
                        auto* newAsteroid2 = new Asteroid(newDirection2, asteroid->position, asteroid->getSize() - 1);

                        // Scale down the size of the new asteroids
                        float scaleFactor = 0.5f;
                        sf::VertexArray scaledVertexArray1(sf::LineStrip, newAsteroid1->getVertexArray().getVertexCount());
                        sf::VertexArray scaledVertexArray2(sf::LineStrip, newAsteroid2->getVertexArray().getVertexCount());
                        for (size_t i = 0; i < newAsteroid1->getVertexArray().getVertexCount(); ++i) {
                            scaledVertexArray1[i].position = newAsteroid1->getVertexArray()[i].position * scaleFactor;
                        }
                        for (size_t i = 0; i < newAsteroid2->getVertexArray().getVertexCount(); ++i) {
                            scaledVertexArray2[i].position = newAsteroid2->getVertexArray()[i].position * scaleFactor;
                        }
                        newAsteroid1->setVertexArray(scaledVertexArray1);
                        newAsteroid2->setVertexArray(scaledVertexArray2);

                        // Add the new asteroids to the game
                        Game::toAddList.push_back(newAsteroid1);
                        Game::toAddList.push_back(newAsteroid2);
                    }
                }
            }
        }
    }
}

// Render the bullet on the window
void Bullet::render(sf::RenderWindow& window) {
    window.draw(shape, sf::Transform().translate(position));
}
