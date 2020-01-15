#ifndef GAME_H
#define GAME_H

#include <string>
#include "board.h"
#include "square.h"
#include "piece.h"
#include "player.h"

class Game {
public:
	Game();
	~Game();

  Board *GameBoard;
	Player Players[2];
	Player CurrentPlayer;
  std::string State;
	Player Winner;

	bool IsSquareOccupied(Square*);
	bool IsValidCastle(Piece*, Square*);
	bool IsValidMove(Piece*, Square*);
	bool IsValidCapture(Piece*, Square*);
	void SwitchPlayers();
};

#endif
