#include "gameObject.hpp"

GameObject::GameObject(){
};

GameObject::GameObject(const char* texturesheet, int x, int y){
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
}

GameObject::GameObject(SDL_Texture* texturesheet, int x, int y){
    objTexture = texturesheet;

    xpos = x;
    ypos = y;
}

GameObject::~GameObject(){
}

void GameObject::update(){
    xpos++;
    ypos++;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::render(){
    SDL_RenderCopy(_renderer, objTexture, &srcRect, &destRect);
}