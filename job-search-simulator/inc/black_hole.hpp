#ifndef INC_BLACK_HOLE_HPP_
#define INC_BLACK_HOLE_HPP_

#include "entity.hpp"

class BlackHole final : public Entity {
public:
  BlackHole(int x, int y);
  ~BlackHole() {}
  void draw() override;
private:
  int x;
  int y;
};

#endif  // INC_BLACK_HOLE_HPP
