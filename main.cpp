#include "Physics.h"
#include "Global.h"

int main() {
    // Create a window with a resolution of 1200x900, title "Asteroids", and with close and titlebar styles
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids",
                      sf::Style::Close | sf::Style::Titlebar);

    // Create a clock to measure time
    sf::Clock clock;

    // Initialize the game
    Game::init();

    // Main game loop
    while (window.isOpen()) {
        // Calculate the time since the last frame
        float deltaTime = clock.restart().asSeconds();

        // Event handling
        sf::Event e{};
        while (window.pollEvent(e)) {
            // If the window is closed, close the application
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window to prepare for new frame
        window.clear();

        // Update the game state
        Game::update(window, deltaTime);

        // Display the new frame
        window.display();
    }
}