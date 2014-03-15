/*
Copyright (c) 2014 Johan Burke

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

#include "Chess.hpp"
#include "Pieces.hpp"
#include "Logger.hpp"

using namespace Chess;

Bishop::Bishop(Game* game, const BoardLocation& loc, bool color) : Piece(game, loc, color) {

}

bool Bishop::isCheck(const BoardLocation& loc) const {
    // TODO: implement this!
    return false;
}

location_vector_type Bishop::getLegalMoves() const {
    Logger *l = Logger::getInstance();
    location_vector_type result;
    BoardLocation nextLocation;
    int file = loc.file - 1;
    int rank = loc.rank - 1;
    Piece *p;
    
    // TODO:  refactor refactor refactor refactor
    while (rank >= 0) {
        if (file < 0) {
            break;
        }
        p = game->getPieceAt(file, rank);
        if (p == nullptr) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Move to " << nextLocation << " is legal." << std::endl;
            result.push_back(nextLocation);
        } else if (p->getColor() != color && p->getType() != PieceType::KING_TYPE) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Capture of " << *p << " is legal." << std::endl;
            result.push_back(nextLocation);
            break;
        } else {
            break;
        }
        --file;
        --rank;
    }
    file = loc.file + 1;
    rank = loc.rank - 1;
    while (rank >= 0) {
        if (file > 7) {
            break;
        }
        p = game->getPieceAt(file, rank);
        if (p == nullptr) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Move to " << nextLocation << " is legal." << std::endl;
            result.push_back(nextLocation);
        } else if (p->getColor() != color && p->getType() != PieceType::KING_TYPE) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Capture of " << *p << " is legal." << std::endl;
            result.push_back(nextLocation);
            break;
        } else {
            break;
        }
        ++file;
        --rank;
    }
    file = loc.file - 1;
    rank = loc.rank + 1;
    while (rank <= 7) {
        if (file < 0) {
            break;
        }
        p = game->getPieceAt(file, rank);
        if (p == nullptr) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Move to " << nextLocation << " is legal." << std::endl;
            result.push_back(nextLocation);
        } else if (p->getColor() != color && p->getType() != PieceType::KING_TYPE) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Capture of " << *p << " is legal." << std::endl;
            result.push_back(nextLocation);
            break;
        } else {
            break;
        }
        --file;
        ++rank;
    }
    file = loc.file + 1;
    rank = loc.rank + 1;
    while (rank <= 7) {
        if (file > 7) {
            break;
        }
        p = game->getPieceAt(file, rank);
        if (p == nullptr) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Move to " << nextLocation << " is legal." << std::endl;
            result.push_back(nextLocation);
        } else if (p->getColor() != color && p->getType() != PieceType::KING_TYPE) {
            nextLocation.file = file;
            nextLocation.rank = rank;
            l->output << "Capture of " << *p << " is legal." << std::endl;
            result.push_back(nextLocation);
            break;
        } else {
            break;
        }
        ++file;
        ++rank;
    }
    return result;
}

PieceType Bishop::getType() const {
    return PieceType::BISHOP_TYPE;
}