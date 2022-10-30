#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Snake.h"


Snake::Snake(float blockSIZES, float widths, float heights)
{   

    blockSIZE = blockSIZES;
    width = widths;
    height = heights;
    int horizontalLine = width/blockSIZE;
    int verticalLine = height/blockSIZE;

    direction = new sf::Vector2f(blockSIZE, 0);

    dead = false;

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
}

void Snake::move()
{
    shiftBody();
}

void Snake::shiftBody()
{
    for(int i = snakeBody.size() - 1 ; i>0; i--)
    {
        snakeBody.at(i) = snakeBody.at(i - 1);
    }

    sf::Vector2f head = snakeBody.at(0);
    //std::cout<<direction.x<<"\n";
    snakeBody.at(0) = sf::Vector2f(head.x + direction->x, head.y + direction->y);
    //std::cout<<snakeBody.at(0).x<<"\n";

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