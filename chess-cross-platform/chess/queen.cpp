#include <string>
#include <cmath>
#include "queen.h"
#include "piece.h"
#include "square.h"

Queen::Queen(Square* position, std::string color) {
  this->Position = position;
  this->Color = color;
  this->Content = Color == "White" ? "\u2655" : "\u265B";
}
Queen::Queen(){}
Queen::~Queen(){}

bool Queen::IsAvailableMove(Square* target) {
  return ((abs(target->Rank - Position->Rank) == abs(target->File - Position->File))
          || ((target->Rank == Position->Rank && target->File != Position->File)
              || (target->File == Position->File && target->Rank != Position->Rank)));
}

bool Queen::CanCapture(Square* target) {
  return IsAvailableMove(target);
}

void Queen::Move(Square* target) {
  Position->Rank = target->Rank;
  Position->File = target->File;
}

