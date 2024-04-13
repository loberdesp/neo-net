#include "../include.h"

#ifndef NEURAL_NET_NEURON_H
#define NEURAL_NET_NEURON_H


class neuron {
private:
    int x,y;
    float value;
public:
    neuron(int x, int y);
    int getX() const;
    int getY() const;
    float getValue() const;
};


#endif //NEURAL_NET_NEURON_H
