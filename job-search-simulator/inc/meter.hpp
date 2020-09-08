#ifndef INC_METER_HPP_
#define INC_METER_HPP_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <string>

#include "entity.hpp"
#include "globals.hpp"
#include "vec2.hpp"

class Meter final : public Entity {
public:
  Meter(const char* label, int x, int y, float percentage);
  ~Meter();
  void draw() override;
  void update() override;
  float percentage;
private:
  ALLEGRO_FONT* font;
  std::string label;
  Vec2 position;
  float width;
};

#endif  // INC_METER_HPP_
