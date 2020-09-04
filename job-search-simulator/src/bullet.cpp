#include "bullet.hpp"

#include "globals.hpp"

Bullet::Bullet(int x, int y, int vx, int vy)
  : marked_for_removal(false),
    x(x),
    y(y),
    vx(vx),
    vy(vy)
{
  al_init_font_addon();
  al_init_ttf_addon();
  font = al_load_font("resources/Comfortaa/Comfortaa-VariableFont_wght.ttf", resolution.y*0.02, 0);
}

Bullet::~Bullet() {
  al_destroy_font(font);
}

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
