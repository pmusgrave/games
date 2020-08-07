#include "manager.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

Manager::Manager(int x, int y)
  : x(x), y(y)
{
  al_init_image_addon();
  img = al_load_bitmap("resources/manager_desk.png");
  if(!img){
    printf("couldn't load img\n");
  }
}

Manager::~Manager() {
  al_destroy_bitmap(img);
}

void Manager::draw() {
  al_draw_scaled_bitmap(img,
                        0, 0,  // source origin
                        al_get_bitmap_width(img),  // source width
                        al_get_bitmap_height(img),  // source height
                        x, y,  // target origin
                        width, height,  // target dimensions
                        0  // flags
                        );
}

void Manager::update() {}
