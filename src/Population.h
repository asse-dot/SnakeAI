#ifndef H_POPULATION
#define H_POPULATION

#include <vector>
#include "Snake.h"

class Population
{
    public:
        Population(int, float, float, float);

        bool done();
        void update();
        void show(sf::RenderWindow &window);
        void naturalSelection();
        void calculateFitness();

    private:
        Snake bestSnake;
        std::vector<Snake> snakes;
        int size;
        int gen;
        float bestFitness;
        float bestSnakeScore;
        float fitnessSum;
        void calculateFitnessSum();
        void setBestSnake();
        Snake selectParent();


};

#endif 