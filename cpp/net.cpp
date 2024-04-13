
#include <cmath>

#include "../header/net.h"

net::net(std::vector<int> l) {
    unsigned int size = l.size();
    int xpos = WIN*4/3/(size+1);

    for(int i=0;i<size;i++) {
        int ypos = WIN/(l[i]+1);
        std::vector<neuron> tmp;
        for(int j=0;j<l[i];j++) {
            neuron n(xpos*(i+1),ypos*(j+1));
            tmp.push_back(n);
        }
        neurons.push_back(tmp);
    }

    for(int i=0;i<size-1;i++) {
        std::vector<std::vector<float>> tmpNeuron;
        for(int j=0;j<l[i];j++) {
            std::vector<float> tmpFloat;
            for(int k=0;k<l[i+1];k++) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> dis(-100, 100);
                int randomInt = dis(gen);
                tmpFloat.push_back(static_cast<float>(randomInt) / 100.0f);
                std::cout << "layer: " << i << " from neuron " << j << " to neuron " << k << " weight " << static_cast<float>(randomInt) / 100.0f << std::endl;
            }
            tmpNeuron.push_back(tmpFloat);
        }
        weights.push_back(tmpNeuron);
    }
}

float net::activationFuction(float x) {
    return float(1/(1+std::exp(-x)));
}

float net::activationFuctionDerivative(float x) {
    return float(std::exp(-x)/pow(1+std::exp(-x),2));
}

std::vector<std::vector<neuron>> net::getNet() {
    return neurons;
}

const std::vector<std::vector<std::vector<float>>> &net::getWeights() {
    return weights;
}

void net::setNeuronValue(int layer, int neuron, float value) {
    neurons[layer][neuron].setValue(value);
}

void net::setNeuronDestination(int layer, int neuron, float dest) {
    neurons[layer][neuron].setDest(dest);
}

void net::calculateWeights() {

    // Use random_device to seed the random number generator
    std::random_device rd;

    // Use mt19937 engine for random number generation
    std::mt19937 g(rd());

    // Shuffle the vector so we don't prioritise first neurons, in display neuron values aren't swapping
    std::shuffle(neurons[0].begin(), neurons[0].end(), g);

    //calculation of neuron weights
    for(int i=1;i<neurons.size();i++) {
        for(int j=0;j<neurons[i].size();j++) {
            float sum = 0;
            for(int k=0;k<neurons[i-1].size();k++) {
                sum+=weights[i-1][k][j]*neurons[i-1][k].getValue();
            }

            neurons[i][j].setValue(activationFuction(sum));
        }
    }

    //calculate error for output layer
    for(auto & i : neurons.back()) {
        i.setError(i.getValue()-i.getDest());
    }

    //error calculation for hidden layers
    for(unsigned int i=neurons.size()-2;i>0;i--) {
        for(int j=0;j<neurons[i].size();j++) {
            float eSum = 0;
            for(int k=0;k<neurons[i+1].size();k++) {
                eSum+=neurons[i+1][k].getError()*weights[i][j][k];
            }
            neurons[i][j].setError(eSum);
        }
    }

    //using learning rate and shit
    for(int i=0;i<neurons.size()-1;i++) {
        for(int j=0;j<neurons[i].size();j++) {
            for(int k=0;k<neurons[i+1].size();k++) {
                weights[i][j][k] -= 0.005f * neurons[i+1][k].getError() * activationFuction(neurons[i+1][k].getValue()) *
                        activationFuctionDerivative(neurons[i+1][k].getValue());
            }
        }
    }

    std::cout << neurons.back().back().getError() << std::endl;
}




