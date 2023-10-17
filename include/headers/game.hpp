#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "textureManager.hpp"
#include "gameObject.hpp"
#include "boardSpot.hpp"

extern SDL_Renderer *_renderer;

enum class GameState{
    PlayerXTurn,
    PlayerOTurn,
    PlayerXWin,
    PlayerOWin,
    Tie,
    Quit
};

class Game{
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        void render();
        void reset();
        void clean();

        void onBoardClick(int x, int y);

        bool running();
    private:
        GameState state;
        SDL_Window *window;

        int moves;

};
