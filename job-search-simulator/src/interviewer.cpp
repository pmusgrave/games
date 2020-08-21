#include "interviewer.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

#include "bullet.hpp"
#include "globals.hpp"

Interviewer::Interviewer(int x, int y, std::vector<Bullet*> *bullets)
  : bullets(bullets),
    x(x),
    y(y),
    bullet_timer(10),
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
    bullet_timer = 10;
  }
  else spawn_bullets = false;

  if (spawn_bullets) {
    bullets->push_back(new Bullet(resolution.x/2, 50, -1, 5));
  }
}
