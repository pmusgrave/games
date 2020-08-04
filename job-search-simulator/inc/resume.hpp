#ifndef INC_RESUME_HPP_
#define INC_RESUME_HPP_

#include <vector>

#include "black_hole.hpp"
#include "entity.hpp"
#include "manager.hpp"

class Resume final : public Entity {
public:
  Resume(int x, int y, std::vector<BlackHole*>* black_holes, Manager* manager);
  ~Resume();
  void draw() override;
  void launch();
  void move_down();
  void move_up();
  void reset();
  void update() override;
  int launch_angle;
  bool win;
  int x;
  int y;
private:
  double angle;
  std::vector<BlackHole*>* black_holes;
  ALLEGRO_BITMAP* img;
  bool fail;
  bool launched;
  Manager* manager;
  double vx;
  double vy;
  static const int width = 50;
  static const int height = 70;
  static const int vmax = 30;
};

#endif  // INC_RESUME_HPP_
