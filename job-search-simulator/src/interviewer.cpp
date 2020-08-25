#include "interviewer.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include "bullet.hpp"
#include "globals.hpp"

Interviewer::Interviewer(int x, int y, int bullet_timer, std::vector<Bullet*> *bullets)
  : x(x),
    y(y),
    bullet_timer(bullet_timer),
    bullet_timer_initial(20),
    bullet_timer_max(bullet_timer),
    bullets(bullets),
    launch_angle(10),
    launch_angle_inc(0.5),
    spawn_bullets(false)
{
  if (rand()%100 > 50) {
    launch_angle_inc = -launch_angle_inc;
  }
}

Interviewer::~Interviewer() {}

void Interviewer::draw() {
  al_draw_filled_rectangle(x, y,
                           x + width, y + height,
                           al_map_rgba_f(1, 1, 1, 1));
}

void Interviewer::update() {
  if (bullet_timer_initial >= 0) {
    bullet_timer_initial--;
    return;
  }
  if (--bullet_timer <= 0) {
    spawn_bullets = true;
    bullet_timer = bullet_timer_max;
  }
  else spawn_bullets = false;

  if (spawn_bullets) {
    launch_angle += launch_angle_inc;
    int launch_vec_x = (int) (cos(launch_angle) * 10);
    int launch_vec_y = (int) (sin(launch_angle) * 10);
    bullets->push_back(std::move(new Bullet(x, y, launch_vec_x, launch_vec_y)));
  }
}
