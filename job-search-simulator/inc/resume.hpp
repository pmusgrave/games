#ifndef INC_RESUME_HPP_
#define INC_RESUME_HPP_

#include <vector>

#include "black_hole.hpp"
#include "entity.hpp"

class Resume final : public Entity {
public:
  Resume(int x, int y, std::vector<BlackHole*>* black_holes);
  ~Resume() {}
  void draw() override;
  void update() override;
private:
  int x;
  int y;
  double vx;
  double vy;
  static const int width = 50;
  static const int height = 70;
  std::vector<BlackHole*>* black_holes;
};

#endif  // INC_RESUME_HPP_
