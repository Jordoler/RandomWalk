#include "Ant.h"

// Ant::Ant(int x, int y, SDL_Color c) : xpos(x), ypos(y), color(c) {}s

void Ant::setPosition(int x, int y) {
    xpos = x;
    ypos = y;
}
void Ant::setPositionX(int x) {
    xpos = x;
}
void Ant::setPositionY(int y) {
    ypos = y;
}

void Ant::update() {
    // xpos += (rand() % 3) - 1; // Moves -1 0 or 1 in x-direction NOT ACTUALLY RANDOM WALK ALGORITHM
    // ypos += (rand() % 3) - 1; // Moves -1 0 or 1 in y-direction NOT ACTUALLY RANDOM WALK ALGORITHM
    xpos += (rand() % 2)*2 -1; // Moves -1 or 1 in x-direction
    ypos += (rand() % 2)*2 -1; // Moves -1 or 1 in y-direction
}

int Ant::getPosition(char a) {
    if (a == 'x') { 
        return xpos;
    } else if (a == 'y') {
        return ypos;
    } else {
        return 0;
    }
}


void Ant::render(SDL_Renderer* renderer) {
     SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
     // Normal Render
     SDL_RenderDrawPoint(renderer, xpos, ypos);
// Optional: X-mode
     // SDL_RenderDrawPoint(renderer, xpos - 1, ypos - 1);
     // SDL_RenderDrawPoint(renderer, xpos - 1, ypos + 1);
     // SDL_RenderDrawPoint(renderer, xpos + 1, ypos - 1);
     // SDL_RenderDrawPoint(renderer, xpos + 1, ypos + 1);
// Optional: Line from Origin
     //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
     //SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, xpos, ypos);
     }