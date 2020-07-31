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
  void launch();
  void reset();
  void update() override;
  int x;
  int y;
  int launch_angle;
private:
  double vx;
  double vy;
  double angle;
  bool launched;
  bool fail;
  static const int width = 50;
  static const int height = 70;
  std::vector<BlackHole*>* black_holes;
};

#endif  // INC_RESUME_HPP_
