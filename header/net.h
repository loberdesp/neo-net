#include "../include.h"
#include "neuron.h"

#ifndef NEURAL_NET_NET_H
#define NEURAL_NET_NET_H


class net {
private:
    std::vector<std::vector<neuron>> v;
public:
    explicit net(std::vector<int> l);
    std::vector<std::vector<neuron>> getNet();
};


#endif //NEURAL_NET_NET_H
