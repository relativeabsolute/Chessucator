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
File:   Rook.cpp
Author: johan
Created on January 1, 2014, 4:06 PM
 */

#include "Chess.hpp"
#include "Pieces.hpp"
#include "Logger.hpp"

using namespace Chess;

Rook::Rook(Game* game, const BoardLocation& loc, bool color) : Piece(game, loc, color) {
}

bool Rook::isCheck(const BoardLocation& loc) const {
    // TODO: implement this
    return false;
}

location_vector_type Rook::getLegalMoves() const {
    Logger *l = Logger::getInstance();
    l->output << "Checking legal moves of " << *this << std::endl;
    location_vector_type result;
    location_vector_type temp = checkRank(true);
    for (location_iterator_type it = temp.begin(); it != temp.end(); ++it) {
        result.push_back(*it);
    }
    temp = checkRank(false);
    for (location_iterator_type it = temp.begin(); it != temp.end(); ++it) {
        result.push_back(*it);
    }
    temp = checkFile(true);
    for (location_iterator_type it = temp.begin(); it != temp.end(); ++it) {
        result.push_back(*it);
    }
    temp = checkFile(false);
    for (location_iterator_type it = temp.begin(); it != temp.end(); ++it) {
        result.push_back(*it);
    }
    return result;
}

location_vector_type Rook::checkRank(bool dir) const {
    Logger *l = Logger::getInstance();
    BoardLocation nextLocation;
    nextLocation.file = loc.file;
    Piece *p;
    location_vector_type result;
    int currRank = loc.rank;
    int minRank = 0;
    int maxRank = 7;
    int step = dir ? 1 : -1;
    while (true) {
        currRank += step;
        if (currRank < minRank) {
            break;
        } else if (currRank > maxRank) {
            break;
        }
        p = game->getPieceAt(loc.file, currRank);
        if (p == nullptr) {
            nextLocation.rank = currRank;
            l->output << "Move to " << nextLocation << " is legal." << std::endl;
            result.push_back(nextLocation);
        } else if (p->getColor() != color && p->getType() != PieceType::KING_TYPE) {
            nextLocation.rank = currRank;
            l->output << "Capture of " << *p << " is legal." << std::endl;
            result.push_back(nextLocation);
            break;
        } else {
            break;
        }
    }
    return result;
}

location_vector_type Rook::checkFile(bool dir) const {
    Logger *l = Logger::getInstance();
    BoardLocation nextLocation;
    nextLocation.rank = loc.rank;
    Piece *p;
    location_vector_type result;
    int currFile = loc.file;
    int minFile = 0;
    int maxFile = 7;
    int step = dir ? 1 : -1;
    while (true) {
        currFile += step;
        if (currFile < minFile) {
            break;
        } else if (currFile > maxFile) {
            break;
        }
        p = game->getPieceAt(currFile, loc.rank);
        if (p == nullptr) {
            nextLocation.file = currFile;
            l->output << "Move to " << nextLocation << " is legal." << std::endl;
            result.push_back(nextLocation);
        } else if (p->getColor() != color && p->getType() != PieceType::KING_TYPE) {
            nextLocation.file = currFile;
            l->output << "Capture of " << *p << " is legal." << std::endl;
            result.push_back(nextLocation);
            break;
        } else {
            break;
        }
    }
    return result;
}

PieceType Rook::getType() const {
    return PieceType::ROOK_TYPE;
}