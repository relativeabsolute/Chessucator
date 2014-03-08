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
File:   Games.cpp
Author: johan
Created on November 7, 2013, 8:59 PM
 */

#include "Games.hpp"
#include "Pieces.hpp"

using namespace Chess;

StandardGame::StandardGame(SDL_Renderer* r) : Game(r) {
}

void StandardGame::initializeBoard() {
    BoardLocation loc;
    // pawns
    Piece *p;
    bool color;
    for (size_t i = 0; i < 16; ++i) {
        color = i <= 7;
        loc.file = i % 8;
        loc.rank = color ? 1 : 6;
        p = new Pawn(this, loc, color);
        loc.occupyingPiece = p;
        addPiece(p, i);
    }
    for (size_t i = 0; i < 4; ++i) {
        color = i <= 1;
        loc.file = i % 2 == 0 ? 2 : 5;
        loc.rank = color ? 0 : 7;
        p = new Bishop(this, loc, color);
        loc.occupyingPiece = p;
        addPiece(p, i + 16);
    }
    for (size_t i = 0; i < 4; ++i) {
        color = i <= 1;
        loc.file = i % 2 == 0 ? 0 : 7;
        loc.rank = color ? 0 : 7;
        p = new Rook(this, loc, color);
        loc.occupyingPiece = p;
        addPiece(p, i + 20);
    }
    for (size_t i = 0; i < 4; ++i) {
        color = i <= 1;
        loc.file = i % 2 == 0 ? 1 : 6;
        loc.rank = color ? 0 : 7;
        p = new Knight(this, loc, color);
        loc.occupyingPiece = p;
        addPiece(p, i + 24);
    }
    for (size_t i = 0; i < 2; ++i) {
        color = i % 2 == 0;
        loc.file = 3;
        loc.rank = color ? 0 : 7;
        p = new Queen(this, loc, color);
        loc.occupyingPiece = p;
        addPiece(p, i + 28);
    }
}