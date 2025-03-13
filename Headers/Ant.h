#include <SDL.h> 


class Ant {
    private:
        int xpos, ypos;   
        SDL_Color color;  
    
    public:
        // Constructor
        Ant(int x, int y, SDL_Color c) : xpos(x), ypos(y), color(c) {}
        // Destructor need to finish
        ~Ant(){}
    
        // Update position Options
        void setPosition(int x, int y);
        void setPositionX(int x);
        void setPositionY(int y);
        void update();

        // Gets
        int getPosition(char a);
    
        // Render ant
        void render(SDL_Renderer* renderer);
    };
    