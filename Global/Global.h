#ifndef POKUSAJ_GLOBAL_H
#define POKUSAJ_GLOBAL_H

class Player;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <vector>
#include <list>
#include <unordered_map>
#include <cmath>
#include "Entity.h"
#include "Player.h"
#include "Asteroid.h"
#include "PowerUp.h"
#include <fstream>
#include <iostream>

// Screen width
constexpr float SCREEN_WIDTH = 1200.0f;

// Screen height
constexpr float SCREEN_HEIGHT = 900.0f;

// Value of PI
constexpr float PI = 3.14159265f;

// Game class
class Game {
    // Time until the next asteroid spawns
    static float asteroidSpawnTime;

    // Time until the next power-up spawns
    static float powerUpSpawnTime;

    // Number of power-ups currently in the game
    static int powerUpCount;

    // High score
    static size_t highScore;

    // Font used for the text
    static sf::Font font;

    // Text object for the score
    static sf::Text scoreText;

    // Text object for the game over message
    static sf::Text gameOverText;

    // Text object for the continue message
    static sf::Text continueText;

    // Text object for the high score
    static sf::Text highScoreText;

    // Text object for the title
    static sf::Text titleText;

    // Text object for the menu
    static sf::Text menuText;

    // Text object for the play message
    static sf::Text playText;

    // Current state of the game
    static enum State { MENU, PLAYING, GAME_OVER } state;

public:
    // Initialization function for the Game class
    static void init();

    // Function to start the game
    static void begin();

    // Update function for the Game class
    static void update(sf::RenderWindow& window, float deltaTime);

    // Function to end the game
    static void gameOver();

    // List of all entities in the game
    static std::vector<Entity*> entities;

    // List of entities to be removed
    static std::list<std::vector<Entity*>::iterator> toRemoveList;

    // List of entities to be added
    static std::list<Entity*> toAddList;

    // Current score
    static size_t score;

    // Sound buffer for the shooting sound
    static sf::SoundBuffer shootSoundBuffer;

    // Sound object for the shooting sound
    static sf::Sound shootSound;

    // Function to decrease the number of power-ups
    static void decreasePowerUpCount() {
        powerUpCount--;
    }

    // Function to get the position of the player
    static sf::Vector2f getPlayerPosition();
};

#endif //POKUSAJ_GLOBAL_H