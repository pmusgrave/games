#ifndef KING_H
#define KING_H

#include <string>
#include "piece.h"
#include "square.h"

class King : public Piece {
public:
  King(Square*, std::string);
  King();
  ~King();

  bool FirstMove;

  bool IsAvailableMove(Square*) override;
  bool CanCapture(Square*) override;
  void Move(Square*) override;
};

#endif

