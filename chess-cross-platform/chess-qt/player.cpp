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
  std::vector<Piece*> ActivePieces;
  this->Color = color;
  if (this->Color == "White") {
    Square current_square(7,4);
    King k(&current_square, color);
    this->ActivePieces.push_back(&k);

    current_square.File = 3;
    Queen q(&current_square, color);
    this->ActivePieces.push_back(&q);

    current_square.File = 0;
    Rook r(&current_square, color);
    this->ActivePieces.push_back(&r);

    current_square.File = 7;
    Rook r2(&current_square, color);
    this->ActivePieces.push_back(&r2);

    current_square.File = 2;
    Bishop b1(&current_square, color);
    this->ActivePieces.push_back(&b1);

    current_square.File = 5;
    Bishop b2(&current_square, color);
    this->ActivePieces.push_back(&b2);

    current_square.File = 1;
    Knight kn1(&current_square, color);
    this->ActivePieces.push_back(&kn1);

    current_square.File = 6;
    Knight kn2(&current_square, color);
    this->ActivePieces.push_back(&kn2);

    current_square.Rank = 6;
    current_square.File = 0;
    Pawn p1(&current_square, color);
    this->ActivePieces.push_back(&p1);

    current_square.File = 1;
    Pawn p2(&current_square, color);
    this->ActivePieces.push_back(&p2);

    current_square.File = 2;
    Pawn p3(&current_square, color);
    this->ActivePieces.push_back(&p3);

    current_square.File = 3;
    Pawn p4(&current_square, color);
    this->ActivePieces.push_back(&p4);

    current_square.File = 4;
    Pawn p5(&current_square, color);
    this->ActivePieces.push_back(&p5);

    current_square.File = 5;
    Pawn p6(&current_square, color);
    this->ActivePieces.push_back(&p6);

    current_square.File = 6;
    Pawn p7(&current_square, color);
    this->ActivePieces.push_back(&p7);

    current_square.File = 7;
    Pawn p8(&current_square, color);
    this->ActivePieces.push_back(&p8);
  }
  else {
    std::vector<Piece*> ActivePieces;
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

