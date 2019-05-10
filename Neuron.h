#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include "math.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define learningRate 0.1
#define momentum 0.7

using namespace std;

class Neuron;

typedef vector <Neuron> Layer;

typedef struct Weights{
    double weight;
    double deltaWeight;
};

class Neuron
{
private:
    vector <Weights> w;
    Weights bias;
    double outputValue;
    double weightChangeFactor;
public:
    Neuron(int numberOfWeights, bool b);
    virtual ~Neuron();
    double sigmoidDerivative(double x);
    double sigmoid(double x);
    double feedForward(Layer &previousLayer, bool f);
    double updateWeights(Layer &previousLayer, bool b);
    double randomWeight();
    void setOutputValue(double value);
    double getOutputValue();
    void outputLayerWeights(double target);
    double sum(Layer &layer, int neuron);
    void hiddenLayerWeights(Layer &layer, int neuron);
};

#endif // NEURON_H
