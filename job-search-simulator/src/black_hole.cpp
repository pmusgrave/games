#include "black_hole.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

BlackHole::BlackHole()
  : message_timer(100), message(false)
{
  radius = rand()%((100 - 30) + 1);
  x = rand()%(1920);
  y = rand()%(1080);
  m = radius * 1e13;
}

void BlackHole::draw() {
  al_draw_circle(x, y, radius, al_map_rgb_f(1, 0, 0), 2);
  if (message) {
    if (--message_timer <= 0) {
      message = false;
      message_timer = 100;
    }
    else message = true;
    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_text(font,
                 al_map_rgb(255, 255, 255),
                 x,
                 y,
                 0,
                 "Thanks for your application! Someone will definitely be getting back to you!");
  }
}

void BlackHole::show_message() {
  message = true;
}

void BlackHole::update() {}
