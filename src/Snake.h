#ifndef H_SNAKE
#define H_SNAKE
#include <vector>
#include <SFML/Graphics.hpp>

class Snake
{
    public:
        Snake(float, float, float);
        void show(sf::RenderWindow&);
        void move();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        bool isAlive();
    
    private:
        sf::Vector2f *direction;
        sf::RectangleShape food;
        float blockSIZE, width, height;
        int score;
        bool dead;
        std::vector<sf::Vector2f> snakeBody;
    
        
        bool foodCollide(float x, float y);
        bool bodyCollide(float x, float y);
        bool wallCollide(float x, float y);
        
        void shiftBody();
        void eat();

        
};


#endif