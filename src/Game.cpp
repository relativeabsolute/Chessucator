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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GraphicsUtils.hpp"
#include "Logger.hpp"
#include "Pieces.hpp"
#include <sstream>
#include <memory>

using namespace Chess;

location_vector_type BoardLocation::getAdjacentLocations() const {
    location_vector_type result;
    BoardLocation tmp;
    tmp.file = file - 1;
    tmp.rank = rank - 1;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    tmp.file = file - 1;
    tmp.rank = rank;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    tmp.file = file - 1;
    tmp.rank = rank + 1;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    tmp.file = file;
    tmp.rank = rank - 1;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    tmp.file = file;
    tmp.rank = rank + 1;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    tmp.file = file + 1;
    tmp.rank = rank - 1;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    tmp.file = file + 1;
    tmp.rank = rank;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    tmp.file = file + 1;
    tmp.rank = rank + 1;
    if (tmp.inBounds()) {
        result.push_back(tmp);
    }
    return result;
}

bool BoardLocation::operator==(const BoardLocation &other) const {
    return file == other.file && rank == other.rank;
}

bool BoardLocation::inBounds() const {
    return file >= 0 && rank >= 0 && file <= 7 && rank <= 7;
}

static const char *pieceTypeNames[] = {
    "pawn", "knight", "bishop", "rook", "queen", "king"
};

const char *Chess::getPieceTypeName(PieceType type) {
    return pieceTypeNames[(size_t) type];
}

BoardLocation::BoardLocation()
: occupyingPiece(nullptr), file(0), rank(0), highlighted(false) {
}

size_t BoardLocation::getRealRank() const {
    return rank + 1;
}

std::ostream &Chess::operator <<(std::ostream& stream, const Piece& p) {
    stream << (p.color ? "White " : "Black ") << getPieceTypeName(p.getType()) << " at " <<
            p.loc;
    return stream;
}

size_t BoardLocation::boardCoordToWindowYCoord(size_t boardCoord) {
    return (squareSize * 7) - (boardCoord * squareSize);
}

size_t BoardLocation::windowYCoordToBoardCoord(size_t windowCoord) {
    return ((squareSize * 8) - windowCoord) / squareSize;
}

std::string BoardLocation::asString() const {
    std::stringstream str;
    str << (char) ('a' + file);
    str << (rank + 1) << " [file = " << file << " rank = " << rank << "]";
    return str.str();
}

std::ostream &Chess::operator <<(std::ostream& stream, const BoardLocation& loc) {
    stream << loc.asString();
    return stream;
}

std::ostream &Chess::operator <<(std::ostream& stream, const Game& p) {
    BoardLocation loc;
    int arrayLoc;
    for (int rank = 0; rank < 8; ++rank) {
        for (int file = 0; file < 8; ++file) {
            arrayLoc = p.getArrayLocation(file, rank);
            loc = p.locations[arrayLoc];
            stream << "Location at index " << arrayLoc << " is ";
            stream << loc;
            if (loc.occupyingPiece != nullptr) {
                stream << " is occupied by " << *loc.occupyingPiece << ".";
            } else {
                stream << " is not occupied.";
            }
            stream << std::endl;
            if (loc.highlighted) {
                stream << loc << " is highlighted." << std::endl;
            }
        }
    }
    return stream;
}

void Game::loadPiece(const char *filename, PieceType type, bool color) {
    // SDL_img refuses to play nice with std::string
    Logger *l = Logger::getInstance();
    SDL_Texture *tmp = IMG_LoadTexture(renderer, filename);
    if (tmp != nullptr) {
        l->output << filename << " loaded successfully." << std::endl;
        pieceTextures[(size_t)type][(size_t)color] = tmp;
    } else {
        pieceTextures[(size_t)type][(size_t)color] = nullptr;
        l->output << "Could not load " << filename << std::endl;
        l->output << "Error message: " << IMG_GetError() << std::endl;
    }
}

void Game::loadPieces() {
    loadPiece("Chess Set - Pawn Black.png", PieceType::PAWN_TYPE, false);
    loadPiece("Chess Set - Pawn White.png", PieceType::PAWN_TYPE, true);
    loadPiece("Chess Set - Knight Black.png", PieceType::KNIGHT_TYPE, false);
    loadPiece("Chess Set - Knight White.png", PieceType::KNIGHT_TYPE, true);
    loadPiece("Chess Set - Bishop Black.png", PieceType::BISHOP_TYPE, false);
    loadPiece("Chess Set - Bishop White.png", PieceType::BISHOP_TYPE, true);
    loadPiece("Chess Set - Rook Black.png", PieceType::ROOK_TYPE, false);
    loadPiece("Chess Set - Rook White.png", PieceType::ROOK_TYPE, true);
    loadPiece("Chess Set - Queen Black.png", PieceType::QUEEN_TYPE, false);
    loadPiece("Chess Set - Queen White.png", PieceType::QUEEN_TYPE, true);
    loadPiece("Chess Set - King Black.png", PieceType::KING_TYPE, false);
    loadPiece("Chess Set - King White.png", PieceType::KING_TYPE, true);
}

Game::Game(SDL_Renderer *r)
: needsUpdate(true), renderer(r), moveIndex(0), justMoved(nullptr) {
    loadPieces();
    size_t loc;
    for (size_t file = 0; file < 8; ++file) {
        for (size_t rank = 0; rank < 8; ++rank) {
            loc = getArrayLocation(file, rank);
            locations[loc].file = file;
            locations[loc].rank = rank;
            locations[loc].highlighted = false;
            locations[loc].occupyingPiece = nullptr;
        }
    }
    BoardLocation l;
    highlightColor.r = 0;
    highlightColor.g = 122;
    highlightColor.b = 0;
    for (size_t i = 0; i < numPieces; ++i) {
        pieces[i] = nullptr;
    }
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            l.file = i;
            l.rank = j;
            updateLocations.push_back(l);
        }
    }
}

Game::~Game() {
    for (size_t i = 0; i < numPieces; ++i) {
        if (pieces[i] != nullptr) {
            delete pieces[i];
            pieces[i] = nullptr;
        }
    }
}

void Game::addPiece(Piece* p, size_t index) {
    pieces[index] = p;
    BoardLocation l = p->getLocation();
    locations[getArrayLocation(l.file, l.rank)].occupyingPiece = p;
    updatePieces.push_back(p);
}

BoardLocation Game::getLocation(int file, int rank) const {
    return locations[getArrayLocation(file, rank)];
}

int Game::getArrayLocation(int file, int rank) const {
    if (file < 0 || rank < 0) {
        return -1;
    }
    return (file * 8) +rank;
}

std::vector<BoardLocation> Game::getOccupiedLocations() const {
    // TODO:  finish this
    std::vector<BoardLocation> result;
    return result;
}

Piece *Game::getPieceAt(const BoardLocation &loc) const {
    return getPieceAt(loc.file, loc.rank);
}

Piece *Game::getPieceAt(int file, int rank) const {
    if (file < 0 || rank < 0 || file > 7 || rank > 7) {
        return nullptr;
    }
    return locations[getArrayLocation(file, rank)].occupyingPiece;
}

bool Game::currentPlayerInCheck() const {
    if (moveIndex > 0) {
        return moves[moveIndex - 1]->check;
    }
    return false; // it's impossible to get in check on the very first move
}

void Game::removePieceAt(const BoardLocation& newLoc) {
    size_t loc = getArrayLocation(newLoc.file, newLoc.rank);
    locations[loc].occupyingPiece = nullptr;
    updateLocations.push_back(locations[loc]);
}

void Game::makeMove(Piece *piece, const BoardLocation &newLocation) {
    Logger *l = Logger::getInstance();
    l->output << "makeMove called for " << *piece << " to move to " << newLocation << std::endl;
    size_t oldLoc = getArrayLocation(piece->getLocation().file, piece->getLocation().rank);
    l->output << "oldLoc index is " << oldLoc << "." << std::endl;
    l->output << "oldLoc is " << locations[oldLoc] << "." << std::endl;
    l->output << "newLocation is " << newLocation << "." << std::endl;
    size_t newLoc = getArrayLocation(newLocation.file, newLocation.rank);
    l->output << "newLoc index is " << newLoc << "." << std::endl;
    l->output << "newLoc is " << locations[newLoc] << "." << std::endl;

    // TODO: handle captures, etc...
    piece->setLocation(newLocation);
    locations[newLoc].occupyingPiece = locations[oldLoc].occupyingPiece;
    locations[newLoc].occupyingPiece->setLocation(newLocation);

    locations[oldLoc].occupyingPiece = nullptr;

    updateHighlightVector();
    updateLocations.push_back(locations[oldLoc]);

    if (justMoved != nullptr) {
        justMoved->justMoved = false;
    }
    justMoved = piece;
    justMoved->justMoved = true;
    justMoved->moved = true;

    updatePieces.push_back(piece);
}

void Game::clearHighlights() {
    updateHighlightVector();
}

void Game::updateHighlightVector() {
    BoardLocation loc;
    Piece *p;
    size_t arrayLoc;
    if (!highlightedLocations.empty()) {
        for (BoardLocation loc : highlightedLocations) {
            arrayLoc = getArrayLocation(loc.file, loc.rank);
            locations[arrayLoc].highlighted = false;
            loc.highlighted = false;
            p = locations[arrayLoc].occupyingPiece;
            if (p != nullptr) {
                updatePieces.push_back(p);
            }
            updateLocations.push_back(loc);
        }
        highlightedLocations.clear();
    }
}

void Game::highlightLegalMoves(const Piece* piece) {
    if (piece != nullptr) {
        Logger *l = Logger::getInstance();
        l->output << "Highlighting legal moves of " << *piece << std::endl;
        location_vector_type legalMoves = piece->getLegalMoves();
        BoardLocation loc;
        updateHighlightVector();
        for (BoardLocation loc : legalMoves) {
            locations[getArrayLocation(loc.file, loc.rank)].highlighted = true;
            loc.highlighted = true;
            updateLocations.push_back(loc);
            highlightedLocations.push_back(loc);
        }
    }
}

void Game::renderLocations() {
    SDL_Rect rect;
    rect.w = squareSize;
    rect.h = squareSize;
    BoardLocation loc;
    for (BoardLocation loc : updateLocations) {
        rect.x = loc.file * squareSize;
        rect.y = BoardLocation::boardCoordToWindowYCoord(loc.rank);
        if (loc.highlighted) {
            SDL_SetRenderDrawColor(renderer, highlightColor.r, highlightColor.g,
                    highlightColor.b, highlightColor.a);
            SDL_RenderDrawRectStroke(renderer, &rect, 5);
        } else {
            if (loc.file % 2 == loc.rank % 2) {
                // white
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            } else {
                // black
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    updateLocations.clear();
}

void Game::renderPieces() {
    SDL_Rect rect;
    rect.w = squareSize;
    rect.h = squareSize;
    for (Piece *p : updatePieces) {
        if (p != nullptr) {
            rect.x = p->getLocation().file * squareSize;
            rect.y = BoardLocation::boardCoordToWindowYCoord(p->getLocation().rank);
            SDL_RenderCopy(renderer, pieceTextures[(size_t) p->getType()][(size_t) p->getColor()],
                nullptr, &rect);
        }
    }
    updatePieces.clear();
}

void Game::render() {
    if (updateLocations.size() != 0) {
        renderLocations();
    }
    if (updatePieces.size() != 0) {
        renderPieces();
    }
}