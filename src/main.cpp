#include "game.hpp"

Game *game = nullptr;

int fps = 120;
int frameDelay = 1000 / fps;

int main(int argc, char *argv[]){
    game = new Game();

    game->init("Tic tac toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 768, false);
    

    while(game->running()){
        Uint32 frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}