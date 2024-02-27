#include "Player.h"

// Player constructor
Player::Player() : Entity(sf::Vector2f (500, 500), 0), array(sf::LineStrip, 9),
    shootTimer(), powerUpTimer_Speed(),  speedBoost(1), powerUpTimer_FastShoot(),
    fastShoot(1), powerUpTimer_Shield(), shield(false)
{
    // Setting the player's shape
    array[0].position = sf::Vector2f(20, 0); // Right point of the spaceship
    array[1].position = sf::Vector2f(-15, -7.5);
    array[2].position = sf::Vector2f(5, -15); // Top left point of the spaceship
    array[3].position = sf::Vector2f(-25, -20);
    array[4].position = sf::Vector2f(-35, 0); // Center left point of the spaceship
    array[5].position = sf::Vector2f(-25, 20);
    array[6].position = sf::Vector2f(5, 15); // Bottom left point of the spaceship
    array[7].position = sf::Vector2f(-15, 7.5);
    array[8].position = array[0].position; // Closing the shape by going back to the right point of the spaceship

    // Setting the color of the player
    for (size_t i = 0; i < array.getVertexCount(); ++i) {
        array[i].color = sf::Color::White;
    }
}

// Updating the player
void Player::update(float deltaTime) {
    shootTimer -= deltaTime;

    // If the player has a power up, the timer will decrease
    if (powerUpTimer_Speed > 0.0f) {
        powerUpTimer_Speed -= deltaTime;
    } else {
        speedBoost = 1;
    }

    if (powerUpTimer_FastShoot > 0.0f) {
        powerUpTimer_FastShoot -= deltaTime;
    } else {
        fastShoot = 1;
    }

    if (powerUpTimer_Shield > 0.0f) {
        powerUpTimer_Shield -= deltaTime;
    } else {
        shield = false;
    }

    // Controlling the player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angle -= TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angle += TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        float radians = angle * (PI / 180.0f);
        float DeltaTime = deltaTime * PLAYER_SPEED * speedBoost;

        // Moving the player
        position.x += std::cos(radians) * DeltaTime;
        position.y += std::sin(radians) * DeltaTime;

        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f) {
        // Playing the shoot sound
        Game::shootSound.play();
        // Resetting the shoot timer
        shootTimer = SHOOT_DELAY * fastShoot;
        // Calculating the angle of the bullet
        float radians = angle * (PI / 180.0f);

        // Creating a bullet
        Game::toAddList.push_back(new Bullet(position, sf::Vector2f(std::cos(radians), std::sin(radians))));
    }

    // Checking if the player intersects with an asteroid
    sf::Transform playerTransform = sf::Transform().translate(position).rotate(angle);

    for (auto & entitie : Game::entities) {
        if (typeid(*entitie) == typeid(Asteroid)) {
            auto* asteroid = dynamic_cast<Asteroid*>(entitie);

            // If the asteroid is hit, it will be destroyed
            if (asteroid->getLife() < ASTEROID_HIT_TIME) {
                continue;
            }

            // Checking if the player intersects with an asteroid
            sf::Transform asteroidTransform = sf::Transform()
                    .translate(asteroid->position)
                    .rotate(asteroid->angle);

            // If the player intersects with an asteroid, the game will be over
            if (physics::intersects(physics::getTransformed(array, playerTransform),
                                    physics::getTransformed(asteroid->getVertexArray() , asteroidTransform)) && !shield) {
                Game::gameOver();
            }
        }
        // Checking if the player intersects with a power up
        else if (typeid(*entitie) == typeid(PowerUp)) {
            auto* powerUp = dynamic_cast<PowerUp*>(entitie);

            // Checking if the player intersects with a power up
            sf::Transform powerUpTransform = sf::Transform()
                    .translate(powerUp->position)
                    .rotate(powerUp->angle);

            // If the player intersects with a power up, the power up will be destroyed
            if (physics::intersects(physics::getTransformed(array, playerTransform),
                                    physics::getTransformed(powerUp->getVertexArray() , powerUpTransform))) {
                Game::toRemoveList.push_back(std::find(Game::entities.begin(), Game::entities.end(), powerUp));
                Game::decreasePowerUpCount();

                // If the power up is a speed boost, the player will move faster
                if (powerUp->getType() == PowerUp::Type::SpeedBoost) {
                    speedBoost = 2.0f;
                    powerUpTimer_Speed = POWERUP_DURATION;
                } else if (powerUp->getType() == PowerUp::Type::FasterShooting) {
                    fastShoot = 0.5;
                    powerUpTimer_FastShoot = POWERUP_DURATION;
                } else {
                    shield = true;
                    powerUpTimer_Shield = POWERUP_DURATION;
                }
            }
        }
    }
}

// Rendering the player
void Player::render(sf::RenderWindow& window) {
    // If the player has the shield power up, the color of the player will be cyan
    if (shield) {
        for (size_t i = 0; i < array.getVertexCount(); ++i) {
            array[i].color = sf::Color::Cyan;
        }
    } else {
        for (size_t i = 0; i < array.getVertexCount(); ++i) {
            array[i].color = sf::Color::White;
        }
    }

    // Drawing the player
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}