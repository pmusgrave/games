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
  void handle_a();
  void handle_d();
  void handle_s();
  void handle_space();
  void handle_w();
  void reset();
  void update() override;
  bool fail;
  bool interlude;
  bool powerup_rocket;
  bool win;
  int x;
  int y;
  static const int width = 50;
  static const int height = 70;
 private:
  void move_down();
  void move_up();
  double angle;
  std::vector<BlackHole*>* black_holes;
  ALLEGRO_BITMAP* img;
  int launch_angle;
  bool launched;
  Manager* manager;
  double vx;
  double vy;
  static const int vmax = 30;
};

#endif  // INC_RESUME_HPP_
