#include <iostream>
#include  <math.h>
#include <cmath>
#include <random>
#include "NeuralNet.h"


NeuralNet::NeuralNet(int input_,int output_, int hidden_, int hLayers_)
{
    input = input_;
    output = output_;
    hidden = hidden_;
    hLayers = hLayers_;
    
    float **temp_hidden = new float *[hidden];
    for(int i = 0; i<hidden; i++)
    {
        temp_hidden[i] = new float[input];
    } 
    matrixNeuron = std::vector<float**>(hLayers + 1);
    matrixNeuron[0] = temp_hidden;

    temp_hidden = new float *[output];
    for(int i = 0; i<output; i++)
    {
        temp_hidden[i] = new float[hidden];
    }
    matrixNeuron[matrixNeuron.size() - 1] =  temp_hidden;
    for(int i = 1; i<hLayers; i++)
    {   
        float **hidden_m = new float *[hidden];
        for(int i = 0; i<hidden; i++)
        {
            hidden_m[i] = new float[hidden];
        }
        matrixNeuron[i] = hidden_m;
    }   
    

}

float* NeuralNet::dot(float* m1, float** m2, size_t size_m2, size_t size_n2)
{
    float* result = new float[size_m2];
    for(int i = 0; i<size_m2; i++) //PER OGNI RIGA DELLA MATRICE M2
    {   
        float summ = 0;
        for(int j = 0; j<size_n2; j++) //COLONNA M2 E COLONNA M1
        {   
           summ += m1[j] * m2[i][j];
        }
        result[i] = summ > 0 ? summ : 0;
    }
    return result;
}

NeuralNet NeuralNet::clonate()
{   
    NeuralNet clone = NeuralNet(input, output, hidden, hLayers);
    for(int i = 0; i<hidden; i++)
    {
        for(int j = 0; j<input; j++)
        {
            clone.matrixNeuron[0][i][j] = matrixNeuron[0][i][j];
        }
    }

    for(int i = 0; i<output; i++)
    {
        for(int j = 0; j<hidden; j++)
        {
            clone.matrixNeuron[matrixNeuron.size()-1][i][j] = matrixNeuron[matrixNeuron.size() - 1][i][j];
        }
    }
    for(int k = 1; k<hLayers; k++)
    {   
        for(int i = 0; i<hidden; i++)
        {
            for(int j = 0; j<hidden; j++)
            {
                clone.matrixNeuron[k][i][j] = matrixNeuron[k][i][j];
            }
        }
    }

    return clone;
}

float NeuralNet::randomNumber(float a, float b)
{   
    //float c =  a + static_cast <float> (random()) /( static_cast <float> (RAND_MAX/(b-a)));
    return a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b-a)));
}

void NeuralNet::randomize()
{
    for(int i = 0; i<hidden; i++)
    {
        for(int j = 0; j<input; j++)
        {
            matrixNeuron[0][i][j] = randomNumber(-1 , 1);
        }
    }

    for(int i = 0; i<output; i++)
    {
        for(int j = 0; j<hidden; j++)
        {
            matrixNeuron[matrixNeuron.size()-1][i][j] = randomNumber(-1, 1);
        }
    }
    for(int k = 1; k<hLayers; k++)
    {   
        for(int i = 0; i<hidden; i++)
        {
            for(int j = 0; j<hidden; j++)
            {
                matrixNeuron[k][i][j] = randomNumber(-1, 1);
            }
        }
    }
}


float* NeuralNet::output_array(float* vision)
{   
    float* output_arr;
    output_arr = dot(vision, matrixNeuron.at(0), hidden, input);
    for(int i = 1; i<hLayers; i++)
    {
        output_arr = dot(output_arr, matrixNeuron.at(i), hidden, hidden);
    }

    output_arr = dot(output_arr, matrixNeuron.at(matrixNeuron.size() - 1), output, hidden);
    return output_arr;
}

NeuralNet NeuralNet::crossover(NeuralNet& other)
{   
    int randC, randR;
    NeuralNet child(input, output, hidden, hLayers);
    randC = rand() % input;
    randR = rand() % hidden;
    for(int i = 0; i<hidden; i++)
    {
        for(int j = 0; j<input; j++)
        {
            if((i < randR || (i == randR && j <= randC)))
            {
                child.matrixNeuron[0][i][j] = this->matrixNeuron[0][i][j];
            }
            else
            {   
                child.matrixNeuron[0][i][j] = other.matrixNeuron[0][i][j];
            }
        }
    }
    randC = rand() % hidden;
    randR = rand() % output;
    for(int i = 0; i<output; i++)
    {
        for(int j = 0; j<hidden; j++)
        {   
            if((i < randR || (i == randR && j <= randC)))
            {      
                child.matrixNeuron[matrixNeuron.size() - 1][i][j] = this->matrixNeuron[matrixNeuron.size() - 1][i][j];
            }
            else
            {
                child.matrixNeuron[matrixNeuron.size() - 1][i][j] = other.matrixNeuron[matrixNeuron.size() - 1][i][j];
            }
        }
    }
    for(int k = 1; k<hLayers; k++)
    {   
        randC = rand() % hidden;
        randR = rand() % hidden;
        for(int i = 0; i<hidden; i++)
        {
            for(int j = 0; j<hidden; j++)
            {   
                if((i <randR) || (i == randR && j <= randC))
                {
                    child.matrixNeuron[k][i][j] = this->matrixNeuron[k][i][j];
                }
                else
                {
                    child.matrixNeuron[k][i][j] = other.matrixNeuron[k][i][j];
                }
            }
        }
    }

    return child;
}

void NeuralNet::mutate()
{
    /*
    float rand = randomNumber(0, 1);
                if(rand > 0.5)
                    continue;
    */
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.5, 0.5);
    for(int i = 0; i<hidden; i++)
    {
        for(int j = 0; j<input; j++)
        {   
            float rand = randomNumber(0, 1);
            if(rand> 0.02)
            {
                continue;
            }
            matrixNeuron[0][i][j] += distribution(generator)/5;

            if(matrixNeuron[0][i][j] > 1)
                matrixNeuron[0][i][j] = 1;
            
            if(matrixNeuron[0][i][j] < -1)
                matrixNeuron[0][i][j] = -1;
        }
    }

    for(int i = 0; i<output; i++)
    {
        for(int j = 0; j<hidden; j++)
        {   
            float rand = randomNumber(0, 1);
            if(rand >0.02)
            {
                continue;
            }
                
            matrixNeuron[matrixNeuron.size()-1][i][j] += distribution(generator) / 5;

            if(matrixNeuron[matrixNeuron.size() - 1][i][j] > 1)
                matrixNeuron[matrixNeuron.size() - 1][i][j] = 1;

            if(matrixNeuron[matrixNeuron.size() - 1][i][j] < -1)
                matrixNeuron[matrixNeuron.size() - 1][i][j] = -1;
        }
    }
    for(int k = 1; k<hLayers; k++)
    {   
        for(int i = 0; i<hidden; i++)
        {
            for(int j = 0; j<hidden; j++)
            {   
                float rand = randomNumber(0, 1);
                if(rand > 0.02)
                {
                    continue;
                }
                matrixNeuron[k][i][j] += distribution(generator)/ 5;
                if(matrixNeuron[k][i][j] > 1)
                    matrixNeuron[k][i][j] = 1;

                if(matrixNeuron[k][i][j] < -1)
                    matrixNeuron[k][i][j] = -1;
            }
        }
    }
}

//debug
void NeuralNet::output_std()
{
    for(int i = 0; i<hidden; i++)
    {
        for(int j = 0; j<input; j++)
        {
            std::cout<<matrixNeuron[0][i][j]<<" ";
            
        }
        std::cout<<"\n";
    }

    for(int i = 0; i<output; i++)
    {
        for(int j = 0; j<hidden; j++)
        {
            std::cout<<matrixNeuron[matrixNeuron.size() - 1][i][j]<<" ";
        }
        std::cout<<"\n";
    }
    for(int k = 1; k<hLayers; k++)
    {   
        for(int i = 0; i<hidden; i++)
        {
            for(int j = 0; j<hidden; j++)
            {
                std::cout<<matrixNeuron[k][i][j]<<" ";
            }
            std::cout<<"\n";
        }
    }
}