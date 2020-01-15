#include <string>
#include "rook.h"
#include "square.h"

Rook::Rook(Square* position, std::string color) {
  this->Position = position;
  this->Color = color;
  this->Content = Color == "White" ? "\u2656" : "\u265C";
  this->FirstMove = true;
}

Rook::~Rook(){}

bool Rook::IsAvailableMove(Square* target) {
  if (this->FirstMove)
    {
      return (target->Rank == Position->Rank && target->File != Position->File)
        || (target->File == Position->File && target->Rank != Position->Rank);
    }
  else
    {
      return (target->Rank == Position->Rank && target->File != Position->File)
        || (target->File == Position->File && target->Rank != Position->Rank);
    }
}

bool Rook::CanCapture(Square* target) {
  return IsAvailableMove(target);
}

void Rook::Move(Square* target) {
  Position->Rank = target->Rank;
  Position->File = target->File;
}
