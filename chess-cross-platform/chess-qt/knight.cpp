#include <string>
#include "knight.h"
#include "square.h"

Knight::Knight(Square* position, std::string color) {
  this->Position = position;
  this->Color = color;
  this->Content = Color == "White" ? "\u2658" : "\u265E";
}
Knight::Knight(){}
Knight::~Knight(){}

bool Knight::IsAvailableMove(Square* target) {
  if ((target->Rank == this->Position->Rank + 2
       || target->Rank == this->Position->Rank - 2)
      && (target->File == this->Position->File + 1
          || target->File == this->Position->File - 1)
      || (target->Rank == this->Position->Rank + 1
          || target->Rank == this->Position->Rank - 1)
      && (target->File == this->Position->File + 2
          || target->File == this->Position->File - 2))
    {
      return true;
    }
  else return false;
}

bool Knight::CanCapture(Square* target) {
  if (IsAvailableMove(target)) return true;
  else return false;
}

void Knight::Move(Square* target) {
  this->Position->Rank = target->Rank;
  this->Position->File = target->File;
}

