#include "../header/display.h"
#include "../header/neuron.h"

display::display(SDL_Renderer &renderer) :  r(renderer){}

//int display::SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius) {
//    int offsetx, offsety, d;
//    int status;
//
//    offsetx = 0;
//    offsety = radius;
//    d = radius -1;
//    status = 0;
//
//    while (offsety >= offsetx) {
//        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
//        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
//        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
//        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
//        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
//        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
//        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
//        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);
//
//        if (status < 0) {
//            status = -1;
//            break;
//        }
//
//        if (d >= 2*offsetx) {
//            d -= 2*offsetx + 1;
//            offsetx +=1;
//        }
//        else if (d < 2 * (radius - offsety)) {
//            d += 2 * offsety - 1;
//            offsety -= 1;
//        }
//        else {
//            d += 2 * (offsety - offsetx - 1);
//            offsety -= 1;
//            offsetx += 1;
//        }
//    }
//
//    return status;
//}


int display::SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius) {
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void display::drawNet(const std::vector<std::vector<neuron>>& v) {
    SDL_SetRenderDrawColor(&r, 255, 255, 255, 255);
    for(const auto& x : v) {
        for(auto y : x) {
            SDL_RenderFillCircle(&r,y.getX(),y.getY(),30);
        }
    }
}


