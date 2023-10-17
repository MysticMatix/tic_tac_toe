#include "game.hpp"
//#include <iostream>

SDL_Renderer* _renderer = nullptr;

BoardSpot* spots[3][3];

Game::Game(){
    state = GameState::Quit;
    window = nullptr;
    _renderer = nullptr;
}

Game::~Game(){
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        //std::cout << "Subsystems initialized!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            //std::cout << "Window created!" << std::endl;
        }

        _renderer = SDL_CreateRenderer(window, -1, 0);
        if(_renderer){
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            //std::cout << "Renderer created!" << std::endl;
        }

        SDL_Surface *icon = IMG_Load("res/icon.png");
        SDL_SetWindowIcon(window, icon);

        state = GameState::PlayerOTurn;
        moves = 0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                spots[i][j] = new BoardSpot("res/spot.png", i * 256, j * 256);
            }
        }

        //std::cout << "Game initialized!" << std::endl;

    }else{
        state = GameState::Quit;
    }
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            state = GameState::Quit;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT){
                int x, y;
                SDL_GetMouseState(&x, &y);
                onBoardClick(x, y);
            }
            break;
        default:
            break;
    }
}

int frameCount = 0;

void Game::update(){
    if(state == GameState::PlayerOTurn || state == GameState::PlayerXTurn){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(spots[i][j]->isEmpty()) spots[i][j]->setState(BoardSpotState::Clear);
            }
        }

        int x, y;
        SDL_GetMouseState(&x, &y);
        if(SDL_GetMouseFocus() == window) if(spots[x / 256][y / 256]->isEmpty()) spots[x / 256][y / 256]->setState(state == GameState::PlayerOTurn ? BoardSpotState::PreviewO : BoardSpotState::PreviewX);

        for(int i = 0; i < 3; i++){
            if(spots[i][0]->getState() == spots[i][1]->getState() && spots[i][1]->getState() == spots[i][2]->getState() && !spots[i][0]->isEmpty()){
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        spots[i][j]->setState(spots[i][j]->getState() == BoardSpotState::X ? BoardSpotState::PreviewX : spots[i][j]->getState() == BoardSpotState::O ? BoardSpotState::PreviewO : BoardSpotState::PreviewClear);
                    }
                }

                if(spots[i][0]->getState() == BoardSpotState::PreviewX){
                    state = GameState::PlayerXWin;
                    spots[i][0]->setState(BoardSpotState::X);
                    spots[i][1]->setState(BoardSpotState::X);
                    spots[i][2]->setState(BoardSpotState::X);
                }
                else if(spots[i][0]->getState() == BoardSpotState::PreviewO){
                    state = GameState::PlayerOWin;
                    spots[i][0]->setState(BoardSpotState::O);
                    spots[i][1]->setState(BoardSpotState::O);
                    spots[i][2]->setState(BoardSpotState::O);
                }
            }

            if(spots[0][i]->getState() == spots[1][i]->getState() && spots[1][i]->getState() == spots[2][i]->getState() && !spots[0][i]->isEmpty()){
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        spots[i][j]->setState(spots[i][j]->getState() == BoardSpotState::X ? BoardSpotState::PreviewX : spots[i][j]->getState() == BoardSpotState::O ? BoardSpotState::PreviewO : BoardSpotState::PreviewClear);
                    }
                }

                if(spots[0][i]->getState() == BoardSpotState::PreviewX){
                    state = GameState::PlayerXWin;
                    spots[0][i]->setState(BoardSpotState::X);
                    spots[1][i]->setState(BoardSpotState::X);
                    spots[2][i]->setState(BoardSpotState::X);
                }
                else if(spots[0][i]->getState() == BoardSpotState::PreviewO){
                    state = GameState::PlayerOWin;
                    spots[0][i]->setState(BoardSpotState::O);
                    spots[1][i]->setState(BoardSpotState::O);
                    spots[2][i]->setState(BoardSpotState::O);
                }
            }
        }

        if(spots[0][0]->getState() == spots[1][1]->getState() && spots[1][1]->getState() == spots[2][2]->getState() && !spots[0][0]->isEmpty()){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    spots[i][j]->setState(spots[i][j]->getState() == BoardSpotState::X ? BoardSpotState::PreviewX : spots[i][j]->getState() == BoardSpotState::O ? BoardSpotState::PreviewO : BoardSpotState::PreviewClear);
                }
            }

            if(spots[0][0]->getState() == BoardSpotState::PreviewX){
                state = GameState::PlayerXWin;
                spots[0][0]->setState(BoardSpotState::X);
                spots[1][1]->setState(BoardSpotState::X);
                spots[2][2]->setState(BoardSpotState::X);
            }
            else if(spots[0][0]->getState() == BoardSpotState::PreviewO){
                state = GameState::PlayerOWin;
                spots[0][0]->setState(BoardSpotState::O);
                spots[1][1]->setState(BoardSpotState::O);
                spots[2][2]->setState(BoardSpotState::O);
            }
        }

        if(spots[0][2]->getState() == spots[1][1]->getState() && spots[1][1]->getState() == spots[2][0]->getState() && !spots[0][2]->isEmpty()){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    spots[i][j]->setState(spots[i][j]->getState() == BoardSpotState::X ? BoardSpotState::PreviewX : spots[i][j]->getState() == BoardSpotState::O ? BoardSpotState::PreviewO : BoardSpotState::PreviewClear);
                }
            }

            if(spots[0][2]->getState() == BoardSpotState::PreviewX){
                state = GameState::PlayerXWin;
                spots[0][2]->setState(BoardSpotState::X);
                spots[1][1]->setState(BoardSpotState::X);
                spots[2][0]->setState(BoardSpotState::X);
            }
            else if(spots[0][2]->getState() == BoardSpotState::PreviewO){
                state = GameState::PlayerOWin;
                spots[0][2]->setState(BoardSpotState::O);
                spots[1][1]->setState(BoardSpotState::O);
                spots[2][0]->setState(BoardSpotState::O);
            }
        }

        if(moves == 9){
            state = GameState::Tie;
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    spots[i][j]->setState(spots[i][j]->getState() == BoardSpotState::X ? BoardSpotState::PreviewX : BoardSpotState::PreviewO);
                }
            }
        }

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                spots[i][j]->update();
            }
        }
    }
    else{

    }
}



void Game::render(){
    SDL_RenderClear(_renderer);

    // this is where we would add stuff to render
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            spots[i][j]->render();
        }
    }

    SDL_RenderPresent(_renderer);
}

void Game::onBoardClick(int x, int y){
    if(state == GameState::PlayerXTurn || state == GameState::PlayerOTurn){
        BoardSpot *spot = spots[x / 256][y / 256];
        if(spot->isEmpty()){
            spot->setState(state == GameState::PlayerOTurn ? BoardSpotState::O : BoardSpotState::X);
            state = state == GameState::PlayerOTurn ? GameState::PlayerXTurn : GameState::PlayerOTurn;
            moves++;
        }
    }
    else{
        reset();
    }
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    //std::cout << "Game cleaned!" << std::endl;
}

bool Game::running(){
    return state != GameState::Quit;
}

void Game::reset(){
    state = GameState::PlayerOTurn;
    moves = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            spots[i][j]->setState(BoardSpotState::Clear);
        }
    }
}