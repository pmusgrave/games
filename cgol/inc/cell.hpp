#ifndef CELL_HPP
#define CELL_HPP

class Cell {
public:
  Cell();
  ~Cell();

  bool occupied;
  bool marked_for_deletion;
  bool marked_for_population;
};

#endif
