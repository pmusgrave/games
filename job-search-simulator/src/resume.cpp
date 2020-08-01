#include "resume.hpp"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>

Resume::Resume(int x, int y, std::vector<BlackHole*>* black_holes, Manager* manager)
  : x(x), y(y), vx(0), vy(0), angle(0), launched(false), fail(false), black_holes(black_holes), manager(manager)
{}

void Resume::draw() {
  if (fail) {
    reset();
  }

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

void Resume::move_down() {
  if (!launched)
    y -= 10;
}

void Resume::move_up() {
  if (!launched)
    y += 10;
}

void Resume::reset() {
  x = 0;
  y = 500;
  vx = 0;
  vy = 0;
  angle = 0;
  launched = false;
  fail = false;
  win = false;
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

  if (vx >= vmax) {
    vx = vmax;
  }
  if (vy >= vmax) {
    vy = vmax;
  }

  for (itr = black_holes->begin(); itr < black_holes->end(); itr++) {
    if (abs(x - (*itr)->x) <= (*itr)->radius && abs(y - (*itr)->y) <= (*itr)->radius) {
      fail = true;
      (*itr)->show_message();
    }
  }

  if ((x+width) >= manager->x
      && (((y >= manager->y
           && y <= (manager->y + manager->height)))
      || ((y+height) >= manager->y
          && (y+height) <= (manager->y + manager->height)))
      ) {
    win = true;
    //reset();
  }
}
