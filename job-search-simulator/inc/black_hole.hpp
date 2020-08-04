#ifndef INC_BLACK_HOLE_HPP_
#define INC_BLACK_HOLE_HPP_

#include <stdio.h>

#include "entity.hpp"

class BlackHole final : public Entity {
public:
  BlackHole();
  ~BlackHole() {}
  void draw() override;
  void show_message();
  void update() override;
  static constexpr double G = 6.67430e-11;
  unsigned long long m;
  int radius;
  int x;
  int y;
private:
  bool message;
  size_t message_index;
  int message_timer;
};

#endif  // INC_BLACK_HOLE_HPP
