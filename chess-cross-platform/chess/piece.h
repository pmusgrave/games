#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "square.h"

/*#define WHITE_KING QChar(0x2654)
#define WHITE_QUEEN QChar(0x2655)
#define WHITE_ROOK QChar(0x2656)
#define WHITE_BISHOP QChar(0x2657)
#define WHITE_KNIGHT QChar(0x2658)
#define WHITE_PAWN QChar(0x2659)
#define BLACK_KING QChar(0x265A)
#define BLACK_QUEEN QChar(0x265B)
#define BLACK_ROOK QChar(0x265C)
#define BLACK_BISHOP QChar(0x265D)
#define BLACK_KNIGHT QChar(0x265E)
#define BLACK_PAWN QChar(0x265F)
*/

class Piece {
public:
    Square* Position;
    std::string Color;
    std::string Content;
    virtual void Move(Square*) = 0;
    virtual bool IsAvailableMove(Square*) = 0;
    virtual bool CanCapture(Square*) = 0;

    Piece(){}
    virtual ~Piece(){}
};

#endif
