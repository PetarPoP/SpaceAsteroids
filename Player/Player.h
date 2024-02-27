#ifndef POKUSAJ_PLAYER_H
#define POKUSAJ_PLAYER_H

#include "Bullet.h"
#include "Global.h"
#include <SFML/Audio.hpp>
#include "PowerUp.h"
#include <deque>

constexpr float PLAYER_W = 50.0f; // Width of the player's spaceship
constexpr float PLAYER_H = 40.0f; // Height of the player's spaceship
constexpr float TURN_SPEED = 200.0f; // Speed at which the player's spaceship turns
constexpr float PLAYER_SPEED = 200.0f; // Speed at which the player's spaceship moves
constexpr float SHOOT_DELAY = 0.3f; // Delay between each shot fired by the player's spaceship

class Player : public Entity {
    sf::VertexArray array; // Array of vertices to draw the player's spaceship

    sf::Texture texture; // Texture for the player's spaceship
    sf::Sprite sprite; // Sprite for the player's spaceship

    float powerUpTimer_Speed; // Timer for the speed power-up
    float speedBoost; // Speed boost multiplier when the speed power-up is active

    float powerUpTimer_FastShoot; // Timer for the fast shooting power-up
    float fastShoot; // Shooting speed multiplier when the fast shooting power-up is active

    float powerUpTimer_Shield; // Timer for the shield power-up
    bool shield; // Boolean to check if the shield power-up is active

    float shootTimer; // Timer to control the shooting delay
public:
    Player(); // Constructor for the Player class

    void update(float deltaTime) override; // Update function to update the player's state

    void render(sf::RenderWindow& window) override; // Render function to draw the player on the window

    std::deque<sf::Vector2f> trail; // Deque to store the trail of the player's spaceship

    const sf::VertexArray& getShape() const { // Getter function to get the shape of the player's spaceship
        return array;
    }
    sf::Vector2f getPlayerPosition()  { // Getter function to get the position of the player's spaceship
        return position;
    }
};

#endif //POKUSAJ_PLAYER_H