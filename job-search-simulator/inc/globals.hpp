#ifndef INC_GLOBALS_HPP_
#define INC_GLOBALS_HPP_

struct screen_resolution {
  unsigned int x;
  unsigned int y;
};

extern struct screen_resolution resolution;
extern int line_height;
extern const double c_squared;

#endif  // INC_GLOBALS_HPP_
