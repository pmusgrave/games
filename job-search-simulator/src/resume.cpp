#include "resume.hpp"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>

Resume::Resume(int x, int y, std::vector<BlackHole*>* black_holes)
  : x(x), y(y), vx(0), vy(0), launched(false), black_holes(black_holes)
{}

void Resume::draw() {
  ALLEGRO_TRANSFORM trans;
  al_identity_transform(&trans);
  al_translate_transform(&trans, -x-width/2, -y-height/2);
  al_rotate_transform(&trans, angle);
  al_translate_transform(&trans, x+width/2, y+height/2);
  al_use_transform(&trans);

  al_draw_filled_rectangle(x, y,
                           x + width, y + height,
                           al_map_rgba_f(1, 1, 1, 1));

  al_identity_transform(&trans);
  al_use_transform(&trans);
}

void Resume::launch() {
  if (launched)
    return;
  launched = true;
  vx = 20*cos(angle);
  vy = 20*sin(angle);
}

void Resume::update() {
  if (!launched) {
    angle = M_PI * launch_angle / 180;
    return;
  }
  else {
    angle += 0.15;
  }

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
    //std::cout << "vx:" << vx << " vy: " << vy << " r:" << r << std::endl;
  }
  x = (int)(x+vx);
  y = (int)(y+vy);
  if (x <= 0) {
    vx = -vx;
    x = 0;
  }
  if (x + width >= 2560) {
    vx = -vx;
  }
  if (y <= 0) {
    vy = -vy;
    y = 0;
  }
  if (y + height >= 1440) {
    vy = -vy;
  }

  if (vx >= 30) {
    vx = 30;
  }
  if (vy >= 30) {
    vy = 30;
  }

  for (itr = black_holes->begin(); itr < black_holes->end(); itr++) {
    if (abs(x - (*itr)->x) < 10 && abs(y - (*itr)->y) < 10) {
      std::cout << "black hole" << std::endl;
      vx = 0;
      vy = 0;
    }
  }
}
