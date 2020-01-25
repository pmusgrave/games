#include "game.hpp"
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

Game::Game(){
  srand(time(NULL));
  for (int i = 0; i < GRID_SIZE + 1; i++) {
    for (int j = 0; j < GRID_SIZE + 1; j++) {
      this->grid[i][j].occupied = rand() % 2;
    }
  }
}

Game::~Game(){}

void Game::update_pre() {
  for (int i = 0; i < GRID_SIZE + 1; i++) {
    for (int j = 0; j < GRID_SIZE + 1; j++) {
      int neighbors = calculate_neighbors(i, j);
      // std::cout << i << " " << j << " " << neighbors << std::endl;
      if (this->grid[i][j].occupied && (neighbors <= 1 || neighbors >= 4)) {
        // std::cout << "delete " << i << " " << j << std::endl;
        this->grid[i][j].marked_for_deletion = true;
      }
      else if (this->grid[i][j].occupied && (neighbors == 2 || neighbors == 3)) {
        this->grid[i][j].marked_for_deletion = true;
      }
      else if (!this->grid[i][j].occupied && neighbors == 3) {
        this->grid[i][j].marked_for_population = true;
      }
    }
  }
}

void Game::update_post() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (this->grid[i][j].marked_for_deletion) {
        this->grid[i][j].occupied = 0;
        //        std::cout << this->grid[i][j].occupied;
      }
      if (this->grid[i][j].marked_for_population) {
        this->grid[i][j].occupied = 1;
      }
      this->grid[i][j].marked_for_deletion = false;
      this->grid[i][j].marked_for_population = false;
    }
  }
}

int Game::calculate_neighbors(size_t i, size_t j){
  if (i > GRID_SIZE || j > GRID_SIZE) {
    return -1;
  }
  if (i == 0 && j == 0) { // upper left corner
    return this->grid[i+1][j].occupied
      + this->grid[i+1][j+1].occupied
      + this->grid[i][j+1].occupied;
  }
  else if (i == 0 && j > 0 && j < GRID_SIZE) { // top row
    return this->grid[i][j-1].occupied
      + this->grid[i][j+1].occupied
      + this->grid[i+1][j-1].occupied
      + this->grid[i+1][j+1].occupied
      + this->grid[i+1][j].occupied;
  }
  else if (i == 0 && j == GRID_SIZE) { // top right corner
    return this->grid[i+1][j].occupied
      + this->grid[i+1][j-1].occupied
      + this->grid[i][j-1].occupied;
  }
  else if (j == 0 && i > 0 && i < GRID_SIZE) { // left edge
    return this->grid[j][i-1].occupied
      + this->grid[j][i+1].occupied
      + this->grid[j+1][i-1].occupied
      + this->grid[j+1][i+1].occupied
      + this->grid[j+1][i].occupied;
  }
  else if (i == GRID_SIZE && j == 0) { // bottom left corner
    return this->grid[i-1][j].occupied
      + this->grid[i-1][j+1].occupied
      + this->grid[i][j+1].occupied;
  }
  else if (i == GRID_SIZE && j > 0 && j < GRID_SIZE) { // bottom edge
    return this->grid[i][j-1].occupied
      + this->grid[i][j+1].occupied
      + this->grid[i-1][j-1].occupied
      + this->grid[i-1][j+1].occupied
      + this->grid[i-1][j].occupied;
  }
  else if (i == GRID_SIZE && j == GRID_SIZE) { // bottom right corner
    return this->grid[i-1][j].occupied
      + this->grid[i-1][j-1].occupied
      + this->grid[i][j-1].occupied;
  }
  else if (j == GRID_SIZE && i > 0 && i < GRID_SIZE) { // right edge
    return this->grid[j][i-1].occupied
      + this->grid[j][i+1].occupied
      + this->grid[j-1][i-1].occupied
      + this->grid[j-1][i+1].occupied
      + this->grid[j-1][i].occupied;
  }
  else { // center
    int val = this->grid[i-1][j-1].occupied
      + this->grid[i-1][j].occupied
      + this->grid[i-1][j+1].occupied
      + this->grid[i][j-1].occupied
      + this->grid[i][j+1].occupied
      + this->grid[i+1][j-1].occupied
      + this->grid[i+1][j].occupied
      + this->grid[i+1][j+1].occupied;
    //    std::cout << val << std::endl;
    return val;
  }
}

void Game::print() {
  for (int i = 0; i < GRID_SIZE + 1; i++) {
    for (int j = 0; j < GRID_SIZE + 1; j++) {
      std::cout << this->grid[i][j].occupied;// << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
