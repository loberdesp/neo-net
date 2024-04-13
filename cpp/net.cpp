
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
        v.push_back(tmp);
    }
}

std::vector<std::vector<neuron>> net::getNet() {
    return v;
}
