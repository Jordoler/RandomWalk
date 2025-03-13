#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <TextRenderer.h>

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    // Set the text color (white)
    SDL_Color color = {255, 255, 255, 255};

    // Create a surface with the text
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        return;
    }

    // Get the dimensions of the texture
    int textWidth = 0, textHeight = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

    // Define the destination rectangle for the text
    SDL_Rect dstRect = {x, y, textWidth, textHeight};

    // Render the text to the screen
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    // Clean up the texture
    SDL_DestroyTexture(texture);
}
