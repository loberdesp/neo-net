#include "include.h"
#include "header/neuron.h"
#include "header/render.h"

int main(int argc, char* argv[]) {

    neuron n;
    n.getX();

    render r;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN*4/3, WIN, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Main loop flag
    bool quit = false;
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen (black)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw and fill a rectangle
//        SDL_Rect rect = { 100, 100, 200, 150 }; // x, y, width, height
//        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
//        SDL_RenderFillRect(renderer, &rect);


        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        r.SDL_RenderDrawCircle(renderer,WIN*2/3,WIN/2,20);
        r.SDL_RenderFillCircle(renderer,WIN*1/3,WIN/2,40);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
