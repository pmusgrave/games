#include "resume.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "globals.hpp"
#include "vec2.hpp"

Resume::Resume(int x, int y, std::vector<BlackHole*>* black_holes, Manager* manager)
  : interlude(false),
    fail(false),
    v_max(35),
    v_init(20),
    win(false),
    x(x),
    y(y),
    width(resolution.y * 0.046),
    height(resolution.y * 0.065),
    angle(0),
    black_holes(black_holes),
    launch_angle(0),
    launched(false),
    manager(manager),
    powerup_rocket(false),
    rocket_acceleration(0),
    rocket_fuel(0.0),
    rocket_fuel_consumption(0.1),
    rocket_fuel_max(0.0),
    rocket_fuel_max_initial(150.0),
    vx(0),
    vy(0)
{
  al_init_image_addon();
  img = al_load_bitmap("resources/resume.png");
  if(!img){
    printf("couldn't load img\n");
  }

  al_init_font_addon();
  al_init_ttf_addon();
  font = al_load_font("resources/Comfortaa/Comfortaa-VariableFont_wght.ttf", resolution.y*0.015, 0);
}

Resume::~Resume() {
  al_destroy_bitmap(img);
  al_destroy_font(font);
}

void Resume::draw() {
  if (fail) {
    reset();
  }

  if (interlude)
    angle = 0;

  ALLEGRO_TRANSFORM trans;
  al_identity_transform(&trans);
  al_translate_transform(&trans, -x-width/2, -y-height/2);
  al_rotate_transform(&trans, angle);
  al_translate_transform(&trans, x+width/2, y+height/2);
  if (!launched || !powerup_rocket || rocket_fuel <= 0) {
    al_use_transform(&trans);
  }

  // al_draw_filled_rectangle(x, y,
  //                          x + width, y + height,
  //                          al_map_rgba_f(1, 1, 1, 1));
  if (rocket_fuel > 0) {
    al_draw_tinted_scaled_bitmap(img,
      al_map_rgb(255,0,0),
      0, 0,  // source origin
      al_get_bitmap_width(img),  // source width
      al_get_bitmap_height(img),  // source height
      x, y,  // target origin
      width, height,  // target dimensions
      0  // flags
    );
  }
  else {
    al_draw_scaled_bitmap(img,
      0, 0,  // source origin
      al_get_bitmap_width(img),  // source width
      al_get_bitmap_height(img),  // source height
      x, y,  // target origin
      width, height,  // target dimensions
      0  // flags
    );

  }

  if (!launched && !interlude) {
    al_draw_line(
      (x + width),
      (y + (height / 2)),
      (x + width) + 15,
      (y + (height / 2)),
      al_map_rgb(255, 255, 255),
      1
    );
    al_draw_line(
      (x + width) + 15,
      (y + (height / 2)),
      (x + width) + 10,
      (y + (height / 2)) + 5,
      al_map_rgb(255, 255, 255),
      1
    );
    al_draw_line(
      (x + width) + 15,
      (y + (height / 2)),
      (x + width) + 10,
      (y + (height / 2)) - 5,
      al_map_rgb(255, 255, 255),
      1
    );
  }
  al_identity_transform(&trans);
  al_use_transform(&trans);

  if (draw_rocket_down) {
    al_draw_filled_triangle(x + width/2 - resolution.y * 0.00926, y + height,
                            x + width/2 + resolution.y * 0.00926, y + height,
                            x + width/2, y + height + resolution.y *0.0278,
                            al_map_rgb(254, 110, 00));
  }
  if (draw_rocket_left) {
    al_draw_filled_triangle(x, y + height/2 - resolution.y * 0.00926,
                            x, y + height/2  + resolution.y * 0.00926,
                            x - resolution.y *0.0278, y + height/2,
                            al_map_rgb(254, 110, 00));
  }
  if (draw_rocket_right) {
    al_draw_filled_triangle(x + width, y + height/2 - resolution.y * 0.00926,
                            x + width, y + height/2 + resolution.y * 0.00926,
                            x + width + resolution.y *0.0278, y + height/2,
                            al_map_rgb(254, 110, 00));
  }
  if (draw_rocket_up) {
    al_draw_filled_triangle(x + width/2 - resolution.y * 0.00926, y,
                            x + width/2 + resolution.y * 0.00926, y,
                            x + width/2, y - resolution.y *0.0278,
                            al_map_rgb(254, 110, 00));
  }
  draw_rocket_down = false;
  draw_rocket_left = false;
  draw_rocket_right = false;
  draw_rocket_up = false;
}

double Resume::get_scalar_velocity_squared() {
  return pow(vx,2) + pow(vy,2);
}

void Resume::handle_a() {
  if (interlude) {
    x -= 10;
    if (x <= 0) x = 0;
  }
  else if (!launched) {
    launch_angle--;
  }
  else if (powerup_rocket && rocket_fuel > 0) {
    draw_rocket_right = true;
    vx -= rocket_acceleration;
    rocket_fuel -= rocket_fuel_consumption;
  }
}

void Resume::handle_d() {
  if (interlude) {
    x += 10;
    if (x >= resolution.x - width) x = resolution.x - width;
  }
  else if (!launched) {
    launch_angle++;
  }
  else if (powerup_rocket  && rocket_fuel > 0) {
    draw_rocket_left = true;
    vx += rocket_acceleration;
    rocket_fuel -= rocket_fuel_consumption;
  }
}

void Resume::handle_s() {
  if (interlude) {
    y += 10;
    if (y >= resolution.y - height) y = resolution.y - height;
  }
  else if (!launched) {
    move_down();
  }
  else if (powerup_rocket  && rocket_fuel > 0) {
    draw_rocket_up = true;
    vy += rocket_acceleration;
    rocket_fuel -= rocket_fuel_consumption;
  }
}

void Resume::handle_space() {
  if (!launched && !interlude) {
    launch();
  }
}

void Resume::handle_w() {
  if (interlude) {
    y -= 10;
    if (y <= 0) y = 0;
  }
  else if (!launched) {
    move_up();
  }
  else if (powerup_rocket  && rocket_fuel > 0) {
    draw_rocket_down = true;
    vy -= rocket_acceleration;
    rocket_fuel -= rocket_fuel_consumption;
  }
}

void Resume::launch() {
  if (launched)
    return;
  launched = true;
  vx = v_init*cos(angle);
  vy = v_init*sin(angle);
}

void Resume::move_down() {
  if (!launched)
      y += 10;
    y = y % resolution.y;
}

void Resume::move_up() {
  if (!launched)
    y -= 10;
  if (y <= 0)
    y = 0;
}

void Resume::reset() {
  if (interlude) {
    x = resolution.x/2;
    y = resolution.y*0.8;
  } else {
    x = 0;
    y = resolution.y / 2;
  }
  vx = 0;
  vy = 0;
  angle = 0;
  // interlude = false;
  launched = false;
  fail = false;
  win = false;
}

void Resume::reinitialize() {
  reset();
  interlude = false;
  fail = false;
  v_max = 35;
  v_init = 20;
  win = false;
  x = x;
  y = y;
  angle = 0;
  black_holes = black_holes;
  launch_angle = 0;
  launched = false;
  manager = manager;
  powerup_rocket = false;
  rocket_acceleration = 0;
  rocket_fuel = 0.0;
  rocket_fuel_consumption = 0.1;
  rocket_fuel_max = 0.0;
  rocket_fuel_max_initial = 150.0;
  vx = 0;
  vy = 0;
}

void Resume::rocket_boost_enable() {
  powerup_rocket = true;
  rocket_fuel_max += rocket_fuel_max_initial/2;
  rocket_fuel = rocket_fuel_max;
  rocket_acceleration += 1;
  if (rocket_fuel > rocket_fuel_max)
    rocket_fuel = rocket_fuel_max;
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

  if (vx >= v_max) {
    vx = v_max;
  }
  if (vy >= v_max) {
    vy = v_max;
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
