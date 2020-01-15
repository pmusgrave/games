#ifndef BOARD_H
#define BOARD_H

class MainWindow;
class Game;
class Piece;

class Board {
public:
  MainWindow *UI;
  Game *CurrentGame;

  Board(MainWindow *, Game *);
  Board();
  ~Board();

  void RenderPieces();
  void ClearBoard();
    
//private:
    //System.Windows.Controls.Button GetButton(Square position);
    
};

#endif
