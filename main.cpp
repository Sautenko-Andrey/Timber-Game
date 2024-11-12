#include <SFML/Graphics.hpp>


enum class Coordinates {
    BackgroundHorizontalPos = 0,
    BackgroundVerticalPos = 0,
    TreeHorizontalPos = 593,
    TreeVerticalPos = 0,
    BeeHorizontalPos = 0,
    BeeVerticalPos = 700,
    CloudHorizontalPos = 0,
    CloudVerticalPos = 0,
    ScreenWidth = 1366,
    ScreenHeight = 768
};

int main(){

    // Create a video mode object
    // sf::VideoMode vm(1366, 768);
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();

    // Create and open a window for the game
    sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

    // Create a texture to hald a graphic on the GPU
    sf::Texture texture_background;

    // Load a graphic into the texture
    texture_background.loadFromFile("graphics/background.png");

    // Create a sprite
    sf::Sprite sprite_background;

    // Attach the texture to the sprite
    sprite_background.setTexture(texture_background);

    // Set the sprite background to cover the screen
    sprite_background.setPosition(
        static_cast<int>(Coordinates::BackgroundHorizontalPos),
        static_cast<int>(Coordinates::BackgroundVerticalPos)
    );

    // Make a tree sprite
    // Create a texture to hald a graphic on the GPU
    sf::Texture texture_tree;

    // Load a graphic into the texture
    texture_tree.loadFromFile("graphics/tree.png");

    // Create a sprite for tree
    sf::Sprite sprite_tree;

    // Attach the texture to the sprite
    sprite_tree.setTexture(texture_tree);

    // Set the sprite background to cover the screen
    sprite_tree.setPosition(
        static_cast<int>(Coordinates::TreeHorizontalPos),
        static_cast<int>(Coordinates::TreeVerticalPos)
    );

    // Prepare the bee
    sf::Texture texture_bee;
    texture_bee.loadFromFile("graphics/bee.png");
    sf::Sprite sprite_bee;
    sprite_bee.setTexture(texture_bee);
    sprite_bee.setPosition(
        static_cast<int>(Coordinates::BeeHorizontalPos),
        static_cast<int>(Coordinates::BeeVerticalPos)
    );

    // Is the bee currently moving?
    bool bee_is_active = false;

    // How fast can the bee fly?
    double bee_speed = 0.0;

    // Prepare 3 clouds
    // Make 3 cloud sprites from 1 texture
    sf::Texture texture_cloud;
    texture_cloud.loadFromFile("graphics/cloud.png");

    // 3 sprites with the same texture
    sf::Sprite sprite_cloud_1;
    sf::Sprite sprite_cloud_2;
    sf::Sprite sprite_cloud_3;

    sprite_cloud_1.setTexture(texture_cloud);
    sprite_cloud_2.setTexture(texture_cloud);
    sprite_cloud_3.setTexture(texture_cloud);

    // Position the clouds on the left of the screen
    // at different heights
    sprite_cloud_1.setPosition(
        static_cast<int>(Coordinates::CloudHorizontalPos),
        static_cast<int>(Coordinates::CloudVerticalPos)
    );
    sprite_cloud_2.setPosition(
        static_cast<int>(Coordinates::CloudHorizontalPos),
        static_cast<int>(Coordinates::CloudVerticalPos) + 250
    );
    sprite_cloud_3.setPosition(
        static_cast<int>(Coordinates::CloudHorizontalPos),
        static_cast<int>(Coordinates::CloudVerticalPos) + 500
    );

    // Are the clouds currently on screen?
    bool cloud_1_is_active = false;
    bool cloud_2_is_active = false;
    bool cloud_3_is_active = false;

    // How fast is each cloud?
    double cloud_1_speed = 0.0;
    double cloud_2_speed = 0.0;
    double cloud_3_speed = 0.0;

    // Variables to control time itself
    sf::Clock clock;


    // Game loop
    while (window.isOpen()){
        // Handle player's input

        //..........code................//

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            // When user presses Esc it means he wants to quit the game
            // We close the game window
            window.close();
        }


        // Update the scene
        // Measure time
        sf::Time dt = clock.restart();

        // Setup the bee
        if (!bee_is_active){

            // How fast is the bee
            srand((int)time(0));

            // Get a random number between 200 and 399
            bee_speed = (rand() % 200) + 200;

            // How high is the bee
            srand((int)time(0) * 10);

            // Get a random number between 300 and 720 and assign height
            double height = (rand() % 300) + 420;

            // Set the position of the bee to 2000 on the x-axis
            // (just off-screen to the right) and to what-ever, height,
            // equals on the y-axis.
            sprite_bee.setPosition(-1000, height);

            // Set bee_is_active to true so this code doesn’t execute again
            // until we again change bee_is_active in the code.
            bee_is_active = true;
        }
        else{
            // When the bee is active
            // Move the bee
            sprite_bee.setPosition(
                sprite_bee.getPosition().x + (bee_speed * dt.asSeconds()),
                sprite_bee.getPosition().y
            );

            // Has the bee reached the left-hand edge of the screen?
            if(sprite_bee.getPosition().x > static_cast<int>(Coordinates::ScreenWidth)){
                // Set it up ready to be a whole new bee next frame
                bee_is_active = false;
            }
        }

        // Manage the clouds
        // Cloud 1
        if(!cloud_1_is_active){

            // How fast is the cloud
            srand((int)time(0) * 10);

            // Speed is between 0 and 199 pixels
            cloud_1_speed = (rand() % 200);

            // How high is the cloud
            srand((int)time(0) * 10);
            double height = (rand() % 150);
            sprite_cloud_1.setPosition(-200, height);
            cloud_1_is_active = true;
        }
        else{
            // when cloud is active
            // move it to the right
            sprite_cloud_1.setPosition(
                sprite_cloud_1.getPosition().x + (cloud_1_speed * dt.asSeconds()),
                sprite_cloud_1.getPosition().y
            );

            // Has the cloud reached the right hand edge of the screen?
            if(sprite_cloud_1.getPosition().x > static_cast<int>(Coordinates::ScreenWidth)){
                // Set it up ready to be a whole new cloud next frame
                cloud_1_is_active = false;
            }
        }

        // Cloud 2
        if(!cloud_2_is_active){
            // How fast is the cloud
            srand((int)time(0) * 20);

            // Speed is between 0 and 199 pixels
            cloud_2_speed = (rand() % 200);

            // How high is the cloud
            srand((int)time(0) * 20);
            double height = (rand() % 300) - 150;
            sprite_cloud_2.setPosition(-200, height);
            cloud_2_is_active = true;
        }
        else{
            // when cloud is active
            // move it to the right
            sprite_cloud_2.setPosition(
                sprite_cloud_2.getPosition().x + (cloud_2_speed * dt.asSeconds()),
                sprite_cloud_2.getPosition().y
            );

            // Has the cloud reached the right hand edge of the screen?
            if(sprite_cloud_2.getPosition().x > static_cast<int>(Coordinates::ScreenWidth)){
                // Set it up ready to be a whole new cloud next frame
                cloud_2_is_active = false;
            }
        }

        // Cloud 3
        if(!cloud_3_is_active){
            // How fast is the cloud
            srand((int)time(0) * 30);

            // Speed is between 0 and 199 pixels
            cloud_3_speed = (rand() % 200);

            // How high is the cloud
            srand((int)time(0) * 30);
            double height = (rand() % 450) - 150;
            sprite_cloud_3.setPosition(-200, height);
            cloud_3_is_active = true;
        }
        else{
            // when cloud is active
            // move it to the right
            sprite_cloud_3.setPosition(
                sprite_cloud_3.getPosition().x + (cloud_3_speed * dt.asSeconds()),
                sprite_cloud_3.getPosition().y
            );

            // Has the cloud reached the right hand edge of the screen?
            if(sprite_cloud_3.getPosition().x > static_cast<int>(Coordinates::ScreenWidth)){
                // Set it up ready to be a whole new cloud next frame
                cloud_3_is_active = false;
            }
        }

        // Draw the scene
        //..................code ...............

        // Clear everything from the last frame 
        window.clear();
        

        // Draw our game scene here
        // Draw the background
        window.draw(sprite_background);

        // Draw 3 clouds
        window.draw(sprite_cloud_1);
        window.draw(sprite_cloud_2);
        window.draw(sprite_cloud_3);

        // Draw the tree
        window.draw(sprite_tree);

        // Draw the bee
        window.draw(sprite_bee);

        // Show everything we jsut drew 
        window.display();
    }

    return 0;

}