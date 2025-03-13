#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <TextRenderer.h>
#include <Ant.h>
#include <time.h>
#include <iostream>
#include <string>
#include <ctime>  
#include <cmath>
#include <iomanip>
#include <sstream> 

// Screen dimensions
//Full screen on mac no High DPI 1512x916
//Full screen on mac High DPI 3024x1832

int SCREEN_WIDTH = 1512; 
int SCREEN_HEIGHT = 916;

// Ant Configs
const int ANT_NUM = 100000;

// Box Configs
int XRightBoundary = SCREEN_WIDTH - 10;
int XLeftBoundary = 10 ;
int YLowerBoundary = SCREEN_HEIGHT - 10;
int YUpperBoundary = 60;

// Avg Distance crosshair
bool avg_Distance_Crosshair = false;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create the SDL window
    SDL_Window* window = SDL_CreateWindow(
        "2D Random Walk",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE  | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create the SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
// Put Pre-Loads Here
    int cycles = 0;
    clock_t dtime;
    int time;
    int frames;
    int logicalWidth, logicalHeight;
    SDL_GetRendererOutputSize(SDL_GetRenderer(window), &logicalWidth, &logicalHeight);
    SCREEN_WIDTH = logicalWidth; //3840x2160
    SCREEN_HEIGHT = logicalHeight;
    XRightBoundary = SCREEN_WIDTH - 10;
    XLeftBoundary = 10 ;
    YLowerBoundary = SCREEN_HEIGHT - 10;
    YUpperBoundary = 60;

    int vertical = 0;
    int horizontal = 0;
    int xpos = SCREEN_WIDTH/2;
    int ypos = SCREEN_HEIGHT/2;
    // Create a vector to store multiple point objects
    std::vector<Ant> points;

    // Initialize the ants with random colors
    for (int i = 0; i < ANT_NUM; i++) {
        int x = xpos;
        int y = ypos;
        SDL_Color color = {static_cast<Uint8>(rand() % 256), 
            static_cast<Uint8>(rand() % 256), 
            static_cast<Uint8>(rand() % 256), 
            255};
        points.emplace_back(x, y, color); // Create and add the ant to vector
    }

    // Load fonts
    TTF_Font* font = TTF_OpenFont("assets/fonts/ubuntu/UbuntuMono-B.ttf", 24);
    TTF_Font* debug = TTF_OpenFont("assets/fonts/jetbrains/JetBrainsMono-Thin.ttf", 12);
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    

    // Main loop flag
    bool quit = false;
    // Event handler
    SDL_Event e;
    // Main loop
    while (!quit) {
        // Quit Handling
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        // Pre-Render Calcs
        clock_t startframe = clock();
        // Clear screen with a color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_GetWindowSizeInPixels(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

        // Add any rendering here
        SDL_SetRenderDrawColor(renderer, 255,255,255, 0);
        renderText(renderer,font,"2D Random Walk",SCREEN_WIDTH/2 -100,15);

        renderText(renderer,debug,"cycles: ",SCREEN_WIDTH - 145,0);
        renderText(renderer,debug,std::to_string(cycles),SCREEN_WIDTH - 90,0);

        renderText(renderer,debug,"time: ",SCREEN_WIDTH - 145,40);
        renderText(renderer,debug,std::to_string(time/1000),SCREEN_WIDTH - 100,40);

        // renderText(renderer,debug,"dtime: ",SCREEN_WIDTH - 145,60);
        // renderText(renderer,debug,std::to_string(dtime),SCREEN_WIDTH - 100,60);

        renderText(renderer,debug,"FPS: ",SCREEN_WIDTH - 145,20);
        renderText(renderer,debug,std::to_string(frames),SCREEN_WIDTH - 105,20);
        SDL_RenderDrawLine(renderer,0,55,SCREEN_WIDTH,55);




        renderText(renderer,debug,"No. Ants: ",10,0);
        renderText(renderer,debug,std::to_string(ANT_NUM),75,0);



        float avg_distance = 0;
        float avg_x = 0;
        float avg_y = 0;
        for (auto& point : points) {
            float distance;
            point.update();
            if (point.getPosition('x')>=XRightBoundary){point.setPositionX(XRightBoundary-1);};
            if (point.getPosition('x')<=XLeftBoundary){point.setPositionX(XLeftBoundary+1);};
            if (point.getPosition('y')>=YLowerBoundary){point.setPositionY(YLowerBoundary-1);};
            if (point.getPosition('y')<=YUpperBoundary){point.setPositionY(YUpperBoundary+1);};            
            point.render(renderer);
           // SDL_RenderDrawLine(renderer,point.getPosition('x'),point.getPosition('y'),SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
            distance = sqrt(pow((point.getPosition('x')-SCREEN_WIDTH/2),2) + pow((point.getPosition('y')-SCREEN_HEIGHT/2),2));
            avg_distance += distance;
            avg_x +=point.getPosition('x')-SCREEN_WIDTH/2; 
            avg_y +=point.getPosition('y')-SCREEN_HEIGHT/2;
        }
        avg_distance = avg_distance/ANT_NUM;
        avg_x = avg_x/ANT_NUM;
        avg_y = avg_y/ANT_NUM;
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << avg_distance;
        std::string distance_str = stream.str();  // Convert to string
        renderText(renderer,debug,"<Distance>: ",10,20);
        renderText(renderer,debug,distance_str,95,20);
        renderText(renderer,debug,"<pos>: ",10,40);
        stream.str("");
        stream << std::fixed << std::setprecision(2) << avg_x;
        std::string avg_x_str = stream.str(); 
        stream.str("");
        stream << std::fixed << std::setprecision(2) << avg_y;
        std::string avg_y_str = stream.str(); 
        renderText(renderer, debug, avg_x_str + ", " + avg_y_str, 50, 40);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        if (avg_Distance_Crosshair)
        {
            SDL_RenderDrawLine(renderer,(avg_x+SCREEN_WIDTH/2),(avg_y+SCREEN_HEIGHT/2)-20,(avg_x+SCREEN_WIDTH/2),(avg_y+SCREEN_HEIGHT/2)+20);
            SDL_RenderDrawLine(renderer,(avg_x+SCREEN_WIDTH/2)-20,(avg_y+SCREEN_HEIGHT/2),(avg_x+SCREEN_WIDTH/2)+20,(avg_y+SCREEN_HEIGHT/2));
            /* code */
        }
        
        


        // Update the screen
        SDL_RenderPresent(renderer);
        cycles = cycles + 1;
        clock_t endframe = clock();
        dtime = (endframe - startframe)/(CLOCKS_PER_SEC/1000);
        time +=dtime; 
        frames = 1000/dtime;
        //SDL_Delay(20); if things are moving too fast
    }

    // Clean up and close the SDL components
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    // debug stuff I dont wanna get rid of.
    // std::cout<<"LogicalHeight: "<<logicalHeight<<std::endl;
    // std::cout<<"LogicalWidth: "<<logicalWidth<<std::endl;
    
    return 0;
}



