#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "game.hpp"
#include "cell.hpp"

using namespace std;

int main(void) {
  Game game;

  while(1){
    game.update_pre();
    game.print();
    game.update_post();
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}
