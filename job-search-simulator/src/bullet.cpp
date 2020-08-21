#include "bullet.hpp"

#include "globals.hpp"

Bullet::Bullet(int x, int y, int vx, int vy)
  : marked_for_removal(false),
    x(x),
    y(y),
    font(al_create_builtin_font()),
    vx(vx),
    vy(vy)
{}

Bullet::~Bullet() {}

void Bullet::draw() {
  al_draw_text(font,
               al_map_rgb(255, 255, 255),
               x,
               y,
               ALLEGRO_ALIGN_CENTRE,
               "?");
}

void Bullet::update() {
  x += vx;
  if (x > resolution.x || x < 0)
    marked_for_removal = true;
  y += vy;
  if (y > resolution.y || y < 0)
    marked_for_removal = true;
}
