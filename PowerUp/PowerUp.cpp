#include "PowerUp.h"

#include <cmath>

// Constructor for the PowerUp class
PowerUp::PowerUp(sf::Vector2f direction, sf::Vector2f position)
    : Entity(position, 0), direction(direction), array(sf::LineStrip, 9), type(static_cast<Type>(getRandomType())) {
    array[0].position = sf::Vector2f(0, 20); // Top point of the power-up shape
    array[1].position = sf::Vector2f(15, 15); // Top right point of the power-up shape
    array[2].position = sf::Vector2f(20, 0); // Right point of the power-up shape
    array[3].position = sf::Vector2f(15, -15); // Bottom right point of the power-up shape
    array[4].position = sf::Vector2f(0, -20); // Bottom point of the power-up shape
    array[5].position = sf::Vector2f(-15, -15); // Bottom left point of the power-up shape
    array[6].position = sf::Vector2f(-20, 0); // Left point of the power-up shape
    array[7].position = sf::Vector2f(-15, 15); // Top left point of the power-up shape
    array[8].position = array[0].position; // Closing the shape by going back to the top point of the power-up shape

    // Setting the color of the power-up shape
    for (size_t i = 0; i < array.getVertexCount(); ++i) {
        if (type == Type::SpeedBoost) {
            array[i].color = sf::Color::Yellow; // If the power-up type is SpeedBoost, color it yellow
        } else if (type == Type::FasterShooting) {
            array[i].color = sf::Color::Red; // If the power-up type is FasterShooting, color it red
        } else {
            array[i].color = sf::Color::Cyan; // If the power-up type is Shield, color it cyan
        }
    }
}

// Update the power-up
void PowerUp::update(float deltaTime) {
    position += direction * POWERUP_SPEED * deltaTime; // Update the position of the power-up based on its direction and speed

    sf::FloatRect bounds = array.getBounds(); // Get the bounds of the power-up shape

    // Check if the power-up has hit the left or right edge of the screen
    if (position.x - bounds.width / 2 < 0) {
        direction.x = std::abs(direction.x); // If it hit the left edge, make sure it moves to the right
    } else if (position.x + bounds.width / 2 > SCREEN_WIDTH) {
        direction.x = -std::abs(direction.x); // If it hit the right edge, make sure it moves to the left
    }

    // Check if the power-up has hit the top or bottom edge of the screen
    if (position.y - bounds.height / 2 < 0) {
        direction.y = std::abs(direction.y); // If it hit the top edge, make sure it moves downwards
    } else if (position.y + bounds.height / 2 > SCREEN_HEIGHT) {
        direction.y = -std::abs(direction.y); // If it hit the bottom edge, make sure it moves upwards
    }
}

// Render the power-up
void PowerUp::render(sf::RenderWindow &window) {
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}

// Get a random power-up type
int PowerUp::getRandomType() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 2);

    return dis(gen);
}

// Get a random direction for the power-up
sf::Vector2f PowerUp::getRandomDirection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 2.0f * PI);

    float angle = dis(gen);
    return {std::cos(angle), std::sin(angle)};
}

// Get a random position for the power-up
sf::Vector2f PowerUp::getRandomPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    // The power-up should not spawn too close to the edges of the screen
    std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);
    std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);

    return {xAxis(gen), yAxis(gen)};
}

// Get the vertex array of the power-up
const sf::VertexArray &PowerUp::getVertexArray() {
    return array;
}
