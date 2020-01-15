#include <string>
#include <vector>

#include "piece.h"
#include "player.h"
#include "square.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

Player::Player(){}
Player::~Player(){}

Player::Player(std::string color) {
  this->Color = color;
  if (this->Color == "White") {
    this->ActivePieces.push_back(new King(new Square(7,4), color));
    this->ActivePieces.push_back(new Queen(new Square(7,3), color));
    this->ActivePieces.push_back(new Rook(new Square(7,0), color));
    this->ActivePieces.push_back(new Rook(new Square(7,7), color));
    this->ActivePieces.push_back(new Bishop(new Square(7,2), color));
    this->ActivePieces.push_back(new Bishop(new Square(7,5), color));
    this->ActivePieces.push_back(new Knight(new Square(7,1), color));
    this->ActivePieces.push_back(new Knight(new Square(7,6), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,0), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,1), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,2), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,3), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,4), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,5), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,6), color));
    this->ActivePieces.push_back(new Pawn(new Square(6,7), color));
  }
  else {
    this->ActivePieces.push_back(new King(new Square(0,4), color));
    this->ActivePieces.push_back(new Queen(new Square(0,3), color));
    this->ActivePieces.push_back(new Rook(new Square(0,0), color));
    this->ActivePieces.push_back(new Rook(new Square(0,7), color));
    this->ActivePieces.push_back(new Bishop(new Square(0,2), color));
    this->ActivePieces.push_back(new Bishop(new Square(0,5), color));
    this->ActivePieces.push_back(new Knight(new Square(0,1), color));
    this->ActivePieces.push_back(new Knight(new Square(0,6), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,0), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,1), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,2), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,3), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,4), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,5), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,6), color));
    this->ActivePieces.push_back(new Pawn(new Square(1,7), color));
  };

  //store rook and king references to make checking for castles easier
  Rook1 = (Rook*)&ActivePieces[2];
  Rook2 = (Rook*)&ActivePieces[3];
  KingPiece = (King*)&ActivePieces[0];
}



void Player::Castle(Square* target) {
  
if(target->File == 2)
  {
    KingPiece->Position->File = 2;
    Rook1->Position->File = 3;
  }
 else if(target->File == 6)
   {
     KingPiece->Position->File = 6;
     Rook2->Position->File = 5;
   }
  
}

bool Player::IsInCheck() {
  return false;
}

