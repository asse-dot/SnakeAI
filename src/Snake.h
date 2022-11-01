#ifndef H_SNAKE
#define H_SNAKE
#include <vector>
#include <SFML/Graphics.hpp>

#include "NeuralNet.h"

class Snake
{
    public:
        float fitness;
        int score;
        NeuralNet brain;
        Snake() = default;
        Snake(float, float, float);
        void show(sf::RenderWindow&);
        void move();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void think();
        bool isAlive();
        Snake crossover(Snake&);

        void calculateFitness();
        Snake clonate();
    
    private:
        sf::Vector2f *direction;
        sf::RectangleShape food;
        float blockSIZE, width, height;
        int lifetime;
        int lifeLeft;
        bool dead;
        std::vector<sf::Vector2f> snakeBody;

    
        
        bool foodCollide(float x, float y);
        bool bodyCollide(float x, float y);
        bool wallCollide(float x, float y);
        float* look();
        float* lookinDirection(sf::Vector2f direction);
        void shiftBody();
        void eat();


        
};


#endif