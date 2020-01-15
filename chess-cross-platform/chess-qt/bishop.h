#ifndef BISHOP_H
#define BISHOP_H

#include <string>
#include "piece.h"
#include "square.h"

class Bishop : public Piece {
public:
  Bishop(Square*, std::string);
  Bishop();
  ~Bishop();

  bool IsAvailableMove(Square* target) override;
  bool CanCapture(Square* target) override;
  void Move(Square* target) override;
};

#endif

