#include "Population.h"
#include "Snake.h"
#include <iostream>

Population::Population(int size, float SIZE, float width, float height)
{   
    srand(time(NULL));
    gen = 0;
    bestFitness = 0;
    bestSnakeScore = 0;
    for(int i = 0; i<size; i++)
    {   
        snakes.push_back(Snake(SIZE, width, height));
        snakes.at(i).brain.randomize();
    }


    bestSnake = snakes.at(0).clonate();


}

bool Population::done()
{
    for(int i = 0; i<snakes.size(); i++)
    {
        if(snakes.at(i).isAlive())
            return false;
    }

    return true;
}

void Population::show(sf::RenderWindow &window)
{
    bestSnake.show(window);
    
    for(int i = 1; i<snakes.size(); i++)
    {   
        if(snakes.at(i).isAlive())
        {
            snakes.at(i).show(window);
        }
    }
    
}

void Population::update()
{   
    if(bestSnake.isAlive())
    {
        bestSnake.think();
        bestSnake.move();
    }

    for(int i = 0; i<snakes.size(); i++)
    {   
        if(snakes.at(i).isAlive())
        {
            snakes.at(i).think();
            snakes.at(i).move();
        }
    }
}

void Population::setBestSnake()
{
    float max = 0;
    int maxI = 0;
    for(int i = 0; i<snakes.size(); i++)
    {
        if(snakes.at(i).fitness > max)
        {
            max = snakes.at(i).fitness;
            maxI = i;
        }
    }
    if(max > bestFitness)
    {
        bestFitness = max;
        bestSnake = snakes[maxI].clonate();
        bestSnakeScore = snakes[maxI].score;

    }
    else
    {
        bestSnake = bestSnake.clonate();
    }


}

void Population::naturalSelection()
{   
    setBestSnake();
    calculateFitnessSum();

    std::vector<Snake> temp;
    temp.push_back(bestSnake.clonate());
    for(int i = 1; i<snakes.size(); i++)
    {   
        Snake parent1 = selectParent();
        Snake parent2 = selectParent();
        //std::cout<<parent1.brain.output_std(parent2.brain)<<"\n";
        Snake child = parent1.crossover(parent2);
        child.brain.mutate();
        temp.push_back(child);
        
    }

    for(int i = 0; i<temp.size(); i++)
    {
        snakes.at(i) = temp.at(i);
    }
    gen ++;
}

Snake Population::selectParent()
{
    int rand_n = rand() % (int)fitnessSum;
    float sum = 0;
    for(int i = 0; i<snakes.size(); i++)
    {
        sum += snakes.at(i).fitness;
        if(sum > rand_n)
        {   
            return snakes.at(i);
        }
        
    }

    return snakes.at(0);


}



void Population::calculateFitness()
{
    for(int i = 0; i<snakes.size(); i++)
    {   
        snakes.at(i).calculateFitness();
    }
}

void Population::calculateFitnessSum()
{
    fitnessSum = 0;
    for(int i = 0; i<snakes.size(); i++)
    {
        fitnessSum += snakes.at(i).fitness; 
    }
}

//debug
void Population::output()
{   
    std::cout<<snakes.size();
    for(int i = 0; i<snakes.size(); i++)
    {
        snakes.at(i).brain.output_std();
        std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
    }
    
}

