#include "black_hole.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

BlackHole::BlackHole(int x, int y) : x(x), y(y) {}

void BlackHole::draw() {
  al_draw_circle(x, y, 30, al_map_rgb_f(1, 0, 0), 2);
}
