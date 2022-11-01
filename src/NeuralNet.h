#ifndef H_NEURALNET
#define H_NEURALNET

#include <vector>

class NeuralNet
{
    public:
        NeuralNet() = default;
        NeuralNet(int,int, int, int);
        float* output_array(float* vision);
        NeuralNet crossover(NeuralNet&);
        void mutate();
        NeuralNet clonate();
    
    private:
        std::vector<float**> matrixNeuron;
        int input, hidden, output, hLayers;
        float* dot(float*, float**, size_t, size_t);
        float randomNumber(float from, float to);
        void randomize();
        
};

#endif 