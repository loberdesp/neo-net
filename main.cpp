#include "include.h"
#include "header/neuron.h"
#include "header/display.h"
#include "header/net.h"

int main(int argc, char* argv[]) {

    //create net with layers, define input and output values here but ill work it out better way
    net n({3,7,3});
    n.setBiasNeuron(0,0);

    float total_error = 0;

//    n.addInput(0,0,4);
//    n.addInput(0,1,0);
//    n.addInput(1,0,1);
//    n.addInput(1,1,2);

//    input a = n.randomInput();

//    n.forwardTrain(a);
//    n.backProp(a);



    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("NeoNet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
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

    //class for drawing things to screen, has permanent access to renderer
    display d(*renderer);

    // Main loop flag
    bool quit = false;
    bool train = false;
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) {
                    if (train) {
                        train=false;
                    } else {
                        train=true;
                    }
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_LEFT) {
                    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    if(mouseX>WIDTH/2 && mouseX<WIDTH && mouseY>0 && mouseY<HEIGHT) {
                        float dotX = (mouseX-WIDTH/2)/static_cast<float>(WIDTH/2);
                        float dotY = mouseY/static_cast<float>(HEIGHT);
                        if(keyboardState[SDL_SCANCODE_R]) {
                            n.addInput(dotX, dotY, 0);
                        } else if(keyboardState[SDL_SCANCODE_G]) {
                            n.addInput(dotX, dotY, 1);
                        } else if(keyboardState[SDL_SCANCODE_B]) {
                            n.addInput(dotX, dotY, 2);
                        } else if(keyboardState[SDL_SCANCODE_Q]) {
                            n.addInput(dotX, dotY, 3);
                        } else if(keyboardState[SDL_SCANCODE_W]) {
                            n.addInput(dotX, dotY, 4);
                        }
                    }
                }
            }
        }
        if(train) {//trainings per frame
            for(int i=0;i<1024;i++) {
                input rand = n.randomInput();
                n.forwardTrain(rand);
                n.backProp(rand);
            }
            total_error = 0;
            int size = n.getInputs().size();
            for(int i=0;i<size;i++) {
                std::vector<float> ret = n.forwardShow(n.getInputs()[i].x, n.getInputs()[i].y);
                total_error = abs(ret[0] - n.getInputs()[i].mono);
            }
            //std::cout << "error: " << total_error << std::endl;
        }

        // Clear the screen (black)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw net
        d.drawNet(n.getNet(), n.getWeights());
        // Draw visualisation
        d.drawOutput(n);
        d.drawInputs(n.getInputs());

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