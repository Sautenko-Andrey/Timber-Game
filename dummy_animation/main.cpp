#include <SFML/Graphics.hpp>
#include <memory>


enum class Coordinates {

    BackgroundXPos = 0,
    BackgroundYPos = 0,
    ScreenWidth = 1366,
    ScreenHeight = 768,
    HeroStartXPos = 50,
    HeroStartYPos = 400
};


class SpriteManager {

public:

    SpriteManager(std::string_view path_to_file, const std::pair<int,int> &coords)
    : m_path_to_file{path_to_file}, m_coords{coords}
    {
        m_texture.loadFromFile(m_path_to_file);

        m_sprite = std::make_shared<sf::Sprite>();
        m_sprite->setTexture(m_texture);
        m_sprite->setPosition(m_coords.first, m_coords.second);
    }

    std::shared_ptr<sf::Sprite> getSprite() const {
        
        return m_sprite;
    }

    void setSpriteCoords(const std::pair<float, float> &coords){
        m_sprite->setPosition(coords.first, coords.second);
    }

private:
    std::string m_path_to_file;

    std::pair<float, float> m_coords;

    sf::Texture m_texture;

    std::shared_ptr<sf::Sprite> m_sprite{nullptr};
};


class MainHero{

public:

    MainHero(float start_x, float start_y)
    : m_position{start_x, start_y}
    {
        m_texture.loadFromFile("graphics/hero.png");
        hero_sprite = std::make_shared<sf::Sprite>();
        hero_sprite->setTexture(m_texture);
        hero_sprite->setPosition(m_position);
    }


    sf::FloatRect getPosition() const {
        return hero_sprite->getGlobalBounds();
    }

    std::shared_ptr<sf::Sprite> getShape() {
        return hero_sprite;
    }

    void moveLeft() {
        m_moving_left = true;
    }

    void moveRight() {
        m_moving_right = true;
    }

    void stopLeft() {
        m_moving_left = false;
    }

    void stopRight() {
        m_moving_right = false;
    }

    void jump() {
        m_jumping = true;
    }

    void stopJump() {
        m_jumping = false;
    }

    void update(sf::Time dt){
        if(m_moving_left){
            m_position.x -= m_speed * dt.asSeconds();
        }

        if(m_moving_right){
            m_position.x += m_speed * dt.asSeconds();
        }

        if(m_jumping){
            m_position.y -= (m_speed * dt.asSeconds()) * 10;
        }

        hero_sprite->setPosition(m_position);
    }

private:

    sf::Vector2f m_position;   // hero position (x,y)

    float m_speed{300.0f};

    bool m_moving_right{false};

    bool m_moving_left{false};

    bool m_jumping{false};

    sf::Texture m_texture;

    std::shared_ptr<sf::Sprite> hero_sprite{nullptr};     // hero object

};


int main(){

    // Create a video mode object
    sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();

    // Create and open a window for the game
    sf::RenderWindow window(video_mode, "Walker", sf::Style::Fullscreen);

    // Create a texture and a sprite for the background
    SpriteManager sprite_background("graphics/background.png",
                                            std::make_pair(
                                                static_cast<int>(Coordinates::BackgroundXPos),
                                                static_cast<int>(Coordinates::BackgroundYPos)
                                            ));

    // // Create a texture and a sprite for the main hero
    // SpriteManager sprite_hero("graphics/hero.png",
    //                           std::make_pair(
    //                             static_cast<int>(Coordinates::HeroStartXPos),
    //                             static_cast<int>(Coordinates::HeroStartYPos)
    //                           ));

    // // Create a texture and a sprite for the main hero
    // SpriteManager sprite_hero_2("graphics/hero_2_2_2.png",
    //                           std::make_pair(-100, -100));

    // Create the main hero
    MainHero main_hero(
        static_cast<int>(Coordinates::HeroStartXPos),
        static_cast<int>(Coordinates::HeroStartYPos)
    );

    // Track whether the game is running
    bool paused = true;

    // Control the player input
    bool accept_input = false;

    // Hero's walking speed
    double hero_speed = 1000;

    // Clock for timing everything
    sf::Clock clock;                              

    // Game loop
    while(window.isOpen()){

        // Handle player's input
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                // Quit the game when the window is closed
                window.close();
            }
        }

        // Exit from the game when user presses Esc
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }

        // Start the game
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            paused = false;
            accept_input = true;
        }

        // Wrap the player controls to
        // Make sure we are accepting input
        // if(accept_input){
        //     // First handle pressing the right cursor key
        //     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //         // Hide first walking hero
        //         // and show up second walking hero
        //         sprite_hero.setSpriteCoords(std::make_pair(2000, 2000));

        //         sprite_hero_2.setSpriteCoords(std::make_pair(
        //             static_cast<int>(Coordinates::HeroStartXPos) + 50,
        //             static_cast<int>(Coordinates::HeroStartYPos)
        //         ));

        //         accept_input = false;
        //     }
        // }

        // Handle the pressing and releasing of the arrow keys
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            main_hero.moveLeft();
        }
        else{
            main_hero.stopLeft();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            main_hero.moveRight();
        }
        else{
            main_hero.stopRight();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            main_hero.jump();
        }
        else{
            main_hero.stopJump();
        }

        // Update main hero
        sf::Time dt = clock.restart();
        main_hero.update(dt);


        // Draw the game scene------------------------------------------------
        
        // Draw the background
        window.draw(*sprite_background.getSprite());

        // Draw the main hero
        // window.draw(*sprite_hero.getSprite());

        // // Draw the main hero 2
        // window.draw(*sprite_hero_2.getSprite());

        window.draw(*main_hero.getShape());
        
        // Show everything we jsut drew 
        window.display();

        //--------------------------------------------------------------------
    }

    
    return 0;
}