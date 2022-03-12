#include <SFML/Graphics.hpp>

#include "cfg/config.hpp"
#include "src/map.cpp"

int main()
{
    bool isPaused = false;
    // create the window
    sf::RenderWindow window(sf::VideoMode(CONFIG_WINDOW_WIDTH, CONFIG_WINDOW_HEIGHT), "Game of Life");
    window.setFramerateLimit(CONFIG_WINDOW_FPS_LIMIT);

    Map map;

    window.clear(sf::Color::Black);
    window.draw(map);
    window.display();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                isPaused = !isPaused;
        }
        if (!isPaused) {
            // clear the window with black color
            window.clear(sf::Color::Black);

            // draw everything here...
            window.draw(map);
            map.update();

            // end the current frame
            window.display();
        }
    }

    return 0;
}