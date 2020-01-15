#include <vector>
#include "board.h"
#include "game.h"

Board::Board(MainWindow *ui, Game *game) {
  this->CurrentGame = game;
  this->CurrentGame->GameBoard = this;
  this->UI = ui;
  this->RenderPieces();
}

Board::Board(){}
Board::~Board(){}

void Board::RenderPieces() {
    this->ClearBoard();
    for (int row = 0; row < 2; row++) {
      std::vector<Piece*> pieces = CurrentGame->Players[row]->ActivePieces;
      for (int col = 0; col < pieces.size(); col++) {
        Square selected_square(row,col);


        //System.Windows.Controls.Button piece_button = GetButton(piece.Position);
        //if (piece_button != null)
        //{
            //piece_button.Content = piece.Content;
        //}
      }
    }
}

void Board::ClearBoard() {
    /*foreach(System.Windows.Controls.Button button in UI.ChessBoardGrid.Children)
    {
        button.Content = "";
        button.BorderThickness = new Thickness(1);
        button.BorderBrush = Brushes.Black;
    }*/
}

/*private System.Windows.Controls.Button GetButton(Square position)
{
    foreach (System.Windows.Controls.Button button in UI.ChessBoardGrid.Children)
    {
        if(System.Windows.Controls.Grid.GetRow(button) == position.Rank
        && System.Windows.Controls.Grid.GetColumn(button) == position.File)
        {
            return button;
        }
    }
    return null;
}
*/
