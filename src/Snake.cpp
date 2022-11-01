#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Snake.h"
#include "NeuralNet.h"


Snake::Snake(float blockSIZE_, float width_, float height_)
{   
    srand(time(NULL));
    blockSIZE = blockSIZE_;
    width = width_;
    height = height_;
    int horizontalLine = width/blockSIZE;
    int verticalLine = height/blockSIZE;
    lifetime = 0;
    lifeLeft = 500;

    direction = new sf::Vector2f(blockSIZE, 0);

    brain = NeuralNet(24, 4, 16, 2);

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
   
    lifeLeft --;
    lifetime ++;

    if(foodCollide(snakeBody.at(0).x, snakeBody.at(0).y))
        eat();

    shiftBody();
    
    if(wallCollide(snakeBody.at(0).x, snakeBody.at(0).y))
        dead = 1;
    else if(bodyCollide(snakeBody.at(0).x, snakeBody.at(0).y))
        dead = 1;
    else if(lifeLeft == 0)
        dead = 1;
    
}

void Snake::eat()
{   
    food.setPosition((rand() % (int)(width/blockSIZE)) * blockSIZE, (rand() % (int)(height/blockSIZE)) * blockSIZE);
    snakeBody.push_back(sf::Vector2f(0, 0));
    score++;
    lifeLeft += 100;
}

bool Snake::foodCollide(float x, float y)
{
    return x == food.getPosition().x && y == food.getPosition().y;
}

bool Snake::wallCollide(float x, float y)
{
    return x < blockSIZE || x >= width - blockSIZE || y >= height - blockSIZE || y < blockSIZE;
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

void Snake::think()
{   
    float* vision = look();
   

    float* decision = brain.output_array(vision);
    
    std::cout<<decision[0]<<"\n";
    std::cout<<decision[1]<<"\n";
    std::cout<<decision[2]<<"\n";
    std::cout<<decision[3]<<"\n";
    std::cout<<"\n\n\n\n";
    
    
    float max = 0;
    int maxI = 0;
    for(int i = 0; i<4; i++)
    {
        if(decision[i] > max)
        {
            max = decision[i];
            maxI = i;
        }
    }
    switch(maxI)
    {
        case 0:
            moveUp();
            break;
        case 1:
            moveDown();
            break;
        case 2:
            moveLeft();
            break;
        case 3:
            moveRight();
            break;
    }     
}

float* Snake::look()
{
    float* look = new float[24]; 

    float* temp;
    temp = lookinDirection(sf::Vector2f(-blockSIZE, 0));
    look[0] = temp[0];
    look[1] = temp[1];
    look[2] = temp[2];
    temp = lookinDirection(sf::Vector2f(-blockSIZE, -blockSIZE));
    look[3] = temp[0];
    look[4] = temp[1];
    look[5] = temp[2];
    temp = lookinDirection(sf::Vector2f(0, -blockSIZE));
    look[6] = temp[0];
    look[7] = temp[1];
    look[8] = temp[2];
    temp = lookinDirection(sf::Vector2f(blockSIZE, -blockSIZE));
    look[9] = temp[0];
    look[10] = temp[1];
    look[11] = temp[2];
    temp = lookinDirection(sf::Vector2f(blockSIZE, 0));
    look[12] = temp[0];
    look[13] = temp[1];
    look[14] = temp[2];
    temp = lookinDirection(sf::Vector2f(blockSIZE, blockSIZE));
    look[15] = temp[0];
    look[16] = temp[1];
    look[17] = temp[2];
    temp = lookinDirection(sf::Vector2f(0, blockSIZE));
    look[18] = temp[0];
    look[19] = temp[1];
    look[20] = temp[2];
    temp = lookinDirection(sf::Vector2f(-blockSIZE, blockSIZE));
    look[21] = temp[0];
    look[22] = temp[1];
    look[23] = temp[2];

    return look;
  

}

float* Snake::lookinDirection(sf::Vector2f direction)
{
    float* look = new float[3];
    float distance = 0;
    bool foundFood = false;
    bool foundBody = false;

    sf::Vector2f pos(snakeBody.at(0).x, snakeBody.at(0).y);
    pos.x += direction.x;
    pos.y += direction.y;
    distance += 1;
    while(!wallCollide(pos.x, pos.y))
    {
        if(foodCollide(pos.x, pos.y) && !foundFood)
        {   
            foundFood = true;
            look[0] = 1;
        }

        if(bodyCollide(pos.x, pos.y) && !foundBody)
        {   
            foundBody = true;
            look[1] = 1;
        }
        pos.x += direction.x;
        pos.y += direction.y;
        distance += 1;
    }
    if(!foundBody)
    {
        look[1] = 0;
    }
    
    if(!foundFood)
    {
        look[0] = 0;
    }

    look[2] = 1/distance;
    return look;

}

Snake Snake::clonate()
{
    Snake clone = Snake(blockSIZE, width, height);
    //clone.brain = brain.clonate();
    clone.brain = this->brain;
    return clone;
}


Snake Snake::crossover(Snake& other)
{
    Snake child(blockSIZE, width, height);
    child.brain = brain.crossover(other.brain);
    return child;
}

void Snake::calculateFitness()
{
    if(score < 10)
    {
        fitness = floor(lifetime * lifetime) * pow(2, score);
    }
    else
    {
        fitness = floor(lifetime * lifetime);
        fitness *= pow(2, 10);
        fitness *= (score - 9);
    }
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