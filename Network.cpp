#include "Network.h"

Network::Network(vector <int> &topology, bool bias)
{
    int numberOfLayers = topology.size();
    for (int layerNum = 0; layerNum < numberOfLayers; layerNum++)
    {
        int numberOfWeights;
        if(layerNum==0)
        {
            numberOfWeights=0;
        }
        else numberOfWeights=topology[layerNum-1];

        layers.push_back(Layer());

        for(int neuronNum=0; neuronNum < topology[layerNum]; neuronNum++)
        {
            layers.back().push_back(Neuron(numberOfWeights, bias));
            //cout << "Stworzono neuron na warstwie " << layerNum << endl;
        }
    }
}

Network::~Network() {}

void Network::feed(vector <double> &input)
{
    for (int neuron=0; neuron<input.size(); neuron++)
    {
        layers[0][neuron].setOutputValue(input[neuron]);
    }
    for (int layer=1; layer<layers.size(); layer++)
    {
        Layer &currLayer = layers[layer];
        Layer &previousLayer = layers[layer-1];
        for (int neuron=0; neuron < currLayer.size(); neuron++)
        {
            if (layer == layers.size()-1)
                currLayer[neuron].feedForward(previousLayer, true);
            else currLayer[neuron].feedForward(previousLayer, false);
        }
    }
}

void Network::backPropagation(vector <double> &target, bool b)
{
    Layer &outputLayer=layers.back();
    Layer &hiddenLayer=layers[1];
    net_error=0.0;
    for(int i=0; i<outputLayer.size(); i++)
    {
        double delta=target[i]-outputLayer[i].getOutputValue();
        net_error+=(delta*delta)/2.0;
    }

    for(int i=0; i<outputLayer.size(); i++)
    {
        outputLayer[i].outputLayerWeights(target[i]);
    }

    for(int i=0; i<hiddenLayer.size(); i++)
    {
        hiddenLayer[i].hiddenLayerWeights(outputLayer, i);
    }

    for(int layerNum = layers.size()-1; layerNum > 0; layerNum--)
    {
        Layer &currLayer=layers[layerNum];
        Layer &previousLayer=layers[layerNum-1];

        for(int n=0; n<currLayer.size(); n++)
        {
            currLayer[n].updateWeights(previousLayer, b);
        }
    }

}

void Network::getResults(vector<double> &resultValues)
{
    for(int i=0; i<layers.back().size(); i++)
    {
        resultValues.push_back(layers.back()[i].getOutputValue());
    }
}

double Network::getError()
{
    return net_error;
}
