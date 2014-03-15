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

Knight::Knight(Game* game, const BoardLocation& loc, bool color)
: Piece(game, loc, color) {
}

bool Knight::isCheck(const BoardLocation& loc) const {
    return false;
}

location_vector_type Knight::getLegalMoves() const {
    location_vector_type result;
    BoardLocation nextLoc;
    Piece *p;
    Logger *l = Logger::getInstance();
    for (int deltaFile = -2; deltaFile < 3; ++deltaFile) {
        if (deltaFile == 0) {
            continue;
        }
        for (int deltaRank = -2; deltaRank < 3; ++deltaRank) {
            if (deltaRank == 0 || abs(deltaRank) == abs(deltaFile)) {
                continue;
            }
            nextLoc.file = loc.file + deltaFile;
            nextLoc.rank = loc.rank + deltaRank;
            if (nextLoc.inBounds()) {
                p = game->getPieceAt(nextLoc.file, nextLoc.rank);
                if (p == nullptr) {
                    l->output << "Move to " << nextLoc << " is legal." << std::endl;
                    result.push_back(nextLoc);
                } else if (p->getColor() != color) {
                    l->output << "Capture of " << *p << " is legal." << std::endl;
                    result.push_back(nextLoc);
                }
            }
        }
    }
    return result;
}

PieceType Knight::getType() const {
    return PieceType::KNIGHT_TYPE;
}