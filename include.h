#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <random>

#define WIN 512

#define WIDTH WIN*2
#define HEIGHT WIN
#define PIXEL_NUM 64
#define SEGMENT_SIZE WIN/PIXEL_NUM
#define LEARNING_RATE 0.03f