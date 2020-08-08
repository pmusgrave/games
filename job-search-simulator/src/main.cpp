#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <time.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "black_hole.hpp"
#include "entity.hpp"
#include "globals.hpp"
#include "manager.hpp"
#include "resume.hpp"

// struct screen_resolution resolution { 2560, 1440 };
struct screen_resolution resolution { 1920, 1080 };

void must_init(bool test, const char *description) {
  if(test) return;

  printf("couldn't initialize %s\n", description);
  exit(1);
}

void clear_black_holes(std::vector<BlackHole*>& black_holes) {
  std::vector<BlackHole*>::iterator itr;
  for (itr = black_holes.begin(); itr < black_holes.end(); itr++) {
    delete (*itr);
  }
  black_holes.clear();
}

int main(int argc, char **argv) {
  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
  al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
  ALLEGRO_DISPLAY* disp = al_create_display(resolution.x, resolution.y);
  must_init(disp, "display");

  ALLEGRO_FONT* font = al_create_builtin_font();
  must_init(font, "font");

  must_init(al_init_primitives_addon(), "primitives");

  must_init(al_init_image_addon(), "image addon");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  std::vector<Entity*> entities;
  std::vector<BlackHole*> black_holes;
  //  entities.push_back(std::move(new BlackHole(100,100)));
  srand(time(NULL));
  // srand(0);
  int current_level = 1;
  for (int i = 0; i < current_level; i++) {
    BlackHole* bh = new BlackHole();
    black_holes.push_back(bh);
    //    entities.push_back(bh);
  }
  /*BlackHole bh1(200, 100);
    BlackHole bh2(600, 300);
    BlackHole bh3(100, 500);
    black_holes.push_back(&bh1);
    black_holes.push_back(&bh2);
    black_holes.push_back(&bh3);
    entities.push_back(&bh1);
    entities.push_back(&bh2);
    entities.push_back(&bh3);*/

  Manager manager(resolution.x - 130, resolution.y / 2);
  entities.push_back(&manager);

  Resume resume(0, resolution.y / 2, &black_holes, &manager);
  entities.push_back(&resume);

  bool show_intro_screen = true;
  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;
  std::string level_string = "Level ";
  level_string += std::to_string(current_level);

#define KEY_SEEN     1
#define KEY_RELEASED 2

  unsigned char key[ALLEGRO_KEY_MAX];
  memset(key, 0, sizeof(key));

  al_start_timer(timer);
  while(1) {
    al_wait_for_event(queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      if(key[ALLEGRO_KEY_W])
        resume.handle_w();
      if(key[ALLEGRO_KEY_S])
        resume.handle_s();
      if(key[ALLEGRO_KEY_A])
        resume.handle_a();
      if(key[ALLEGRO_KEY_D])
        resume.handle_d();
      if(key[ALLEGRO_KEY_R])
        resume.reset();
      if(key[ALLEGRO_KEY_SPACE])
        resume.handle_space();

      if(key[ALLEGRO_KEY_ESCAPE])
        done = true;

      for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
        key[i] &= KEY_SEEN;

      redraw = true;
      break;

    case ALLEGRO_EVENT_KEY_DOWN:
      key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
      break;
    case ALLEGRO_EVENT_KEY_UP:
      key[event.keyboard.keycode] &= KEY_RELEASED;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    }

    if(done)
      break;

    if (show_intro_screen) {
      al_draw_text(font,
                   al_map_rgb(255, 255, 255),
                   resolution.x/2,
                   resolution.y/2,
                   ALLEGRO_ALIGN_CENTRE,
                   "Get a job");
      al_flip_display();
      std::chrono::milliseconds timespan(3000);
      std::this_thread::sleep_for(timespan);
      show_intro_screen = false;
    }

    if(redraw && al_is_event_queue_empty(queue)) {
      al_clear_to_color(al_map_rgb(0, 0, 0));

      al_draw_text(font,
                   al_map_rgb(255, 255, 255),
                   resolution.x/2,
                   15,
                   ALLEGRO_ALIGN_CENTRE,
                   level_string.c_str());

      std::vector<Entity*>::iterator itr;
      for (itr = entities.begin(); itr < entities.end(); itr++) {
        (*itr)->update();
        (*itr)->draw();
      }

      std::vector<BlackHole*>::iterator bh_itr;
      for (bh_itr = black_holes.begin(); bh_itr < black_holes.end(); bh_itr++) {
        (*bh_itr)->update();
        (*bh_itr)->draw();
      }

      al_flip_display();
      redraw = false;
    }

    if (resume.win) {
      current_level++;
      level_string = "Level ";
      level_string += std::to_string(current_level);
      clear_black_holes(black_holes);
      for (int i = 0; i < current_level; i++) {
        BlackHole* bh = new BlackHole();
        black_holes.push_back(bh);
        //entities.push_back(bh);
      }
      resume.reset();

      if (current_level %5 == 0) {
        resume.powerup_rocket = true;
      }
    }
  }

  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  clear_black_holes(black_holes);

  return 0;
}
