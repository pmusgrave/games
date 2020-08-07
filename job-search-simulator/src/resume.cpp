#include "resume.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "globals.hpp"

Resume::Resume(int x, int y, std::vector<BlackHole*>* black_holes, Manager* manager)
  : launch_angle(0),
    win(false),
    x(x),
    y(y),
    angle(0),
    black_holes(black_holes),
    fail(false),
    launched(false),
    manager(manager),
    vx(0),
    vy(0)
{
  al_init_image_addon();
  img = al_load_bitmap("resources/resume.png");
  if(!img){
    printf("couldn't load img\n");
  }
}

Resume::~Resume() {
  al_destroy_bitmap(img);
}

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

  // al_draw_filled_rectangle(x, y,
  //                          x + width, y + height,
  //                          al_map_rgba_f(1, 1, 1, 1));
  al_draw_scaled_bitmap(img,
                        0, 0,  // source origin
                        al_get_bitmap_width(img),  // source width
                        al_get_bitmap_height(img),  // source height
                        x, y,  // target origin
                        width, height,  // target dimensions
                        0  // flags
                        );

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
  if (y <= 0)
    y = 0;
}

void Resume::move_up() {
  if (!launched)
    y += 10;
  y = y % resolution.y;
}

void Resume::reset() {
  x = 0;
  y = resolution.y / 2;
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
    double theta = atan(abs(dy/dx));
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
  if (x + width >= (int)resolution.x) {
    vx = -vx;
  }
  if (y <= 0) {
    vy = -vy;
    y = 0;
  }
  if (y + height >= (int)resolution.y) {
    vy = -vy;
  }

  if (vx >= vmax) {
    vx = vmax;
  }
  if (vy >= vmax) {
    vy = vmax;
  }

  for (itr = black_holes->begin(); itr < black_holes->end(); itr++) {
    int bb = (*itr)->radius*sqrt(2);
    int circle_bb_x = (*itr)->x - bb/2;
    int circle_bb_y = (*itr)->y - bb/2;

    if ((circle_bb_x <= (x + width) && x <= (circle_bb_x + bb))
    && (circle_bb_y <= (y + height) && y <= (circle_bb_y + bb))) {
      fail = true;
      (*itr)->show_message();
      break;
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
