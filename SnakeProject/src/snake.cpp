#include <SFML/Audio.hpp>
#include "Snake.h"

Snake::Snake(sf::RenderWindow &window, int Size1, int Speed1) : mWindow(window), Size2(Size1), Speed2(Speed1)
{
    Left = Up = Down = false;
    Right = true;
    srand(std::time(0));
    AddCase();
    AddCase();
    Food.setSize(sf::Vector2f(32, 32));
    Food.setFillColor(sf::Color::Black);
    FoodGenerator();
}

void Snake::FoodGenerator()
{
    int randomX = rand() % (mWindow.getSize().x / Size2);
    int randomY = rand() % (mWindow.getSize().y / Size2);

    for(unsigned int i = 0; i < mSnakes.size(); i++)
    {
        if((mSnakes[0].getPosition().x != randomX * Size2) && (mSnakes[0].getPosition().y != randomY))
        {
            Food.setPosition(randomX * Size2, randomY * Size2);
        }
    }
}

void Snake::AddCase()
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(32, 32));
    rect.setOutlineColor(sf::Color(156,206,156));
    rect.setOutlineThickness(3.0f);
    if (mSnakes.empty())
    {
        rect.setFillColor(sf::Color::Black);
        rect.setPosition(320, 256);
    }
    else
    {
        rect.setFillColor(sf::Color::Black);
        rect.setPosition(mSnakes[mSnakes.size() - 1].getPosition().x - rect.getSize().x, mSnakes[mSnakes.size() - 1].getPosition().y);
    }
    mSnakes.push_back(rect);
}

void Snake::Move()
{
    if (mSnakes.size() > 1)
    {
        for (unsigned int i = mSnakes.size() - 1; i > 0; i--)
        {
            mSnakes[i].setPosition(sf::Vector2f(mSnakes[i-1].getPosition().x, mSnakes[i-1].getPosition().y));
        }
    }
    if (Left)
    {
        mSnakes[0].move(-Speed2, 0);
    }
    if (Right)
    {
        mSnakes[0].move(Speed2, 0);
    }
    if (Up)
    {
        mSnakes[0].move(0, -Speed2);
    }
    if (Down)
    {
        mSnakes[0].move(0, Speed2);
    }
    CheckCollision();
}

void Snake::CheckCollision()
{
    for (unsigned int i = 2; i < mSnakes.size(); i++)
    {
        if (mSnakes[0].getPosition().x == mSnakes[i].getPosition().x
        && mSnakes[0].getPosition().y == mSnakes[i].getPosition().y)
        {

            GameOver();
            startScreen = false;
        }
    }
    if (mSnakes[0].getPosition().x < 0 || mSnakes[0].getPosition().x + mSnakes[0].getSize().x > mWindow.getSize().x
    || mSnakes[0].getPosition().y < 0 || mSnakes[0].getPosition().y + mSnakes[0].getSize().y > mWindow.getSize().y)
    {

        GameOver();
        startScreen = false;
    }
    if (mSnakes[0].getPosition().x == Food.getPosition().x
    && mSnakes[0].getPosition().y == Food.getPosition().y)
    {
        AddCase();
        FoodGenerator();
    }
}

void Snake::Update(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            Check_Move = 1;
            if(mSnakes[0].getPosition().x - mSnakes[0].getSize().x != mSnakes[1].getPosition().x)
            {
                if (Check_Move == 1)
                {
                    Left = true;
                    Right = false;
                    Up = false;
                    Down = false;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            Check_Move = 2;
            if(mSnakes[0].getPosition().x + mSnakes[0].getSize().x != mSnakes[1].getPosition().x)
            {
                if (Check_Move == 2)
                {
                    Left = false;
                    Right = true;
                    Up = false;
                    Down = false;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            Check_Move = 3;
            if(mSnakes[0].getPosition().y - mSnakes[0].getSize().x != mSnakes[1].getPosition().y)
            {
                if (Check_Move == 3)
                {
                    Left = false;
                    Right = false;
                    Up = true;
                    Down = false;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            Check_Move = 4;
            if(mSnakes[0].getPosition().y + mSnakes[0].getSize().x != mSnakes[1].getPosition().y)
            {
                if (Check_Move == 4)
                {
                    Left = false;
                    Right = false;
                    Up = false;
                    Down = true;
                }
            }
        }
    }
}

void Snake::Draw()
{
    mWindow.draw(Food);
    for (unsigned int i = 0; i < mSnakes.size(); i++)
        mWindow.draw(mSnakes[i]);
}

void Snake::GameOver()
{
    mSnakes.clear();
    Left = Up = Down = false;
    Right = true;

    sf::Texture gameOver;
    gameOver.loadFromFile("asset\\images\\snakeGameOver.png");
    sf::Sprite GAMEOver;
    GAMEOver.setTexture(gameOver);

    sf::SoundBuffer buffer1;
    buffer1.loadFromFile("asset\\sounds\\mort.wav");
    sf::Sound sound1;
    sound1.setBuffer(buffer1);
    sound1.play();

    while (startScreen == 0 )
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            startScreen = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            mWindow.close();
        }
        mWindow.clear();
        mWindow.draw(GAMEOver);
        mWindow.display();
    }
    AddCase();
    AddCase();
    FoodGenerator();
}
