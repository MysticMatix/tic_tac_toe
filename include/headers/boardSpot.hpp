#pragma once

#include "game.hpp"

enum class BoardSpotState{
    Clear, X, O, PreviewClear, PreviewX, PreviewO
};

class BoardSpot{
    public:
        BoardSpot(const char* texturesheet, int x, int y);
        BoardSpot(SDL_Texture* texturesheet, int x, int y);
        ~BoardSpot();

        void update();
        void render();

        void setState(BoardSpotState state);
        BoardSpotState getState();

        bool isEmpty();
    private:
        BoardSpot();
        int xpos;
        int ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;

        BoardSpotState state;
};