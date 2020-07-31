#include "black_hole.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

BlackHole::BlackHole() {
  radius = rand()%((100 - 30) + 1);
  x = rand()%(2560);
  y = rand()%(1440);
  m = radius * 1e13;
}

void BlackHole::draw() {
  al_draw_circle(x, y, radius, al_map_rgb_f(1, 0, 0), 2);
}

void BlackHole::update() {}
