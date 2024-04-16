#include "../include.h"
#include "neuron.h"

#ifndef NEURAL_NET_NET_H
#define NEURAL_NET_NET_H


struct input {
    float x,y;
    bool mono;
    std::vector<int> rgb;
};

class net {
private:
    std::vector<std::vector<neuron>> neurons;
    std::vector<std::vector<std::vector<float>>> weights;
    std::vector<input> inputs;
    std::vector<bool> outputs;
public:
    explicit net(std::vector<int> l);
    static float activationFuction(float x);
    static float activationFuctionDerivative(float x);
    std::vector<std::vector<neuron>> getNet();
    const std::vector<std::vector<std::vector<float>>> &getWeights();
    void setNeuronValue(int layer, int neuron, float value);
    void setNeuronDestination(int layer, int neuron, float dest);
    input randomInput();
    //this is for training network
    void forwardTrain(input rand);
    //this is feeding data and getting result to draw output
    std::vector<float> forwardShow(float x, float y);
    void backProp(input rand);
    void addInput(float x, float y, int col);
    void addOutput(bool o);
    std::vector<input> getInputs();
    void setBiasNeuron(int layer, int neuron);
};


#endif //NEURAL_NET_NET_H
