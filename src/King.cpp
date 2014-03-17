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

King::King(Game *game, const BoardLocation &location, bool color) : Piece(game, location, color) {
}

bool King::isCheck(const BoardLocation &location) const {
    return false;
}

location_vector_type King::getLegalMoves() const {
    Logger *logger = Logger::getInstance();
    logger->output << "Checking legal moves of " << *this << "." << std::endl;
    location_vector_type result;
    location_vector_type adjacent = loc.getAdjacentLocations();
    Piece *toCapture = nullptr;
    for (auto l : adjacent) {
        toCapture = game->getPieceAt(l);
        if (toCapture != nullptr) {
            if (toCapture->getColor() != color) {
                logger->output << "Capture of " << *toCapture << " is legal." << std::endl;
                result.push_back(l);
            }
        } else {
            logger->output << "Move to " << l << " is legal." << std::endl;
            result.push_back(l);
        }
    }
    return result;
}

PieceType King::getType() const {
    return PieceType::KING_TYPE;
}