#ifndef INC_BLACK_HOLE_HPP_
#define INC_BLACK_HOLE_HPP_

#include "entity.hpp"

class BlackHole final : public Entity {
public:
  BlackHole();
  ~BlackHole() {}
  void draw() override;
  void show_message();
  void update() override;
  int x;
  int y;
  int radius;
  unsigned long long m;
  static constexpr double G = 6.67430e-11;
private:
  int message_timer;
  bool message;
};

#endif  // INC_BLACK_HOLE_HPP
