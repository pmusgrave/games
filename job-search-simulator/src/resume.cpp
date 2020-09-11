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
  rocket_boost_sprite[0] = al_load_bitmap("resources/rocket-boost-frame-3.png");
  rocket_boost_sprite[1] = al_load_bitmap("resources/rocket-boost-frame-2.png");
  rocket_boost_sprite[2] = al_load_bitmap("resources/rocket-boost-frame-2.png");
  rocket_boost_sprite[3] = al_load_bitmap("resources/rocket-boost-frame-3.png");
  rocket_boost_sprite[4] = al_load_bitmap("resources/rocket-boost-frame-4.png");
  if(!img
    || !rocket_boost_sprite[0]
    || !rocket_boost_sprite[1]
    || !rocket_boost_sprite[2]
    || !rocket_boost_sprite[3])
  {
    printf("couldn't load img\n");
  }
  rocket_frame[0] = 0;
  rocket_frame[1] = 0;
  rocket_frame[2] = 0;
  rocket_frame[3] = 0;
  rocket_frame_index[0] = 0;
  rocket_frame_index[1] = 0;
  rocket_frame_index[2] = 0;
  rocket_frame_index[3] = 0;
  rocket_frame_rate[0] = rand()%10;
  rocket_frame_rate[1] = rand()%10;
  rocket_frame_rate[2] = rand()%10;
  rocket_frame_rate[3] = rand()%10;

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

  if (interlude) {
    angle = 0;
  }

  if (draw_rocket_down) {
    rocket_frame[0] += rand();
    if (rocket_frame[0] >= rocket_frame_rate[0]) {
      rocket_frame_index[0] = (++rocket_frame_index[0])%frame_max;
      rocket_frame[0] = 0;
    }

    al_draw_scaled_rotated_bitmap(rocket_boost_sprite[rocket_frame_index[0]],
      al_get_bitmap_width(rocket_boost_sprite[rocket_frame_index[0]])/2,
      0,
      x+width/2, y+height,
      0.35,0.35,
      0,
      0);
    // al_draw_filled_triangle(x + width/2 - resolution.y * 0.00926, y + height,
    //                         x + width/2 + resolution.y * 0.00926, y + height,
    //                         x + width/2, y + height + resolution.y *0.0278,
    //                         al_map_rgb(254, 110, 00));
  }
  if (draw_rocket_left) {
    rocket_frame[1] += rand();
    if (rocket_frame[1] >= rocket_frame_rate[1]) {
      rocket_frame_index[1] = (++rocket_frame_index[1])%frame_max;
      rocket_frame[1] = 0;
    }

    al_draw_scaled_rotated_bitmap(rocket_boost_sprite[rocket_frame_index[1]],
      al_get_bitmap_width(rocket_boost_sprite[rocket_frame_index[1]])/2,
      0,
      x, y+height/2,
      0.35,0.35,
      M_PI/2,
      0);
    // al_draw_filled_triangle(x, y + height/2 - resolution.y * 0.00926,
    //                         x, y + height/2  + resolution.y * 0.00926,
    //                         x - resolution.y *0.0278, y + height/2,
    //                         al_map_rgb(254, 110, 00));
  }
  if (draw_rocket_right) {
    rocket_frame[2] += rand();
    if (rocket_frame[2] >= rocket_frame_rate[2]) {
      rocket_frame_index[2] = (++rocket_frame_index[2])%frame_max;
      rocket_frame[2] = 0;
    }

    al_draw_scaled_rotated_bitmap(rocket_boost_sprite[rocket_frame_index[2]],
      al_get_bitmap_width(rocket_boost_sprite[rocket_frame_index[2]])/2,
      0,
      x+width, y+height/2,
      0.35,0.35,
      -M_PI/2,
      0);
    // al_draw_filled_triangle(x + width, y + height/2 - resolution.y * 0.00926,
    //                         x + width, y + height/2 + resolution.y * 0.00926,
    //                         x + width + resolution.y *0.0278, y + height/2,
    //                         al_map_rgb(254, 110, 00));
  }
  if (draw_rocket_up) {
    rocket_frame[3] += rand();
    if (rocket_frame[3] >= rocket_frame_rate[3]) {
      rocket_frame_index[3] = (++rocket_frame_index[3])%frame_max;
      rocket_frame[3] = 0;
    }

    al_draw_scaled_rotated_bitmap(rocket_boost_sprite[rocket_frame_index[3]],
      al_get_bitmap_width(rocket_boost_sprite[rocket_frame_index[3]])/2,
      0,
      x+width/2, y,
      0.35,0.35,
      M_PI,
      0);
  //   al_draw_filled_triangle(x + width/2 - resolution.y * 0.00926, y,
  //                           x + width/2 + resolution.y * 0.00926, y,
  //                           x + width/2, y - resolution.y *0.0278,
  //                           al_map_rgb(254, 110, 00));
  // }
  }
  draw_rocket_down = false;
  draw_rocket_left = false;
  draw_rocket_right = false;
  draw_rocket_up = false;

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
      al_map_rgb(255,200,200),
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
      (x + width) + resolution.x*0.0078,
      (y + (height / 2)),
      al_map_rgb(255, 255, 255),
      1
    );
    al_draw_line(
      (x + width) + resolution.x*0.0078,
      (y + (height / 2)),
      (x + width) + resolution.x*0.0052,
      (y + (height / 2)) + resolution.x*0.0026,
      al_map_rgb(255, 255, 255),
      1
    );
    al_draw_line(
      (x + width) + resolution.x*0.0078,
      (y + (height / 2)),
      (x + width) + resolution.x*0.0052,
      (y + (height / 2)) - resolution.x*0.0026,
      al_map_rgb(255, 255, 255),
      1
    );
  }
  al_identity_transform(&trans);
  al_use_transform(&trans);
}

double Resume::get_scalar_velocity_squared() {
  return pow(vx,2) + pow(vy,2);
}

void Resume::handle_a() {
  if (interlude) {
    x -= resolution.x*0.0052;
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
    x += resolution.x*0.0052;
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
    y += resolution.y*0.0093;
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
    y -= resolution.y*0.0093;
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
      y += resolution.y*0.0093;
    y = y % resolution.y;
}

void Resume::move_up() {
  if (!launched)
    y -= resolution.y*0.0093;
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
  width = resolution.y * 0.046;
  height = resolution.y * 0.065;
  font = al_load_font("resources/Comfortaa/Comfortaa-VariableFont_wght.ttf", resolution.y*0.015, 0);
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
    double r_sq = pow(dx,2) + pow(dy,2);
    double theta = atan(abs(dy/dx));
    double a = (*itr)->G * (*itr)->m / r_sq;
    vx = dx > 0 ? vx + a*cos(theta) : vx - a*cos(theta);
    vy = dy > 0 ? vy + a*sin(theta) : vy - a*cos(theta);
  }
  x = (int)(x+vx*resolution.x/1920);
  y = (int)(y+vy*resolution.y/1080);
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
  }
}
