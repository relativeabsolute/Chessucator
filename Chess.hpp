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
File:   Chess.hpp
Author: johan
Created on November 2, 2013, 4:04 PM
 */

#ifndef CHESS_HPP
#define CHESS_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>

#define SQUARE_WIDTH 64
#define NUM_PIECES 32

namespace Chess {
    class Piece;
    using pieces_vector_type = std::vector<Piece*>;
    typedef pieces_vector_type::iterator pieces_iterator_type;

    struct BoardLocation {
        size_t file;
        size_t rank;
        Piece *occupyingPiece;
        bool highlighted;
        
        size_t getRealRank() const;
        
        BoardLocation();
        
        bool inBounds() const;

        /**
         * Only check if the rank and file are the same.
         */
        bool operator==(const BoardLocation &other) const;
        
        static size_t boardCoordToWindowYCoord(size_t boardCoord);
        static size_t windowYCoordToBoardCoord(size_t windowCoord);
        
        std::string asString() const;
        
        friend std::ostream &operator<<(std::ostream &stream, const BoardLocation &loc);
    };
    
    std::ostream &operator<<(std::ostream &stream, const BoardLocation &loc);
    
    typedef std::vector<BoardLocation> location_vector_type;
    typedef location_vector_type::iterator location_iterator_type;

    struct Move {
        bool capture;
        bool check;
        bool promotion;
        BoardLocation prevLocation;
        BoardLocation newLocation;
        std::string notation;
    };
    
    typedef std::vector<Move*> move_vector_type;
    typedef move_vector_type::iterator move_iterator_type;

    enum class PieceType {
        PAWN_TYPE = 0, KNIGHT_TYPE, BISHOP_TYPE, ROOK_TYPE, QUEEN_TYPE, KING_TYPE, NUM_PIECE_TYPES
    };
    const char *getPieceTypeName(PieceType type);

    class Game {
    public:
        Game(SDL_Renderer *r);
        virtual ~Game();
        
        std::vector<BoardLocation> getOccupiedLocations() const;
        BoardLocation getLocation(int file, int rank) const;
        Piece *getPieceAt(int file, int rank) const;
        bool currentPlayerInCheck() const;
        void makeMove(Piece *piece, const BoardLocation &newLoc);        
        void removePieceAt(const BoardLocation &newLoc);
        
        /**
         * Highlight the given piece's legal moves, one of which can then be clicked
         * to make that move.  Calls Piece::getLegalMoves().
         * @param piece The piece to check the moves of.
         */
        void highlightLegalMoves(const Piece *piece);
        void render();
        void clearHighlights();
        
        virtual void initializeBoard() = 0;
        
        friend Piece;
        friend std::ostream &operator<<(std::ostream &stream, const Game &p);
    protected:
        /**
         * Flatten the given parameters into their index in the array.
         * @param file The file of the board location.
         * @param rank The rank of the board location.
         * @return The array index of the given board location.
         */
        int getArrayLocation(int file, int rank) const;
        BoardLocation locations[64];
        std::vector<Move*> moves;
        size_t moveIndex;
        void addPiece(Piece *p, size_t index);
        void updateHighlightVector();
        void loadPieces();

        /*
        This array has a very specific order:
        First are the 8 white pawns and 8 black pawns.  Each set of 8 is ordered from the 'a' file to the 'g' file.
        Next are the white knights and black knights, bishops, rooks, queens, and finally kings.
         */
        Piece *pieces[32];

        void renderLocations();
        void renderPieces();
        
        bool needsUpdate;
        location_vector_type updateLocations;
        location_vector_type highlightedLocations;
        pieces_vector_type updatePieces;
        SDL_Texture *pieceTextures[(size_t)PieceType::NUM_PIECE_TYPES][2];
        SDL_Renderer *renderer;
        Piece *justMoved;
        SDL_Color highlightColor;
    };
    
    std::ostream &operator<<(std::ostream &stream, const Game &p);

    class Piece {
    public:
        /**
         * Construct a new chess piece.
         * \param game The game this piece is a part of.
         * \param location The location at which this piece will be placed.
         * \param color The color of the piece.  True for white, false for black
         */
        Piece(Game *game, const BoardLocation &location, bool color);
        
        virtual ~Piece();

        /**
         * Get the moves this piece can make at any given time.  Overriden by different classes for the different types of pieces.
         * \return A list of moves this piece can make legally.
         */
        virtual location_vector_type getLegalMoves() const = 0;

        /**
         * Get the type of this piece.
         */
        virtual PieceType getType() const = 0;
        
        virtual void makeMove(const BoardLocation &loc);

        BoardLocation getLocation() const;
        void setLocation(const BoardLocation &loc);
        
        bool getColor() const;
        bool hasBeenCaptured() const;
        
        bool hasJustMoved() const;
        bool hasMoved() const;

        void setCaptured(bool nowCaptured);
        
        friend std::ostream &operator<<(std::ostream &stream, const Piece &p);
        friend Game;
    protected:
        virtual bool isCheck(const BoardLocation &loc) const = 0;

        bool moved, justMoved;
        Game *game;
        BoardLocation loc;
        bool color;
        bool captured;
    };
    
    std::ostream &operator<<(std::ostream &stream, const Piece &p);
}

#endif