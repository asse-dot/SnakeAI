#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Snake.h"


Snake::Snake(float blockSIZE_, float width_, float height_)
{   
    srand(time(NULL));
    blockSIZE = blockSIZE_;
    width = width_;
    height = height_;
    int horizontalLine = width/blockSIZE;
    int verticalLine = height/blockSIZE;

    direction = new sf::Vector2f(blockSIZE, 0);

    dead = false;

    food.setSize(sf::Vector2f(blockSIZE, blockSIZE));
    food.setFillColor(sf::Color::Red);
    food.setOutlineColor(sf::Color::White);

    food.setPosition(rand() % (int)(width/blockSIZE) * blockSIZE, (rand() % (int)(height/blockSIZE)) * blockSIZE);
    this->snakeBody.push_back(sf::Vector2f(horizontalLine/2 * blockSIZE,  verticalLine/2 * blockSIZE));
}

void Snake::show(sf::RenderWindow& window)
{   
    sf::RectangleShape blockSnake;
    blockSnake.setSize(sf::Vector2f(blockSIZE, blockSIZE));
    blockSnake.setFillColor(sf::Color::Green);
    blockSnake.setOutlineColor(sf::Color::White);

    for(std::vector<sf::Vector2f>::iterator it = snakeBody.begin(); it != snakeBody.end(); ++it)
    {  
        blockSnake.setPosition(*it);
        window.draw(blockSnake);
    }

    window.draw(food);
}

void Snake::move()
{   
   
    if(foodCollide(snakeBody.at(0).x, snakeBody.at(0).y))
        eat();

    shiftBody();
    
    if(wallCollide(snakeBody.at(0).x, snakeBody.at(0).y))
        dead = 1;
    else if(bodyCollide(snakeBody.at(0).x, snakeBody.at(0).y))
        dead = 1;
    
}

void Snake::eat()
{   
    srand(time(NULL));
    food.setPosition((rand() % (int)(width/blockSIZE)) * blockSIZE, (rand() % (int)(height/blockSIZE)) * blockSIZE);
    snakeBody.push_back(sf::Vector2f(0, 0));
    score++;
}

bool Snake::foodCollide(float x, float y)
{
    return x == food.getPosition().x && y == food.getPosition().y;
}

bool Snake::wallCollide(float x, float y)
{
    return x < 0 || x > width - blockSIZE || y > height - blockSIZE || y < 0;
}

bool Snake::bodyCollide(float x, float y)
{
    for(int i = 1; i<snakeBody.size(); i++)
    {
        if(x == snakeBody.at(i).x && y == snakeBody.at(i).y)
        {   
            return 1; 
        }
            
    }

    return 0;
}

void Snake::shiftBody()
{
    for(int i = snakeBody.size() - 1 ; i>0; i--)
    {
        snakeBody.at(i) = snakeBody.at(i - 1);
    }

    sf::Vector2f head = snakeBody.at(0);
    snakeBody.at(0) = sf::Vector2f(head.x + direction->x, head.y + direction->y);
}

void Snake::moveUp()
{   
    if(direction->y != blockSIZE)
        direction = new sf::Vector2f(0, -blockSIZE);
}

void Snake::moveDown()
{
    if(direction->y != -blockSIZE)
        direction = new sf::Vector2f(0, blockSIZE);
}

void Snake::moveLeft()
{
    if(direction->x != blockSIZE)
        direction = new sf::Vector2f(-blockSIZE, 0);
}

void Snake::moveRight()
{
    if(direction->x != -blockSIZE)
        direction = new sf::Vector2f(blockSIZE, 0);
}

bool Snake::isAlive()
{
    return !dead;
}