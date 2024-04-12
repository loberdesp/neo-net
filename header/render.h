#include "../include.h"

#ifndef NEURAL_NET_RENDER_H
#define NEURAL_NET_RENDER_H


class render {

public:
    int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius);
    int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

};


#endif //NEURAL_NET_RENDER_H
