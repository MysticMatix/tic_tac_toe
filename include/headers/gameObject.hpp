#pragma once

#include "game.hpp"

class GameObject{
    public:
        GameObject(const char* texturesheet, int x, int y);
        GameObject(SDL_Texture* texturesheet, int x, int y);
        GameObject();
        ~GameObject();

        void update();
        void render();

    private:

        int xpos;
        int ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;
};