#include "Neuron.h"

Neuron::Neuron(int numberOfWeights, bool b)
{
    for (int i = 0; i < numberOfWeights; i++)
    {
        w.push_back(Weights());
        w[i].weight=randomWeight();
        //cout << "Wagi: " <<  w[i].weight  << endl;
    }
    if (b)
        bias.weight=randomWeight();
    else bias.weight=0;
}

Neuron::~Neuron() {}

double Neuron::randomWeight()
{
    return rand()/double(RAND_MAX);
}

double Neuron::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double Neuron::sigmoidDerivative(double x)
{
    return x * (1 - x);
}

double Neuron::feedForward(Layer &previousLayer, bool f)
{
    double sum=0.0;
    for (int i=0; i<previousLayer.size(); i++)
        sum+=previousLayer[i].getOutputValue()*this->w[i].weight;
    sum+=this->bias.weight;
    if (f)
        setOutputValue(sum);
    else
        setOutputValue(sigmoid(sum));
}

void Neuron::setOutputValue(double value)
{
    outputValue=value;
}

double Neuron::getOutputValue()
{
    return outputValue;
}

void Neuron::outputLayerWeights(double target)
{
    weightChangeFactor=(outputValue-target);
}

double Neuron::sum(Layer &layer, int neuron)
{
    double sum=0.0;
    for(int i=0; i<layer.size(); i++)
    {
        sum+=layer[i].weightChangeFactor*layer[i].w[neuron].weight;
    }
    return sum;
}

void Neuron::hiddenLayerWeights(Layer &layer, int neuron)
{
    weightChangeFactor=sum(layer, neuron)*sigmoidDerivative(getOutputValue());
}

double Neuron::updateWeights(Layer &previousLayer, bool b)
{
    for(int i=0; i<previousLayer.size(); i++)
    {
        Neuron &prevNeuron = previousLayer[i];
        double oldDeltaWeight=this->w[i].deltaWeight;
        double newDeltaWeight=learningRate*prevNeuron.getOutputValue()*weightChangeFactor+momentum*oldDeltaWeight;
        this->w[i].deltaWeight=newDeltaWeight;
        this->w[i].weight -=newDeltaWeight;
    }
    if (b)
    {
        double oldDeltaWeight=this->bias.deltaWeight;
        double newDeltaWeight=learningRate*1.0*weightChangeFactor+momentum*oldDeltaWeight;
        this->bias.deltaWeight=newDeltaWeight;
        this->bias.weight -= newDeltaWeight;
    }
}
