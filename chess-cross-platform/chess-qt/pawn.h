#ifndef PAWN_H
#define PAWN_H

#include <string>
#include "piece.h"
#include "square.h"

class Pawn : public Piece {
public:
  Pawn(Square*, std::string);
  Pawn();
  ~Pawn();

  int DirectionMultiplier;
  bool FirstMove;

  bool IsAvailableMove(Square* target) override;
  bool CanCapture(Square* target) override;
  void Move(Square* target) override;
};

#endif

