#include <string>
#include <cmath>
#include "piece.h"
#include "king.h"
#include "square.h"

King::King(Square* position, std::string color) {
  Position = position;
  Color = color;
  Content = Color == "White" ? "\u2654" : "\u265A";
  FirstMove = true;
}

King::King(){}
King::~King(){}

bool King::IsAvailableMove(Square* target) {
  if (FirstMove) {
    return (target->Rank == Position->Rank && abs(target->File - Position->File) == 1)
      || (target->File == Position->File && abs(target->Rank - Position->Rank) == 1)
      || (abs(target->File - Position->File) == 1 && abs(target->Rank - Position->Rank) == 1)
      || (abs(target->Rank - Position->Rank) == 1 && abs(target->File - Position->File) == 1)
      || (abs(target->File - Position->File) == 2) && target->Rank == Position->Rank;
  }
  else return (target->Rank == Position->Rank && abs(target->File - Position->File) == 1)
       || (target->File == Position->File && abs(target->Rank - Position->Rank) == 1)
       || (abs(target->File - Position->File) == 1 && abs(target->Rank - Position->Rank) == 1)
       || (abs(target->Rank - Position->Rank) == 1 && abs(target->File - Position->File) == 1);
  }

bool King::CanCapture(Square* target) {
  if (IsAvailableMove(target)) return true;
  else return false;
}

void King::Move(Square* target) {
  Position->Rank = target->Rank;
  Position->File = target->File;
}

