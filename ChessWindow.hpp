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
File:   ChessWindow.hpp
Author: johan
Created on November 18, 2013, 9:18 PM
*/

#ifndef CHESSWINDOW_HPP
#define	CHESSWINDOW_HPP

#include <SDL2/SDL.h>
#include "Chess.hpp"
#include "Games.hpp"
#include "Logger.hpp"
#include <memory>

namespace Chess {

    class ChessWindow {
    public:
        ChessWindow();

        int execute();
    private:
        /**
         * Render pieces and squares.
         */
        void render();
        bool init();
        bool initGame();
        void mainLoop();
        void cleanup();
        void handleEvent(SDL_Event *evt);
        void handleClick(SDL_MouseButtonEvent *evt);
        void handleMotion(SDL_MouseMotionEvent *evt);
        void handleKeyDown(SDL_KeyboardEvent *evt);
        
        /**
         * Convert window coordinates into a rank and file.
         * @param x The x coordinate to convert.
         * @param y The y coordinate to convert.
         * @return A board location containing the rank and file of the given coordinates.
         */
        BoardLocation getLocationFromCoordinates(int x, int y) const;

        SDL_Window *window;
        SDL_Renderer *ren;
        bool running;
        bool currentTurn;  // true for white false for black
        Game *game;
        Logger *l;
        Piece *lastPieceClicked;
    };
}

#endif	/* CHESSWINDOW_HPP */

