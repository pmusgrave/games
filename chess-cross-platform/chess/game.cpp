//#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <typeinfo>
#include "board.h"
#include "square.h"
#include "piece.h"
#include "player.h"
#include "game.h"
#include "king.h"
#include "rook.h"

Game::Game(){
  Player Player1("White");
  Player Player2("Black");
  Players[0] = Player1;
  Players[1] = Player2;
  CurrentPlayer = Player1;
  State = "In Progress";
}

bool Game::IsSquareOccupied(Square *target) {
  for (uint i = 0; i < 2; i++) {
      for (uint j = 0; j < this->Players[i].ActivePieces.size(); j++) {
          Piece* piece = this->Players[i].ActivePieces[j];
          if (piece->Position.Rank == target->Rank
              && piece->Position.File == target->File) {
              return true;
          }
      }
  }

  return false;
}



bool Game::IsValidCastle(Piece *selected_piece, Square *target) {
  Square OneLeft = Square(0, selected_piece->Position.File - 1);
  Square *pOneLeft = &OneLeft;
  Square TwoLeft = Square(0, selected_piece->Position.File - 2);
  Square *pTwoLeft = &TwoLeft;
  Square ThreeLeft = Square(0, selected_piece->Position.File - 3);
  Square *pThreeLeft = &ThreeLeft;
  Square OneRight = Square(0, selected_piece->Position.File + 1);
  Square *pOneRight = &OneRight;
  Square TwoRight = Square(0, selected_piece->Position.File + 2);
  Square *pTwoRight = &TwoRight;
  Square ThreeRight = Square(0, selected_piece->Position.File + 3);
  Square *pThreeRight = &ThreeRight;

  if (typeid(*selected_piece) == typeid(King())
  && (target->File - selected_piece->Position.File) == -2
  && target->Rank == selected_piece->Position.Rank
  && (!IsSquareOccupied(pOneLeft)
      && !IsSquareOccupied(pTwoLeft)
      && !IsSquareOccupied(pThreeLeft)))

  {
    King *king = dynamic_cast<King*>(selected_piece);
      if (king->FirstMove && CurrentPlayer.Rook1->FirstMove)
      {
          king->FirstMove = false;
          CurrentPlayer.Rook1->FirstMove = false;
          return true;
      }
  }
  else if (typeid(*selected_piece) == typeid(new King())
  && (target->File - selected_piece->Position.File) == 2
  && target->Rank == selected_piece->Position.Rank
  && (!IsSquareOccupied(pOneRight)
      && !IsSquareOccupied(pTwoRight)))
  {
    King *king = dynamic_cast<King*>(selected_piece);
      if (king->FirstMove && CurrentPlayer.Rook2->FirstMove)
      {
          king->FirstMove = false;
          CurrentPlayer.Rook2->FirstMove = false;
          return true;
      }
  }
  else if (typeid(*selected_piece) == typeid(new Rook(new Square(0, 0), "White"))
  && (target->File - selected_piece->Position.File) == 3
  && target->Rank == selected_piece->Position.Rank
  && (!IsSquareOccupied(pOneRight))
        && !IsSquareOccupied(pTwoRight)
        && !IsSquareOccupied(pThreeRight))
  {
      if (CurrentPlayer.KingPiece->FirstMove && CurrentPlayer.Rook1->FirstMove)
      {
          CurrentPlayer.KingPiece->FirstMove = false;
          CurrentPlayer.Rook1->FirstMove = false;
          return true;
      }
  }
  else if (typeid(*selected_piece) == typeid(new Rook(new Square(0, 0), "White"))
  && (target->File - selected_piece->Position.File) == -2
  && target->Rank == selected_piece->Position.Rank
        && (!IsSquareOccupied(pOneLeft)
        && !IsSquareOccupied(pTwoLeft)))
  {
      if (CurrentPlayer.KingPiece->FirstMove && CurrentPlayer.Rook2->FirstMove)
      {
          CurrentPlayer.KingPiece->FirstMove = false;
          CurrentPlayer.Rook2->FirstMove = false;
          return true;
      }
  }

  return false;
}

bool Game::IsValidMove(Piece *selected_piece, Square *target) {
  if (!this->CurrentPlayer.IsInCheck() 
  && (!IsSquareOccupied(target) && selected_piece->IsAvailableMove(target)))
  {
      return true;
  }
  else return false;
}

bool Game::IsValidCapture(Piece *selected_piece, Square *target) {
  if (IsSquareOccupied(target) && selected_piece->CanCapture(target))
  {
      return true;
  }
  else return false; 
}

void Game::SwitchPlayers() {
    CurrentPlayer = (&CurrentPlayer == &Players[0]) ? Players[1] : Players[0];
}

/*void Game::ResetBoard(Ui::MainWindow *& ui){
  ui->square_00->setText(WHITE_ROOK);
  ui->square_01->setText(WHITE_KNIGHT);
  ui->square_02->setText(WHITE_BISHOP);
  ui->square_03->setText(WHITE_QUEEN);
  ui->square_04->setText(WHITE_KING);
  ui->square_05->setText(WHITE_BISHOP);
  ui->square_06->setText(WHITE_KNIGHT);
  ui->square_07->setText(WHITE_ROOK);
  ui->square_10->setText(WHITE_PAWN);
  ui->square_11->setText(WHITE_PAWN);
  ui->square_12->setText(WHITE_PAWN);
  ui->square_13->setText(WHITE_PAWN);
  ui->square_14->setText(WHITE_PAWN);
  ui->square_15->setText(WHITE_PAWN);
  ui->square_16->setText(WHITE_PAWN);
  ui->square_17->setText(WHITE_PAWN);

  ui->square_70->setText(BLACK_ROOK);
  ui->square_71->setText(BLACK_KNIGHT);
  ui->square_72->setText(BLACK_BISHOP);
  ui->square_73->setText(BLACK_QUEEN);
  ui->square_74->setText(BLACK_KING);
  ui->square_75->setText(BLACK_BISHOP);
  ui->square_76->setText(BLACK_KNIGHT);
  ui->square_77->setText(BLACK_ROOK);
  ui->square_60->setText(BLACK_PAWN);
  ui->square_61->setText(BLACK_PAWN);
  ui->square_62->setText(BLACK_PAWN);
  ui->square_63->setText(BLACK_PAWN);
  ui->square_64->setText(BLACK_PAWN);
  ui->square_65->setText(BLACK_PAWN);
  ui->square_66->setText(BLACK_PAWN);
  ui->square_67->setText(BLACK_PAWN);
}
*/
