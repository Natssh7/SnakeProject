#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Snake
{
    public:
        Snake(sf::RenderWindow &window, int Size1, int Speed1);

        void Move();
        void Update(sf::Event &event);
        void Draw();
        void GameOver();
        int restartgame = 1;
        bool startScreen = false;


    private:
        sf::RenderWindow &mWindow;
        sf::RectangleShape Food;
        int Check_Move;
        int TimeToUpdate;
        int Size2;
        int Speed2;
        bool Left, Right, Up, Down;
        float CurrentTime;
        std::vector<sf::RectangleShape> mSnakes;

        void CheckCollision();
        void AddCase();
        void FoodGenerator();
};

#endif // SNAKE_H_INCLUDED
