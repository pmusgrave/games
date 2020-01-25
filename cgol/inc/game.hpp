#ifndef GAME_HPP
#define GAME_HPP
#include <stdio.h>
#include "cell.hpp"

#define GRID_SIZE 99

class Game {
public:
  Game();
  ~Game();

  int calculate_neighbors(size_t, size_t);
  void update_pre();
  void update_post();
  void print();

  Cell grid[GRID_SIZE + 1][GRID_SIZE + 1];
};

#endif
