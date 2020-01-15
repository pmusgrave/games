#include <string>
#include "pawn.h"
#include "square.h"

Pawn::Pawn(Square* position, std::string color) {
  this->Position = position;
  this->Color = color;
  this->Content = Color == "White" ? "\u2659": "\u265F";
  this->DirectionMultiplier = Color == "White" ? -1 : 1;
  this->FirstMove = true;
}

Pawn::Pawn(){}
Pawn::~Pawn(){}

bool Pawn::IsAvailableMove(Square* target) {
  if (this->FirstMove)
    {
      if((target->Rank == Position->Rank + DirectionMultiplier
          || target->Rank == Position->Rank + 2 * DirectionMultiplier)
         && target->File == Position->File)
        {
          return true;
        }
    }
  else if (target->Rank == Position->Rank + DirectionMultiplier 
           && target->File == Position->File)
    {
      return true;
    }

  return false;
}

bool Pawn::CanCapture(Square* target) {
  if (FirstMove)
    {
      if ((target->Rank == Position->Rank + DirectionMultiplier
           || target->Rank == Position->Rank + 2 * DirectionMultiplier)
          && (target->File == Position->File + 1 
              || target->File == Position->File - 1))
        {
          return true;
        }
    }
  else if (target->Rank == Position->Rank + DirectionMultiplier
           && (target->File == Position->File + 1
               || target->File == Position->File - 1))
    {
      return true;
    }

  return false;
}

void Pawn::Move(Square* target) {
  if (FirstMove)
    {
      FirstMove = false;
    }
  Position->Rank = target->Rank;
  Position->File = target->File;
}

