
#include <cmath>

#include "../header/net.h"

net::net(std::vector<int> l) {
    unsigned int size = l.size();
    int xpos = WIDTH/2/(size+1);

    for(int i=0;i<size;i++) {
        int ypos = WIDTH/2/(l[i]+1);
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
    return 1/(1+exp(-x));
}

float net::activationFuctionDerivative(float x) {
    double sig = activationFuction(x);
    return sig * (1-sig);
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

input net::randomInput() {
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, inputs.size()-1);

    for(auto x : weights) {
        std::cout << x.size() << std::endl;
    }
    return inputs[dist(mt)];

}

void net::forwardTrain(input rand) {
    //calculation of neuron weights
    for(int i=0;i<neurons.size();i++) {
        for(int j=0;j<neurons[i].size();j++) {
            if(i==0) {
                if(j==0) {
                    neurons[i][j].setValue(rand.x);
                } else {
                    neurons[i][j].setValue(rand.y);
                }
            } else {
                float sum = 0;
                for(int k=0;k<neurons[i-1].size();k++) {
                    sum+=weights[i-1][k][j]*neurons[i-1][k].getValue();
                }
                neurons[i][j].setValue(activationFuction(sum));
            }
        }
    }
}

void net::backProp(input rand) {
    //error calculation for hidden layers
    for(unsigned int i=neurons.size()-1;i>0;i--) {
        for(int j=0;j<neurons[i].size();j++) {
            if(i==neurons.size()-1) {
                if(rand.rgb.empty()) {
                    //std::cout << "error: " << neurons[i][j].getValue() << " " << float(rand.mono) << std::endl;
                    neurons[i][j].setError(float(neurons[i][j].getValue()-float(rand.mono)));
                } else {
                    neurons[i][j].setError(float(neurons[i][j].getValue()-float(rand.rgb[j])));
                }
            } else {
                float eSum = 0;
                for(int k=0;k<neurons[i+1].size();k++) {
                    eSum+=neurons[i+1][k].getError()*weights[i][j][k];
                }

                neurons[i][j].setError(eSum);
            }
            //std::cout << "layer: " << i << " neuron: " << j << " error: " << neurons[i][j].getError() << std::endl;
        }
    }

    //using learning rate and shit i have no idea why it doesn't work i swear to god, i spent waaaay too much time looking for mistake
    for(unsigned int i=neurons.size()-1;i>0;i--) {
        std::cout << "i: " <<  i << std::endl;
        //std::cout << weights[i-1].size() << std::endl;
        for(unsigned int j=0;j<neurons[i].size();j++) {
            for(unsigned int k=0;k<neurons[i-1].size();k++) {
                //std::cout << "error: " <<  neurons[i][k].getError() << " value: " << neurons[i][k].getValue() << " der: " << activationFuctionDerivative(neurons[i][k].getValue()) << std::endl;
                weights[i-1][k][j] -= LEARNING_RATE * neurons[i][j].getError() * neurons[i-1][k].getValue() *
                                    activationFuctionDerivative(neurons[i][j].getValue());
            }
        }
    }
}

std::vector<float> net::forwardShow(float x, float y) {
    std::vector<std::vector<neuron>> nCopy = neurons;

    nCopy[0][0].setValue(x);
    nCopy[0][1].setValue(y);

    for(int i=1;i<nCopy.size();i++) {
        for(int j=0;j<nCopy[i].size();j++) {
            float sum = 0;
            for(int k=0;k<nCopy[i-1].size();k++) {
                sum+=weights[i-1][k][j]*nCopy[i-1][k].getValue();
            }
            nCopy[i][j].setValue(activationFuction(sum));
        }
    }
    //std::cout << nCopy.back()[0].getValue() << " " << nCopy.back()[1].getValue() << " " << nCopy.back()[2].getValue() << std::endl;
    if(nCopy.back().size()==1) {
        return {nCopy.back().back().getValue(), nCopy.back().back().getValue(), nCopy.back().back().getValue()};
    } else {
        return {nCopy.back()[0].getValue(), nCopy.back()[1].getValue(), nCopy.back()[2].getValue()};
    }
}

void net::addInput(float x, float y, int col) {
    input i{x,y};
    switch(col) {
        case 0://red
            i.rgb = {1,0,0};
            break;
        case 1://green
            i.rgb = {0,1,0};
            break;
        case 2://blue
            i.rgb = {0,0,1};
            break;
        case 3://white
            i.mono = true;
            break;
        case 4://black
            i.mono = false;
            break;
        default:
            break;}
    inputs.push_back(i);
}

void net::addOutput(bool o) {
    outputs.push_back(o);
}

std::vector<input> net::getInputs() {
    return inputs;
}
