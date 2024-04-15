#include "../header/display.h"
#include "../header/neuron.h"
#include "../header/net.h"

display::display(SDL_Renderer &renderer) :  r(renderer){
    gFont = TTF_OpenFont("../assets/font.ttf", 18); // Change the path to your font file
    if (gFont == nullptr) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(0);
    }
}

int display::SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

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

void display::renderText(const std::string& text, int x, int y) {
    SDL_Color textColor = {0, 0, 0}; // black color
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (textSurface == nullptr) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(&r, textSurface);
        if (texture == nullptr) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            SDL_Rect renderQuad = {x-textSurface->w/2, y-textSurface->h/2, textSurface->w, textSurface->h};
            SDL_RenderCopy(&r, texture, nullptr, &renderQuad);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(textSurface);
    }
}

void display::drawNet(const std::vector<std::vector<neuron>>& v, const std::vector<std::vector<std::vector<float>>>& w) {
    //draw connections between layers
    unsigned int size = v.size();

    for(int i=0;i<size-1;i++) {
        for(int j=0;j<v[i].size();j++) {
            for(int k=0;k<v[i+1].size();k++) {
                if(w[i][j][k]>0) {
                    SDL_SetRenderDrawColor(&r, 0, 255, 0, 255);
                } else {
                    SDL_SetRenderDrawColor(&r, 255, 0, 0, 255);
                }
                SDL_RenderDrawLine(&r, v[i][j].getX(), v[i][j].getY(), v[i+1][k].getX(), v[i+1][k].getY());
            }
        }
    }

    SDL_SetRenderDrawColor(&r, 255, 255, 255, 255);

    //draw neurons
    for(const auto& x : v) {
        for(auto y : x) {
            SDL_RenderFillCircle(&r,y.getX(),y.getY(),30);
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(2) << y.getValue();
            renderText(stream.str(), y.getX(), y.getY());
        }
    }
}

void display::drawOutput(net &n) {
    for(int i=0;i<PIXEL_NUM;i++) {
        for(int j=0;j<PIXEL_NUM;j++) {
            std::vector<float> color = n.forwardShow(float(i)/PIXEL_NUM,float(j)/PIXEL_NUM);
            //std::cout << i << " " << j << " " << 255*color[0] << " " << 255*color[1] << " " << 255*color[2] << " " << std::endl;
            SDL_SetRenderDrawColor(&r, 255*color[0], 255*color[1], 255*color[2], SDL_ALPHA_OPAQUE);
            SDL_Rect segmentRect = { i * SEGMENT_SIZE+WIDTH/2, j * SEGMENT_SIZE, SEGMENT_SIZE, SEGMENT_SIZE};
            SDL_RenderFillRect(&r, &segmentRect);
        }
    }
}

void display::drawInputs(const std::vector<input>& i) {
    for(auto x : i) {
        if(!x.rgb.empty()) {
            if(x.rgb[0]==1) {
                SDL_SetRenderDrawColor(&r, 255, 0, 0, SDL_ALPHA_OPAQUE);
            } else if(x.rgb[1]) {
                SDL_SetRenderDrawColor(&r, 0, 255, 0, SDL_ALPHA_OPAQUE);
            } else if(x.rgb[2]) {
                SDL_SetRenderDrawColor(&r, 0, 0, 255, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderFillCircle(&r,WIDTH/2*(x.x+1),x.y*HEIGHT,5);
            SDL_SetRenderDrawColor(&r, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawCircle(&r,WIDTH/2*(x.x+1),x.y*HEIGHT,5);
        } else {
            if(x.mono==1) {
                SDL_SetRenderDrawColor(&r, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderFillCircle(&r,WIDTH/2*(x.x+1),x.y*HEIGHT,5);
                SDL_SetRenderDrawColor(&r, 0, 0, 0, SDL_ALPHA_OPAQUE);
            }
            else if(x.mono==0) {
                SDL_SetRenderDrawColor(&r, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillCircle(&r,WIDTH/2*(x.x+1),x.y*HEIGHT,5);
                SDL_SetRenderDrawColor(&r, 255, 255, 255, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderDrawCircle(&r,WIDTH/2*(x.x+1),x.y*HEIGHT,5);
        }

    }
}
