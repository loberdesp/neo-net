#include "../include.h"
#include "neuron.h"

#ifndef NEURAL_NET_RENDER_H
#define NEURAL_NET_RENDER_H


class display {

    SDL_Renderer &r;
    TTF_Font *gFont = nullptr;

public:
    explicit display(SDL_Renderer &renderer);
    //static int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius);
    static int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius);
    void renderText(const std::string &text, int x, int y);
    void drawNet(const std::vector<std::vector<neuron>>& v);
};


#endif //NEURAL_NET_RENDER_H
