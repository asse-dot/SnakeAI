#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <time.h>


#include "Snake.h"
#include "Population.h"


float SIZE = 30;
float vx = 1280;
float vy = 600;
int horizontalLine = vx / SIZE;
int verticalLine = vy / SIZE;

//DEBUG PLAYING AI OR HUMAN
bool humanPlaying =0;


int main()
{   
    //std::ios_base::sync_with_stdio(false);
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(vx, vy), "Snake AI");
    sf::RectangleShape block;

    sf::Clock clock;
    float chrono = 0;
    float delay = 0.1;

    block.setSize(sf::Vector2f(SIZE, SIZE));
    block.setFillColor(sf::Color::Black);
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::White);

    Snake snake(SIZE, vx, vy);
    Population pop(500, SIZE, vx, vy);


    while(window.isOpen())
    {   
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        chrono += time;

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {   
                window.close();
            }
        
        }

        if(!snake.isAlive() && humanPlaying)
        {   
            snake = Snake(SIZE, vx, vy);
        }

        if(humanPlaying)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                snake.moveLeft();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                snake.moveRight();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                snake.moveUp();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                snake.moveDown();
        }

        if(chrono > delay && humanPlaying)
        {
            chrono = 0;
            snake.move();
        }
        window.clear();
        for(int i = 0; i < verticalLine; i++)
        {
            for(int j = 0; j < horizontalLine; j++)
            {
                block.setPosition(j * SIZE, i * SIZE);
                window.draw(block);
            }
        }
    
        if(humanPlaying)
        {
            snake.show(window);
        }
        else
        {   

            if(!pop.done())
            {   
                pop.update();
                pop.show(window);
            }
            else
            {   
                pop.calculateFitness();
                pop.naturalSelection();
            }
        
        }
        window.display();
        
    }

    return 0;
}