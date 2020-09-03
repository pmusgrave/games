#ifndef INC_BLACK_HOLE_HPP_
#define INC_BLACK_HOLE_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "entity.hpp"

class BlackHole final : public Entity {
public:
  BlackHole();
  ~BlackHole();
  void draw() override;
  void show_message();
  void update() override;
  static double G;
  unsigned long long m;
  int radius;
  int x;
  int y;
private:
  ALLEGRO_BITMAP* img;
  bool flip;
  bool message;
  size_t message_index;
  int message_timer;
  float rotation;
  float rotation_rate;
};

#endif  // INC_BLACK_HOLE_HPP
