#include "boardSpot.hpp"

BoardSpot::BoardSpot(const char* texturesheet, int x, int y){
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;

    state = BoardSpotState::Clear;
}

BoardSpot::BoardSpot(SDL_Texture* texturesheet, int x, int y){
    objTexture = texturesheet;

    xpos = x;
    ypos = y;

    state = BoardSpotState::Clear;
}

BoardSpot::~BoardSpot(){
}

void BoardSpot::update(){
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 32 * (int)state;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 8;
    destRect.h = srcRect.h * 8;
}

void BoardSpot::render(){
    SDL_RenderCopy(_renderer, objTexture, &srcRect, &destRect);
}

void BoardSpot::setState(BoardSpotState state){
    this->state = state;
}

bool BoardSpot::isEmpty(){
    return state == BoardSpotState::Clear || state == BoardSpotState::PreviewClear || state == BoardSpotState::PreviewX || state == BoardSpotState::PreviewO;
}

BoardSpotState BoardSpot::getState(){
    return state;
}