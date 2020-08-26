#include "manager.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include <random>

Manager::Manager(int x, int y)
  : x(x), y(y), width(resolution.x*0.0508), height(resolution.y*0.0972)
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

void Manager::respawn() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned int> y_pos_dist(resolution.y*0.3, resolution.y*0.7);
  y = y_pos_dist(gen) % resolution.y;
}

void Manager::update() {}
