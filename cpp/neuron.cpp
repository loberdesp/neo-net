#include "../header/neuron.h"

neuron::neuron() {
    x = WIN/2;
    y = WIN/2;
}

int neuron::getX() const {
    return x;
}

int neuron::getY() const {
    return y;
}