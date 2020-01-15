#include<iostream>
#include "board.h"
#include "game.h"
#include "player.h"

//#include "king.h"
//#include "queen.h"
//#include "rook.h"
//#include "knight.h"
//#include "bishop.h"
//#include "pawn.h"

int main(int argc, char *argv[]) {
  std::cout << "hello world\n";

  Game chess_game();
  Board chess_board();
  Player p1("White");
  Player p2("Black");

  return 0;
}
