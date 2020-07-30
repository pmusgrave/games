#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <vector>

#include "entity.hpp"
#include "black_hole.hpp"

void must_init(bool test, const char *description) {
  if(test) return;

  printf("couldn't initialize %s\n", description);
  exit(1);
}

int main() {
  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
  ALLEGRO_DISPLAY* disp = al_create_display(800, 600);
  must_init(disp, "display");

  ALLEGRO_FONT* font = al_create_builtin_font();
  must_init(font, "font");

  must_init(al_init_primitives_addon(), "primitives");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  std::vector<Entity*> entities;
  entities.push_back(std::move(new BlackHole(100,100)));
  entities.push_back(std::move(new BlackHole(200,200)));

  bool redraw = true;
  ALLEGRO_EVENT event;

  al_start_timer(timer);

  while(1) {
    al_wait_for_event(queue, &event);

    if(event.type == ALLEGRO_EVENT_TIMER)
      redraw = true;
    else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
      break;

    if(redraw && al_is_event_queue_empty(queue)) {
      al_clear_to_color(al_map_rgb(0, 0, 0));

      std::vector<Entity*>::iterator itr;
      for (itr = entities.begin(); itr < entities.end(); itr++) {
        (*itr)->draw();
      }

      al_flip_display();
      redraw = false;
    }
  }

  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  std::vector<Entity*>::iterator itr;
  for (itr = entities.begin(); itr < entities.end(); itr++) {
    delete (*itr);
  }


  return 0;
}