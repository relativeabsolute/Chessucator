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
File:   Pieces.hpp
Author: johan
Created on November 2, 2013, 4:08 PM
 */

#include "Chess.hpp"

namespace Chess {

    class Pawn : public Piece {
    public:
        Pawn(Game *game, const BoardLocation &loc, bool color);
        location_vector_type getLegalMoves() const;
        PieceType getType() const;
        bool isCheck(const BoardLocation &loc) const;
        virtual void makeMove(const BoardLocation& loc);

    };

    class Knight : public Piece {
    public:
        Knight(Game *game, const BoardLocation &loc, bool color);
        location_vector_type getLegalMoves() const;
        PieceType getType() const;
        bool isCheck(const BoardLocation &loc) const;
    };

    class Bishop : public Piece {
    public:
        Bishop(Game *game, const BoardLocation &loc, bool color);
        location_vector_type getLegalMoves() const;
        PieceType getType() const;
        bool isCheck(const BoardLocation &loc) const;
    };
    
    class Rook : public Piece {
    public:
        Rook(Game *game, const BoardLocation &loc, bool color);
        location_vector_type getLegalMoves() const;
        PieceType getType() const;
        bool isCheck(const BoardLocation &loc) const;
    private:
        location_vector_type checkRank(bool dir) const;
        location_vector_type checkFile(bool dir) const;
    };
    
    class Queen : public Piece {
    public:
        Queen(Game *game, const BoardLocation &loc, bool color);
        location_vector_type getLegalMoves() const;
        PieceType getType() const;
        bool isCheck(const BoardLocation &loc) const;
    private:
        location_vector_type checkRank(bool dir) const;
        location_vector_type checkFile(bool dir) const;
        location_vector_type checkDiagonals() const;
    };
}