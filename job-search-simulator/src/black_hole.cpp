#include "black_hole.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

BlackHole::BlackHole(int x, int y)
  : x(x), y(y)
{
  srand(time(NULL));
  radius = rand()%((100 - 30) + 1);
  m = radius * 1e12;
}

void BlackHole::draw() {
  al_draw_circle(x, y, radius, al_map_rgb_f(1, 0, 0), 2);
}

void BlackHole::update() {}
