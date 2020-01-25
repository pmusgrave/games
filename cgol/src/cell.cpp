#include "cell.hpp"

Cell::Cell(){
  this->occupied = false;
  this->marked_for_deletion = false;
  this->marked_for_population = false;
}
Cell::~Cell(){}
