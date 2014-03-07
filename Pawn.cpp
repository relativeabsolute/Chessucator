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
File:   Pawn.cpp
Author: johan
Created on January 1, 2014, 4:04 PM
 */

#include "Chess.hpp"
#include "Pieces.hpp"
#include "Logger.hpp"

using namespace Chess;

Pawn::Pawn(Game *game, const BoardLocation &location, bool color) : Piece(game, location, color) {
}

bool Pawn::isCheck(const BoardLocation &location) const {
    int direction = color ? 1 : -1;
    if (location.file > 0) {
        BoardLocation checkLeft;
        checkLeft.file = location.file - 1;
        checkLeft.rank = location.rank + direction;
        Piece *piece = game->getPieceAt(checkLeft.file, checkLeft.rank);
        if (piece != nullptr) {
            if (piece->getType() == PieceType::KING_TYPE && piece->getColor() != color) {
                return true;
            }
        }
    }
    if (location.file < 7) {
        BoardLocation checkRight;
        checkRight.file = location.file + 1;
        checkRight.rank = location.rank + direction;
        Piece *piece = game->getPieceAt(checkRight.file, checkRight.rank);
        if (piece != nullptr) {
            if (piece->getType() == PieceType::KING_TYPE && piece->getColor() != color) {
                return true;
            }
        }
    }
    return false;
}

void Pawn::makeMove(const BoardLocation& loc) {
    int dir = color ? 1 : -1;
    BoardLocation toCheck;
    toCheck.file = loc.file;
    toCheck.rank = loc.rank - dir;
    Piece *p = game->getPieceAt(loc.file, loc.rank - dir);
    if (p != nullptr && p->getType() == PieceType::PAWN_TYPE && p->getColor() != color) {
        game->removePieceAt(toCheck);
    }
    Piece::makeMove(loc);
}

location_vector_type Pawn::getLegalMoves() const {
    Logger *l = Logger::getInstance();
    l->output << "Checking legal moves of " << *this << "." << std::endl;
    location_vector_type result;
    int direction = color ? 1 : -1;
    BoardLocation nextLocation;
    nextLocation.file = loc.file;
    nextLocation.rank = loc.rank + direction;
    if (game->currentPlayerInCheck()) {
        // if you are currently in check, you need to move such that you are in check no longer.

    }
    if (game->getPieceAt(nextLocation.file, nextLocation.rank) == nullptr) {
        l->output << "Move to " << nextLocation << " is legal." << std::endl;
        result.push_back(nextLocation);
        int rank = loc.getRealRank();
        if ((rank == 2 && color) || (rank == 7 && !color)) {
            nextLocation.file = loc.file;
            nextLocation.rank = loc.rank + (direction * 2);
            if (game->getPieceAt(nextLocation.file, nextLocation.rank) == nullptr) {
                l->output << "Move to " << nextLocation << " is legal." << std::endl;
                result.push_back(nextLocation);
            }
        }
    }
    Piece *toCapture = nullptr;
    if (loc.file > 0) {
        nextLocation.file = loc.file - 1;
        nextLocation.rank = loc.rank + direction;
        toCapture = game->getPieceAt(nextLocation.file, nextLocation.rank);
        if (toCapture != nullptr) {
            if (toCapture->getColor() != color) {
                l->output << "Capture of " << *toCapture << " is legal." << std::endl;
                result.push_back(nextLocation);
            }
        }
    }
    if (loc.file < 7) {
        nextLocation.file = loc.file + 1;
        nextLocation.rank = loc.rank + direction;
        toCapture = game->getPieceAt(nextLocation.file, nextLocation.rank);
        if (toCapture != nullptr) {
            if (toCapture->getColor() != color) {
                l->output << "Capture of " << *toCapture << " is legal." << std::endl;
                result.push_back(nextLocation);
            }
        }
    }
    if (loc.rank == (color ? 4 : 3)) {
        if (loc.file > 0) {
            toCapture = game->getPieceAt(loc.file - 1, loc.rank);
            if (toCapture != nullptr && toCapture->getType() == PieceType::PAWN_TYPE
                    && toCapture->getColor() != color && toCapture->hasJustMoved()) {
                nextLocation.rank = loc.rank + direction;
                nextLocation.file = loc.file - 1;
                l->output << "Capture of " << *toCapture << " is legal." << std::endl;
                result.push_back(nextLocation);
            }
        }
        if (loc.file < 7) {
            toCapture = game->getPieceAt(loc.file + 1, loc.rank);
            if (toCapture != nullptr && toCapture->getType() == PieceType::PAWN_TYPE
                    && toCapture->getColor() != color && toCapture->hasJustMoved()) {
                nextLocation.rank = loc.rank + direction;
                nextLocation.file = loc.file + 1;
                l->output << "Capture of " << *toCapture << " is legal." << std::endl;
                result.push_back(nextLocation);
            }
        }
    }
    return result;
}

PieceType Pawn::getType() const {
    return PieceType::PAWN_TYPE;
}