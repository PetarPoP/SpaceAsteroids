#include "Asteroid.h"

// Constructor for the Asteroid class
Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position, int size)
        : Entity(position, 0), direction(direction), array(sf::LineStrip, 9), life(0.0f), hitCount(ASTEROID_HIT_POINT), size(size) {
    // Define the shape of the asteroid
    // Multiply by 2.0f to scale the asteroid size
    array[0].position = sf::Vector2f(-30, 30) * 2.0f;
    array[1].position = sf::Vector2f(-15, -30) * 2.0f;
    array[2].position = sf::Vector2f(0, -30) * 2.0f;
    array[3].position = sf::Vector2f(15, -30) * 2.0f;
    array[4].position = sf::Vector2f(30, 0) * 2.0f;
    array[5].position = sf::Vector2f(15, 30) * 2.0f;
    array[6].position = sf::Vector2f(0, 30) * 2.0f;
    array[7].position = sf::Vector2f(-15, 30) * 2.0f;
    array[8].position = array[0].position; // Close the shape

    // Set the color of the asteroid to white
    for (size_t i = 0; i < array.getVertexCount(); ++i) {
        array[i].color = sf::Color::White;
    }
}

// Update the state of the asteroid
void Asteroid::update(float deltaTime) {
    // Increase the lifetime of the asteroid
    life += deltaTime;

    // Update the position and angle of the asteroid
    position += direction * ASTEROID_SPEED * deltaTime;
    angle += ASTEROID_SPIN * deltaTime;

    // Check if the asteroid hits the screen boundaries and change its direction if it does
    if (position.x < ASTEROID_W / 2.0f) {
        direction.x = std::abs(direction.x);
    } else if (position.x > SCREEN_WIDTH - (ASTEROID_W / 2.0f)) {
        direction.x = -std::abs(direction.x);
    }

    if (position.y < ASTEROID_H / 2.0f) {
        direction.y = std::abs(direction.y);
    } else if (position.y > SCREEN_HEIGHT - (ASTEROID_H / 2.0f)) {
        direction.y = -std::abs(direction.y);
    }
}

// Render the asteroid on the window
void Asteroid::render(sf::RenderWindow& window) {
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}

// Getter for the vertex array
const sf::VertexArray& Asteroid::getVertexArray() const {
    return array;
}

// Generate a random direction for the asteroid
sf::Vector2f Asteroid::getRandomDirection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 2.0f * PI);

    float angle = dis(gen);
    return {std::cos(angle), std::sin(angle)};
}

// Calculate the distance between two points
float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

// Generate a random position for the asteroid
sf::Vector2f Asteroid::getRandomPosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);
    std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);

    sf::Vector2f randomPosition;
    // Ensure the asteroid spawns at a safe distance from the player
    do {
        randomPosition = {xAxis(gen), yAxis(gen)};
    } while (distance(randomPosition, Game::getPlayerPosition()) < SAFE_DISTANCE);

    return randomPosition;
}