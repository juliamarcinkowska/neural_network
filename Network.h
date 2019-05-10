#ifndef NETWORK_H
#define NETWORK_H

#include "Neuron.h"
#include <iostream>

using namespace std;

class Network
{
private:
    vector <Layer> layers;
public:
    Network(vector <int> &topology, bool bias);
    virtual ~Network();
    void feed(vector <double> &input);
    void backPropagation(vector <double> &target, bool b);
    void getResults(vector<double> &resultValues);
    double getError();
    double net_error;
};

#endif // NETWORK_H
