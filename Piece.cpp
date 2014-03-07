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
File:   Piece.cpp
Author: johan
Created on November 2, 2013, 4:06 PM
 */

#include "Chess.hpp"
#include "Pieces.hpp"
#include "Logger.hpp"

using namespace Chess;

Piece::Piece(Game *game, const BoardLocation &location, bool color) {
    this->game = game;
    this->loc = location;
    this->color = color;
}

Piece::~Piece() {

}

void Piece::makeMove(const BoardLocation& newLoc) {
    game->makeMove(this, newLoc);
}

void Piece::setLocation(const BoardLocation& loc) {
    this->loc = loc;
}

BoardLocation Piece::getLocation() const {
    return loc;
}

bool Piece::getColor() const {
    return color;
}

bool Piece::hasBeenCaptured() const {
    return captured;
}

void Piece::setCaptured(bool nowCaptured) {
    captured = nowCaptured;
}

bool Piece::hasJustMoved() const {
    return justMoved;
}

bool Piece::hasMoved() const {
    return moved;
}