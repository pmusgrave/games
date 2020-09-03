#include "black_hole.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

#include <random>
#include <string>
#include <vector>

#include "globals.hpp"

std::vector<std::string> rejection_phrases {
  "Thanks for your application! Someone will definitely be getting back to you!",
  "Your experience is impressive! But not what we're looking for.",
  "We're looking for someone with at least 5 years of experience.",
  "We received your application!",
  "Thanks <applicant name here>!",
  "Thanks for your interest in this company! We'll carefully review your application!",
  "Your resume will absolutely be read by a human!",
  "Thanks for spending an hour on our repetitive application process!",
  "Hope you had fun manually filling out unnecessary application forms!",
  "You didn't include a cover letter telling us why you're passionate about this company.",
  "There's a typo in your resume.",
  "...",
  "You wait one week but hear no response.",
  "Your experience is not impressive.",
  "You're not passionate enough about this company.",
  "Your cover letter was a little too passionate about this company.",
  "Sorry, not a great culture fit.",
  "We're only looking for senior level applicants.",
  "Not enough keywords in your resume.",
  "Your salary expectations were too high.",
  "Your salary expectations were too low.",
  "Your salary expectations were reasonable, but someone else is asking for less.",
  "Your application is sitting in a pile on someone's desk.",
  "Your application is buried under 1000 other applications.",
  "You waited too long to apply and the position has been filled.",
  "You applied at the wrong time of day.",
};

double BlackHole::G;

BlackHole::BlackHole()
  :  message(false), message_index(0), message_timer(100)
{
  al_init_image_addon();
  flip = rand()%100 > 50;
  if (flip) {
    img = al_load_bitmap("resources/black-hole-mirrored.png");
  } else {
    img = al_load_bitmap("resources/black-hole.png");
  }
  if(!img){
    printf("couldn't load img\n");
  }
  // source: https://stackoverflow.com/questions/7560114
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(resolution.y*0.00694, resolution.y*0.0694);
  radius = distr(gen);
  std::uniform_int_distribution<int> x_pos_distr(radius + 200, resolution.x - radius - 200);
  std::normal_distribution<float> y_pos_distr(resolution.y/2, 130);
  x = ((unsigned int)x_pos_distr(gen))%(resolution.x - radius);
  y = ((unsigned int)y_pos_distr(gen) + resolution.y/2)%(resolution.y - radius);// + (radius/2);
  m = radius * 1e13;

  std::normal_distribution<float> rotation_dist(0, 360);
  std::normal_distribution<float> rotation_rate_dist(0.001, 1);
  rotation = rotation_dist(gen);
  rotation_rate = rotation_rate_dist(gen);
  if (flip) {
    rotation_rate = abs(rotation_rate);
  }
  else {
    rotation_rate = -abs(rotation_rate);
  }

}

BlackHole::~BlackHole() {
  al_destroy_bitmap(img);
}

void BlackHole::draw() {
  if (radius > resolution.y*0.0694/3) {
    al_draw_circle(x, y, radius, al_map_rgb_f(1, 1, 1), 2);
    al_draw_filled_circle(x, y, radius * 0.9, al_map_rgb_f(0, 0, 0));
  } else {
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    // al_rotate_transform(&trans, rotation * M_PI/180);
    // if (flip) al_rotate_transform(&trans, );
    al_use_transform(&trans);
    al_draw_scaled_rotated_bitmap(img,
      al_get_bitmap_width(img)/2, al_get_bitmap_height(img)/2, // center
      x, y,  // destination origin
      radius/(3*resolution.y*0.00694), radius/(3*resolution.y*0.00694),  // destination scale factor
      (int)rotation * M_PI/180, // angle
      0  // flags
    );

    al_identity_transform(&trans);
    al_use_transform(&trans);
  }

  if (message) {
    if (--message_timer <= 0) {
      message = false;
      message_timer = 100;
    }
    else message = true;
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_draw_text(font,
                 al_map_rgb(255, 255, 255),
                 x,
                 y + radius + 15,
                 ALLEGRO_ALIGN_CENTRE,
                 rejection_phrases[message_index].c_str());
  }
}

void BlackHole::show_message() {
  message = true;
  message_index = rand()%(rejection_phrases.size());
  message_timer = 100;
}

void BlackHole::update() {
  rotation += rotation_rate;
  if (rotation > 360) rotation = 360;
}
