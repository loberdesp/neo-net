#include "../header/neuron.h"

neuron::neuron(int x, int y) : x(x), y(y) {}

int neuron::getX() const {
    return x;
}

int neuron::getY() const {
    return y;
}

float neuron::getValue() const {
    return value;
}
