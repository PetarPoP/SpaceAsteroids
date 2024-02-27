#include "Global.h"
#include "Player.h"

// Static member variables of the Game class
std::vector<Entity*> Game::entities{}; // List of all entities in the game
std::list<std::vector<Entity*>::iterator> Game::toRemoveList{}; // List of entities to be removed
std::list<Entity*> Game::toAddList{}; // List of entities to be added

sf::SoundBuffer Game::shootSoundBuffer{}; // Sound buffer for the shooting sound
sf::Sound Game::shootSound{}; // Sound object for the shooting sound

float Game::asteroidSpawnTime{}; // Time until the next asteroid spawns
float Game::powerUpSpawnTime{}; // Time until the next power-up spawns
int Game::powerUpCount{}; // Number of power-ups currently in the game
size_t Game::score{}; // Current score
size_t Game::highScore{}; // High score
Game::State Game::state{}; // Current state of the game

sf::Font Game::font{}; // Font used for the text
sf::Text Game::scoreText{}; // Text object for the score

sf::Text Game::gameOverText{}; // Text object for the game over message
sf::Text Game::continueText{}; // Text object for the continue message

sf::Text Game::highScoreText{}; // Text object for the high score
sf::Text Game::titleText{}; // Text object for the title
sf::Text Game::menuText{}; // Text object for the menu
sf::Text Game::playText{}; // Text object for the play message

// Function to create a centered text object
sf::Text createCenteredText(const std::string& string, int characterSize, const sf::Font& font) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setString(string);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

    return text;
}

// Initialization function for the Game class
void Game::init() {
    // Load the high score from a file
    std::ifstream file("C:/Users/petar/OneDrive/Documents/Programiranje2/C++/Pokusaj/res/highscore.txt", std::ios::binary | std::ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
        file.close();
    } else {
        std::cout << "Error opening file" << std::endl;
    }

    // Load the font and create the text objects
    font.loadFromFile("C:/Users/petar/OneDrive/Documents/Programiranje2/C++/Pokusaj/res/Arial.ttf");
    scoreText = createCenteredText("Score: " + std::to_string(score), 30, font);
    scoreText.setPosition(65.0f, 23.0f); // Keep the score text in the top left corner

    gameOverText = createCenteredText("GAME OVER", 100, font);
    continueText = createCenteredText("Press Enter to continue", 30, font);
    continueText.move(0, 70.0f); // Move the continue text down a bit

    menuText = createCenteredText("Press Esc to return to menu", 30, font);
    menuText.move(0, 105.0f); // Move the menu text down a bit

    highScoreText = createCenteredText("High Score: " + std::to_string(highScore), 30, font);
    highScoreText.move(0, 60.0f); // Move the high score text down a bit

    titleText = createCenteredText("ASTEROIDS", 70, font);
    titleText.move(0, -30.0f); // Move the title text up a bit

    playText = createCenteredText("Press Enter to play", 30, font);
    playText.move(0, 25.0f); // Move the play text down a bit

    // Load the shooting sound
    shootSoundBuffer.loadFromFile("C:/Users/petar/OneDrive/Documents/Programiranje2/C++/Pokusaj/res/shoot2.wav");
    shootSound.setBuffer(shootSoundBuffer);

    // Set the initial state to MENU
    state = MENU;
}

// Function to start the game
void Game::begin() {
    state = PLAYING;
    entities.push_back(new Player());
    asteroidSpawnTime = ASTEROID_SPAWN_TIME;
    powerUpSpawnTime = POWERUP_SPAWN_TIME;
    score = 0;
}

// Update function for the Game class
void Game::update(sf::RenderWindow &window, float deltaTime) {
    // If the game is in the MENU state, draw the menu and wait for the player to start the game
    if (state == MENU) {
        window.draw(highScoreText);
        window.draw(titleText);
        window.draw(playText);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            begin();
        }

        return;
    }

    // Clear the lists of entities to add and remove
    toAddList.clear();
    toRemoveList.clear();

    // Decrease the spawn timers
    asteroidSpawnTime -= deltaTime;
    if (powerUpCount == 2) {
        powerUpSpawnTime = POWERUP_SPAWN_TIME;
    }
    powerUpSpawnTime -= deltaTime;

    // Update and render all entities
    for (auto & entitie : entities) {
        entitie->update(deltaTime);
        entitie->render(window);
    }

    // Remove entities that need to be removed
    for (auto & it : toRemoveList) {
        delete *it;
        entities.erase(it);
    }

    // Add entities that need to be added
    for (const auto& it : toAddList) {
        entities.push_back(it);
    }

    // Spawn a new asteroid if it's time
    if (asteroidSpawnTime <= 0.0f) {
        asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        entities.push_back(new Asteroid(Asteroid::getRandomDirection()));
    }

    // Spawn a new power-up if it's time and there are less than the maximum number of power-ups on screen
    if (powerUpSpawnTime <= 0.0f && powerUpCount < POWERUP_ON_SCREEN) {
        powerUpSpawnTime = POWERUP_SPAWN_TIME;
        ++powerUpCount;
        entities.push_back(new PowerUp(PowerUp::getRandomDirection(), PowerUp::getRandomPosition()));
    }

    // Update the score text and draw it
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    // If the game is over, clear the entities and draw the game over screen
    if (state == GAME_OVER) {
        entities.clear();
        window.draw(gameOverText);
        window.draw(continueText);
        window.draw(menuText);

        // If the player presses Enter, restart the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            score = 0;
            begin();
        }

        // If the player presses Escape, return to the menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            state = MENU;
        }
    }
}

// Function to end the game
void Game::gameOver() {
    // If the score is higher than the high score, update the high score and save it to a file
    if (score > highScore) {
        highScore = score;
        std::ofstream file("res/highscore.txt", std::ios::binary | std::ios::out);
        if (file.is_open()) {
            file.write(reinterpret_cast<char*>(&highScore), sizeof(size_t));
            file.close();
        } else {
            std::cout << "Error opening file" << std::endl;
        }

        highScoreText.setString("High Score: " + std::to_string(highScore));
    }

    // Set the state to GAME_OVER
    state = GAME_OVER;
}

// Function to get the position of the player
sf::Vector2f Game::getPlayerPosition() {
    // Search for the player in the list of entities
    for (const auto& entity : entities) {
        if (auto* player = dynamic_cast<Player*>(entity)) {
            return player->getPlayerPosition();
        }
    }
    return {0, 0};  // Default position if no player is found
}