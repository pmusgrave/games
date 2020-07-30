#include "resume.hpp"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>

Resume::Resume(int x, int y, std::vector<BlackHole*>* black_holes)
  : x(x), y(y), vx(10), vy(5), black_holes(black_holes)
{}

void Resume::draw() {
  al_draw_filled_rectangle(x, y,
                           x + width, y + height,
                           al_map_rgba_f(1, 1, 1, 1));
}

void Resume::update() {
  std::vector<BlackHole*>::iterator itr;
  for (itr = black_holes->begin(); itr < black_holes->end(); itr++) {
    double d = abs((*itr)->x - x);
    doubl dx = cos(M_PI *d / 180);
    vx += (*itr)->G * (*itr)->m / pow(cos(M_PI*d/180), 2);
    std::cout << "d:" << d << "vx" << vx << std::endl;;
  }
  //  x = (int)(x+vx) % 800;
  //  y = (int)(y+vy) % 600;
}
