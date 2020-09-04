#ifndef INC_STAR_HPP_
#define INC_STAR_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "entity.hpp"

class Star final : public Entity {
public:
  Star();
  ~Star();
  void draw() override;
  void update() override;
  static constexpr int frame_max = 3;
private:
  ALLEGRO_BITMAP* img[frame_max];
  int frame;
  int frame_index;
  int frame_rate;
  float rotation;
  float rotation_rate;
  int x;
  int y;
};

#endif  // INC_STAR_HPP
