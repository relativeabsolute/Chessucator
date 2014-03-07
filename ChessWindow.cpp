/*
Copyright (c) 2013 Johan Burke

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

/* 
 * File:   ChessWindow.cpp
 * Author: johan
 *
 * Created on November 18, 2013, 9:24 PM
 */

#include "ChessWindow.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

using namespace Chess;

ChessWindow::ChessWindow() {
    window = nullptr;
    ren = nullptr;
    currentTurn = true;
}

int ChessWindow::execute() {
    if (!init()) {
        return -1;
    }
    mainLoop();
    cleanup();
    return 0;
}

void ChessWindow::cleanup() {
    delete game;
    Logger::destroy();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
}

void ChessWindow::handleMotion(SDL_MouseMotionEvent* evt) {
    // TODO: handle hover on highlighted squares etc
}

void ChessWindow::handleKeyDown(SDL_KeyboardEvent* evt) {
    switch (evt->keysym.sym) {
        case SDLK_SPACE:
            l->output << "////Dumping values////" << std::endl;
            l->output << *game;
            l->output << "////End dump////" << std::endl;
            break;
    }
}

void ChessWindow::handleEvent(SDL_Event* evt) {
    if (evt->type == SDL_QUIT) {
        l->output << "SDL_QUIT event received.  Exiting." << std::endl;
        running = false;
    } else if (evt->type == SDL_MOUSEBUTTONDOWN) {
        handleClick(&evt->button);
    } else if (evt->type == SDL_MOUSEMOTION) {
        handleMotion(&evt->motion);
    } else if (evt->type == SDL_KEYDOWN) {
        handleKeyDown(&evt->key);
    }
}

BoardLocation ChessWindow::getLocationFromCoordinates(int x, int y) const {
    int file = x / SQUARE_WIDTH;
    int rank = BoardLocation::windowYCoordToBoardCoord(y);
    return game->getLocation(file, rank);
}

void ChessWindow::handleClick(SDL_MouseButtonEvent* evt) {
    l->output << "SDL_MOUSEBUTTONDOWN event received.  X = " <<
            evt->x << " Y = " << evt->y << std::endl;
    if (evt->x <= SQUARE_WIDTH * 8 && evt->y <= SQUARE_WIDTH * 8) {
        BoardLocation loc = getLocationFromCoordinates(evt->x, evt->y);
        l->output << "Mouse clicked at " << loc << std::endl;
        Piece *p = game->getPieceAt(loc.file, loc.rank);
        if (loc.highlighted) {
            l->output << "Making move of " << *lastPieceClicked << " to " << loc << std::endl;
            lastPieceClicked->makeMove(loc);
            currentTurn = !currentTurn;
        } else if (p != nullptr) {
            l->output << "Piece clicked: " << *p << std::endl;
            if (p->getColor() == currentTurn) {
                game->highlightLegalMoves(p);
                lastPieceClicked = p;
            }
        } else {
            game->clearHighlights();
            lastPieceClicked = nullptr;
        }
    } else {
        game->clearHighlights();
        lastPieceClicked = nullptr;
    }
}

void ChessWindow::render() {
    game->render();
    SDL_RenderPresent(ren);
}

void ChessWindow::mainLoop() {
    running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            handleEvent(&e);
        }
      render();
    }
}

bool ChessWindow::init() {
    l = Logger::getInstance();
    l->open("Log.txt");
    l->output << "Creating window." << std::endl;
    int width = 1280;
    int height = 1024;
    window = SDL_CreateWindow("Chess", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        l->output << SDL_GetError() << std::endl;
        return false;
    }
    l->output << "Window created successfully." << std::endl;
    l->output << "Creating renderer." << std::endl;
    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (ren == nullptr) {
        l->output << SDL_GetError() << std::endl;
        return false;
    }
    l->output << "Renderer created successfully." << std::endl;

    l->output << "Initializing SDL_image." << std::endl;
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        l->output << IMG_GetError() << std::endl;
        return false;
    }
    l->output << "SDL_image initialized successfully." << std::endl;

    l->output << "Initializing SDL_ttf." << std::endl;
    if (TTF_Init() == -1) {
        l->output << TTF_GetError() << std::endl;
        return false;
    }
    l->output << "SDL_ttf initialized successfully." << std::endl;

    return initGame();
}

bool ChessWindow::initGame() {
    game = new StandardGame(ren);
    game->initializeBoard();
    return true;
}