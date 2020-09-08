#ifndef INC_METER_HPP_
#define INC_METER_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "entity.hpp"

class Meter final : public Entity {
public:
  Meter();
  ~Meter();
  void draw() override;
  void update() override;
private:
  Vec2 position;
};

#endif  // INC_METER_HPP_
