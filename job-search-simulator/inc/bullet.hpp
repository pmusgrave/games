#ifndef INC_BULLET_HPP_
#define INC_BULLET_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "entity.hpp"

class Bullet final : public Entity {
 public:
  Bullet(int x, int y, int vx, int vy);
  ~Bullet();
  void draw() override;
  void update() override;
  bool marked_for_removal;
  int x;
  int y;
 private:
  ALLEGRO_FONT* font;
  int vx;
  int vy;
};

#endif  // INC_BULLET_HPP_
