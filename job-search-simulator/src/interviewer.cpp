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
  al_init_image_addon();
  img = al_load_bitmap("resources/interviewer.png");
  if(!img){
    //printf("couldn't load img\n");
  }
  if (rand()%100 > 50) {
    launch_angle_inc = -launch_angle_inc;
  }
  int r = rand()%255;
  int g = rand()%255;
  int b = rand()%255;
  color.r = r;
  color.g = g;
  color.b = b;
}

Interviewer::~Interviewer() {
  al_destroy_bitmap(img);
}

void Interviewer::draw() {
  al_draw_tinted_bitmap(img, al_map_rgb(color.r, color.g, color.b), x, y, 0);
  // al_draw_filled_rectangle(x, y,
  //                          x + width, y + height,
  //                          al_map_rgba_f(1, 1, 1, 1));
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
    bullets->push_back(std::move(new Bullet(x + width, y + height, launch_vec_x, launch_vec_y)));
  }
}
