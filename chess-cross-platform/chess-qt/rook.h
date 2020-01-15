#ifndef ROOK_H
#define ROOK_H

#include <string>
#include "square.h"
#include "piece.h"

class Rook : public Piece {
public:
  Rook(Square*, std::string);
  ~Rook();

  bool FirstMove;

  bool IsAvailableMove(Square* target) override;
  bool CanCapture(Square* target) override;
  void Move(Square* target) override;
};

#endif

