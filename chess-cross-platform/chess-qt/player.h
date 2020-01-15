#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "piece.h"
#include "square.h"
#include "king.h"
#include "rook.h"


class Player {
public:
  Player(std::string);
  Player();
  ~Player();

  std::string Color;
  std::vector<Piece*> ActivePieces;
  std::vector<Piece*> CapturedPieces;
  Piece* SelectedPiece;
  King* KingPiece;
  Rook* Rook1;
  Rook* Rook2;

  void Castle(Square *target);
  bool IsInCheck();
};

#endif
