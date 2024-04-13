#include "../include.h"
#include "neuron.h"

#ifndef NEURAL_NET_NET_H
#define NEURAL_NET_NET_H


class net {
private:
    std::vector<std::vector<neuron>> neurons;
    std::vector<std::vector<std::vector<float>>> weights;
public:
    explicit net(std::vector<int> l);
    static float activationFuction(float x);
    static float activationFuctionDerivative(float x);
    std::vector<std::vector<neuron>> getNet();
    const std::vector<std::vector<std::vector<float>>> &getWeights();
    void setNeuronValue(int layer, int neuron, float value);
    void setNeuronDestination(int layer, int neuron, float dest);
    void calculateWeights();
};


#endif //NEURAL_NET_NET_H
