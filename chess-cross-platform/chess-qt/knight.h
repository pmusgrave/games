#ifndef KNIGHT_H
#define KNIGHT_H

#include <string>
#include "piece.h"
#include "square.h"

class Knight : public Piece {
public:
  Knight(Square*, std::string);
  Knight();
  ~Knight();

  bool IsAvailableMove(Square* target) override;
  bool CanCapture(Square* target) override;
  void Move(Square* target) override;
};

#endif

