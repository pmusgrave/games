#include "meter.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

Meter::Meter(const char* label, int x, int y, float percentage)
: percentage(percentage),
  label(std::string(label)),
  position(Vec2(x,y)),
  width(150.0f)
{
  al_init_font_addon();
  al_init_ttf_addon();
  font = al_load_font("resources/Comfortaa/Comfortaa-VariableFont_wght.ttf", resolution.y*0.015, 0);
}

Meter::~Meter() {
  al_destroy_font(font);
}

void Meter::draw() {
  al_draw_text(font,
              al_map_rgb(255, 255, 255),
              position.x,
              position.y + line_height + resolution.y * 0.00926,
              ALLEGRO_ALIGN_LEFT,
              label.c_str());
  al_draw_rectangle(position.x,
                    position.y,
                    position.x + line_height + width,
                    position.y + line_height,
                    al_map_rgba_f(1, 1, 1, 1), resolution.y * 0.00185);
  al_draw_filled_rectangle(position.x,
                           position.y,
                           position.x + width*percentage,
                           position.y + line_height,
                           al_map_rgba_f(1, 1, 1, 1));
}

void Meter::update() {}
