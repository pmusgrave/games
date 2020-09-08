#ifndef INC_RESUME_HPP_
#define INC_RESUME_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <vector>

#include "black_hole.hpp"
#include "entity.hpp"
#include "manager.hpp"
#include "vec2.hpp"

class Resume final : public Entity {
 public:
  Resume(int x, int y, std::vector<BlackHole*>* black_holes, Manager* manager);
  ~Resume();
  void draw() override;
  void launch();
  double get_scalar_velocity_squared();
  void handle_a();
  void handle_d();
  void handle_s();
  void handle_space();
  void handle_w();
  void reset();
  void rocket_boost_enable();
  void update() override;
  bool fail;
  bool interlude;
  bool powerup_rocket;
  double rocket_fuel;
  double rocket_fuel_max;
  int v_max;
  int v_init;
  bool win;
  int x;
  int y;
  const int width;
  const int height;
 private:
  void move_down();
  void move_up();
  double angle;
  std::vector<BlackHole*>* black_holes;
  bool draw_rocket_down;
  bool draw_rocket_left;
  bool draw_rocket_right;
  bool draw_rocket_up;
  ALLEGRO_BITMAP* img;
  ALLEGRO_FONT* font;
  int launch_angle;
  bool launched;
  Manager* manager;
  int rocket_acceleration;
  double rocket_fuel_consumption;
  double rocket_fuel_max_initial;
  double vx;
  double vy;
};

#endif  // INC_RESUME_HPP_
