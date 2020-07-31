#include "resume.hpp"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>

Resume::Resume(int x, int y, std::vector<BlackHole*>* black_holes)
  : x(x), y(y), vx(1), vy(0), black_holes(black_holes)
{}

void Resume::draw() {
  al_draw_filled_rectangle(x, y,
                           x + width, y + height,
                           al_map_rgba_f(1, 1, 1, 1));
}

void Resume::update() {
  std::vector<BlackHole*>::iterator itr;
  for (itr = black_holes->begin(); itr < black_holes->end(); itr++) {
    double dx = (*itr)->x - x;
    double dy = (*itr)->y - y;
    double r = sqrt(pow(dx,2) + pow(dy,2));
    double theta = atan(dy/dx);
    double a = (*itr)->G * (*itr)->m / pow(r, 2);
    vx = dx > 0 ? vx + a*cos(theta) : vx - a*cos(theta);
    vy = dy > 0 ? vy + a*sin(theta) : vy - a*cos(theta);
    //std::cout << "a:" << a << std::endl;
    std::cout << "vx:" << vx << " vy: " << vy << " r:" << r << std::endl;
  }
  x = (int)(x+vx) % 800;
  y = (int)(y+vy) % 600;
  if (x <= 0) {
    x = 800;
  }
  if (y <= 0) {
    y = 600;
  }

  for (itr = black_holes->begin(); itr < black_holes->end(); itr++) {
    if (x == (*itr)->x && y == (*itr)->y) {
      std::cout << "black hole" << std::endl;
      vx = 0;
      vy = 0;
    }
  }
}
