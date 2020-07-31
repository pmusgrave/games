#ifndef INC_MANAGER_HPP_
#define INC_MANAGER_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "entity.hpp"

class Manager final : public Entity {
public:
  Manager(int x, int y);
  ~Manager();
  void draw() override;
  void update() override;
  int x;
  int y;
private:
  ALLEGRO_BITMAP* img;
  static const int width = 100;
  static const int height = 140;
};

#endif  // INC_MANAGER_HPP_