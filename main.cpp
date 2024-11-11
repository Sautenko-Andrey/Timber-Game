#include <SFML/Graphics.hpp>


int main(){

    // Create a video mode object
    // sf::VideoMode vm(1366, 768);
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();

    // Create and open a window for the game
    sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

    // Game loop
    while (window.isOpen()){
        // Handle player's input

        //..........code................//

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            // When user presses Esc it means he wants to quit the game
            // We close the window
            window.close();
        }


        // Update the scene
        // ...............code.................

        // Draw the scene
        //..................code ...............

        // Clear everything from the last frame window.clear()
        // ...................code...............

        // Draw our game scene here
        //....................code.....................

        // Show eberything we jsut drew window.display()
    }

    return 0;

}