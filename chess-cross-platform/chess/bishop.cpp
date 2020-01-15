#include <string>
#include <cmath>
#include "bishop.h"
#include "square.h"

Bishop::Bishop(Square* position, std::string color) {
  this->Position = position;
  this->Color = color;
  this->Content = Color == "White" ? "\u2657" : "\u265D";
}

Bishop::Bishop(){}
Bishop::~Bishop(){}

bool Bishop::IsAvailableMove(Square* target) {
  if (abs(target->Rank - Position->Rank) == abs(target->File - Position->File))
    {
      return true;
    }
  else return false;
}

bool Bishop::CanCapture(Square* target) {
  if (IsAvailableMove(target)) return true;
  else return false;
}

void Bishop::Move(Square* target) {
  this->Position->Rank = target->Rank;
  this->Position->File = target->File;
}

