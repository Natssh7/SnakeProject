#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"

int restartgame = 1;

int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(1024, 720), "SFML window");
    window.setFramerateLimit(16);
    window.setKeyRepeatEnabled(false);
    Snake snake(window, 32, 32);
    bool startScreen = false;

    sf::Texture textureMainMenu;
    textureMainMenu.loadFromFile("asset\\images\\MenuSnake.png");
    sf::Sprite MainMenu;
    MainMenu.setTexture(textureMainMenu);

    sf::Texture nokia;
    nokia.loadFromFile("asset\\images\\overlay.png");
    sf::Sprite Overlay;
    Overlay.setTexture(nokia);

    sf::Music music;
    music.openFromFile("asset\\music\\8bitMusic.ogg");
    music.play();
    music.setLoop(true);
    music.setVolume(35);

    while (restartgame == 1)
    {
        while (window.isOpen())
        {
            sf::Event event;

            // Start Screen Game
            while(startScreen == false)
            {
                window.clear();
                window.draw(MainMenu);
                window.display();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))    //H = Hard
                {
                    window.setFramerateLimit(25);
                    startScreen = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))    //L = Low
                {
                    window.setFramerateLimit(12);
                    startScreen = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))    //M = Medium
                {
                    startScreen = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    window.close();
                }
            }

            snake.Move();

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    window.close();
                }

                snake.Update(event);
            }

            window.clear(sf::Color(156,206,156));
            snake.Draw();
            window.draw(Overlay);
            window.display();
        }
    }
    return EXIT_SUCCESS;
}


