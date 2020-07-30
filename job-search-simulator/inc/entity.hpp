#ifndef INC_ENTITY_HPP_
#define INC_ENTITY_HPP_

class Entity {
 public:
  virtual ~Entity() {}
  virtual void draw() = 0;
  virtual void update() = 0;
};

#endif  // INC_ENTITY_HPP_
