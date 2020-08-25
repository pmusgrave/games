#ifndef INC_INTERVIEWER_HPP_
#define INC_INTERVIEWER_HPP_

#include <vector>

#include "bullet.hpp"

class Interviewer final : public Entity {
 public:
  Interviewer(int x, int y, int bullet_timer, std::vector<Bullet*> *bullets);
  ~Interviewer();
  void draw() override;
  void update() override;
  int x;
  int y;
 private:
  int bullet_timer;
  int bullet_timer_initial;
  int bullet_timer_max;
  std::vector<Bullet*> *bullets;
  float launch_angle;
  float launch_angle_inc;
  bool spawn_bullets;
  static const int width = 50;
  static const int height = 50;
};

#endif  // INC_INTERVIEWER_HPP_