#ifndef QUEEN_H
#define QUEEN_H

#include <string>
#include "piece.h"

class Square;

class Queen : public Piece {
public:
  Queen(Square*, std::string);
  Queen();
  ~Queen();

  bool IsAvailableMove(Square* target) override;
  bool CanCapture(Square* target) override;
  void Move(Square* target) override;
};

#endif

