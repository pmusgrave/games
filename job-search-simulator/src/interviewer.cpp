#include "interviewer.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include "bullet.hpp"
#include "globals.hpp"

Interviewer::Interviewer(int x, int y, std::vector<Bullet*> *bullets)
  : x(x),
    y(y),
    bullet_timer(10),
    bullets(bullets),
    launch_angle(10),
    launch_angle_inc(0.5),
    spawn_bullets(false)
{}

Interviewer::~Interviewer() {}

void Interviewer::draw() {
  al_draw_filled_rectangle(x, y,
                           x + width, y + height,
                           al_map_rgba_f(1, 1, 1, 1));
}

void Interviewer::update() {
  if (--bullet_timer <= 0) {
    spawn_bullets = true;
    bullet_timer = 1;
  }
  else spawn_bullets = false;

  if (spawn_bullets) {
    launch_angle += launch_angle_inc;
    int launch_vec_x = (int) (cos(launch_angle) * 10);
    int launch_vec_y = (int) (sin(launch_angle) * 10);
    bullets->push_back(std::move(new Bullet(x, y, launch_vec_x, launch_vec_y)));
  }
}
