#ifndef INC_GLOBALS_HPP_
#define INC_GLOBALS_HPP_

#include <allegro5/allegro5.h>

#include <string>

struct screen_resolution {
  screen_resolution() : x(1920), y(1080), display_string("1920x1080") {}
  screen_resolution(int x, int y, const char* display_string)
    : x(x),
      y(y),
      display_string(std::string(display_string)),
      selected(false)
  {}

  void set_auto() {
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    int w = info.x2 - info.x1;
    int h = info.y2 - info.y1;
    x = w;
    y = h;
    display_string = std::string("auto");
  }

  unsigned int x;
  unsigned int y;
  std::string display_string;
  bool selected;
};

extern struct screen_resolution resolution;
extern int line_height;
extern const double c_squared;

#endif  // INC_GLOBALS_HPP_
