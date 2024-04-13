#include "../header/neuron.h"

neuron::neuron(int x, int y) : x(x), y(y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 100);
    int randomInt = dis(gen);
    value = static_cast<float>(randomInt) / 100.0f;
}

int neuron::getX() const {
    return x;
}

int neuron::getY() const {
    return y;
}

float neuron::getValue() const {
    return value;
}
