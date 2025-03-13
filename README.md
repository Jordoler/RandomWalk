## 2D Random Walk
A basic SDL2 simulation of 2D Random Walk for a determined number of pixels (Ants)

## MakeFile
- Made for Mac with homebrew, SDL2 and SDL_ttf pre-installed

### Optional Configs
#### In RandomWalk.cpp, *Under Includes*
- Number of Ants: **INT**
- Screen Size, (width and height): **Two separate INT values**
- an invisible boundary box: **4 INT values***
- Average position crosshair: **BOOL**
##### Line 210
- Render Delay (ms): **INT**

#### In Ant.cpp
- Different Walk Algorithm: **Two Commented out lines** To enable the "-1, 0, 1" algorithm uncomment the two lines, and comment out the "-1,1" lines
- X-Mode: **4 SDL draw point lines in render method**, to enable uncomment lines
- Line from Origin: **SDL color and SDL draw line**, to enable uncomment these lines
