#include "game.hpp"
#include "textureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* fileName){
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}
