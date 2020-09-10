#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "black_hole.hpp"
#include "entity.hpp"
#include "globals.hpp"
#include "interviewer.hpp"
#include "manager.hpp"
#include "meter.hpp"
#include "resume.hpp"
#include "star.hpp"

enum GameState {
  intro_screen = 0,
  normal,
  interlude,
  interlude_fail,
  interlude_win,
  failure,
  game_win,
};

std::array<screen_resolution,18> resolution_settings {
  screen_resolution(1920,1080, "auto"),
  screen_resolution(640,480, "640x480"),
  screen_resolution(800,600, "800x600"),
  screen_resolution(1024,768, "1024x768"),
  screen_resolution(1280,720, "1280x720"),
  screen_resolution(1280,800, "1280x800"),
  screen_resolution(1280,1024, "1280x1024"),
  screen_resolution(1360,768, "1360x768"),
  screen_resolution(1366,768, "1366x768"),
  screen_resolution(1440,900, "1440x900"),
  screen_resolution(1600,900, "1600x900"),
  screen_resolution(1680,1050, "1680x1050"),
  screen_resolution(1920,1080, "1920x1080"),
  screen_resolution(1920,1200, "1920x1200"),
  screen_resolution(2560,1080, "2560x1080"),
  screen_resolution(2560,1440, "2560x1440"),
  screen_resolution(3440,1440, "3440x1440"),
  screen_resolution(3840,2160, "3840x2160"),
};
struct screen_resolution resolution;
int line_height;
const double c_squared = 8.98755179e16;

class MenuItem {
 public:
  MenuItem(const char* label, bool selected, std::function<void()>action)
    : action(action),
      label(label),
      selected(selected)
  {}
  ~MenuItem() {}
  std::function<void()> action;
  std::string label;
  bool selected;
};

struct GameContext {
 public:
  GameContext(GameState state)
    : audio_volume(1),
      menu_selected_index(0),
      resolution(screen_resolution()),
      screen_resolution_index(0),
      show_controls(false),
      show_menu(false),
      state(state)
  {}

  void menu_item_down() {
    menu_selected_index++;
    if (menu_selected_index >= menu.size()) {
      menu_selected_index = 0;
    }
    std::vector<MenuItem>::iterator menu_itr;
    for (menu_itr = menu.begin(); menu_itr < menu.end(); menu_itr++) {
      (*menu_itr).selected = false;
    }
    menu[menu_selected_index].selected = true;
  }

  void menu_action() {
    menu[menu_selected_index].action();
  }

  void menu_item_left() {
    if (menu[menu_selected_index].label.substr(0,6) == "Volume") {
      audio_volume -= 0.05;
      if (audio_volume < 0) audio_volume = 0;
      std::stringstream ss;
      ss << "Volume < " << round(audio_volume*100) << " >";
      menu[menu_selected_index].label = ss.str();
    }

    if (menu[menu_selected_index].label.substr(0,17) == "Screen Resolution") {
      screen_resolution_index--;
      if (screen_resolution_index < 0) screen_resolution_index = resolution_settings.size() - 1;
      std::array<screen_resolution,18>::iterator scr_res_itr;
      for (scr_res_itr = resolution_settings.begin(); scr_res_itr < resolution_settings.end(); scr_res_itr++) {
        (*scr_res_itr).selected = false;
      }
      resolution_settings[screen_resolution_index].selected = true;
      resolution = resolution_settings[screen_resolution_index];

      std::stringstream res_ss;
      res_ss << "Screen Resolution < " << resolution.display_string << " >";
      std::string res_str = res_ss.str();
      menu[menu_selected_index].label = res_str;
    }
  }

  void menu_item_right() {
    if (menu[menu_selected_index].label.substr(0,6) == "Volume") {
      audio_volume += 0.05;
      if (audio_volume > 1) audio_volume = 1;
      std::stringstream ss;
      ss << "Volume < " << round(audio_volume*100) << " >";
      menu[menu_selected_index].label = ss.str();
    }

    if (menu[menu_selected_index].label.substr(0,17) == "Screen Resolution") {
      screen_resolution_index++;
      if (screen_resolution_index >= resolution_settings.size()) screen_resolution_index = 0;
      std::array<screen_resolution,18>::iterator scr_res_itr;
      for (scr_res_itr = resolution_settings.begin(); scr_res_itr < resolution_settings.end(); scr_res_itr++) {
        (*scr_res_itr).selected = false;
      }
      resolution_settings[screen_resolution_index].selected = true;
      resolution = resolution_settings[screen_resolution_index];

      std::stringstream res_ss;
      res_ss << "Screen Resolution < " << resolution.display_string << " >";
      std::string res_str = res_ss.str();
      menu[menu_selected_index].label = res_str;
    }
  }

  void menu_item_up() {
    menu_selected_index--;
    if (menu_selected_index < 0) {
      menu_selected_index = menu.size()-1;
    }
    std::vector<MenuItem>::iterator menu_itr;
    for (menu_itr = menu.begin(); menu_itr < menu.end(); menu_itr++) {
      (*menu_itr).selected = false;
    }
    menu[menu_selected_index].selected = true;
  }

  void reset_time() {
    time_remaining = tick_rate * 3000;
    reference_time_remaining = tick_rate * 3000;
  }

  std::function<void()> menu_confirm_action;

  float audio_volume;
  std::vector<MenuItem> menu;
  int menu_selected_index;
  unsigned int prestige_level;
  screen_resolution resolution;
  int screen_resolution_index;
  bool show_controls;
  bool show_menu;
  GameState state;
  static constexpr float tick_rate = 1.0f / 30.0f;
  float time_remaining;
  float reference_time_remaining;
};

enum Powerup {
  rocket_boost = 0,
  gravity_reduction,
  gravity_increase,
  init_speed_reduction,
  init_speed_increase,
  max_speed_reduction,
  max_speed_increase,
};
std::vector<Powerup> powerups {
  Powerup::rocket_boost,
  Powerup::gravity_reduction,
  Powerup::gravity_increase,
  Powerup::rocket_boost,
  Powerup::max_speed_reduction,
  Powerup::max_speed_increase,
  Powerup::init_speed_reduction,
  Powerup::init_speed_increase,
};

void must_init(bool test, const char *description) {
  if(test) return;

  printf("couldn't initialize %s\n", description);
  std::cin.get();
  exit(1);
}

template <typename T>
void clear_entities(typename std::vector<T*>& entities_to_clear) {
  typename std::vector<T*>::iterator itr;
  for (itr = entities_to_clear.begin(); itr < entities_to_clear.end(); itr++) {
    delete (*itr);
  }
  entities_to_clear.clear();
}

void init_level(
  std::vector<Entity*> &entities,
  Resume* resume,
  Manager* manager)
{
  clear_entities<Entity>(entities);
  entities.push_back(resume);
  entities.push_back(manager);
}

int main(int argc, char **argv) {
  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  al_set_new_display_option(ALLEGRO_AUX_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
  al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

  float user_setting_audio_volume = 1.0f;
  char user_settings_filename[] = "resources/user_settings";
  std::fstream user_settings_file;
  user_settings_file.open(user_settings_filename, std::fstream::in | std::fstream::out | std::fstream::app);
  if (!user_settings_file) {
    // std::cout << "User settings file does not exist. Creating a new one.";
    user_settings_file.open(user_settings_filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);

    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    int w = info.x2 - info.x1;
    int h = info.y2 - info.y1;
    resolution.x = w;
    resolution.y = h;
    resolution.display_string = std::string("auto");

    user_settings_file << resolution.x << std::endl;
    user_settings_file << resolution.y << std::endl;
    user_settings_file << resolution.display_string << std::endl;
    user_settings_file << user_setting_audio_volume << std::endl;
    user_settings_file << std::endl;
    user_settings_file.close();
  }
  else {
    int line_num = 0;
    // std::cout << "successfully opened "<< user_settings_filename << std::endl;
    std::string val;
    while (user_settings_file >> val) {
      switch(line_num) {
      case 0:
        resolution.x = std::stoi(val);
        break;
      case 1:
        resolution.y = std::stoi(val);
        break;
      case 2:
        resolution.display_string = std::string(val);
        break;
      case 3:
        user_setting_audio_volume = std::stof(val);
        break;
      default:
        break;
      }
      line_num++;
    }
    user_settings_file.close();
  }

  ALLEGRO_DISPLAY* disp = al_create_display(resolution.x, resolution.y);
  must_init(disp, "display");

  must_init(al_init_font_addon(), "init font");
  must_init(al_init_ttf_addon(), "ttf");
  ALLEGRO_FONT* font = al_load_font("resources/Comfortaa/Comfortaa-VariableFont_wght.ttf", resolution.y*0.02, 0);
  must_init(font, "load font");
  line_height = al_get_font_line_height(font);

  must_init(al_init_primitives_addon(), "primitives");
  must_init(al_init_image_addon(), "image addon");

  // AUDIO INITIALIZATION
  must_init(al_install_audio(), "install audio addon");
  must_init(al_init_acodec_addon(), "audio codec addon");
  must_init(al_reserve_samples(10), "reserve audio samples");
  ALLEGRO_VOICE* voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16,
    ALLEGRO_CHANNEL_CONF_2);
  must_init(voice, "create voice");
  ALLEGRO_MIXER* audio_mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,
    ALLEGRO_CHANNEL_CONF_2);
  must_init(audio_mixer, "create audio mixer");
  ALLEGRO_AUDIO_STREAM* intro_music = al_load_audio_stream("resources/soundtrack/intro.ogg", 4, 2048);
  ALLEGRO_AUDIO_STREAM* level_music = al_load_audio_stream("resources/soundtrack/level.ogg", 4, 2048);
  must_init(intro_music, "load intro music stream");
  must_init(level_music, "load level music stream");
  al_set_audio_stream_playmode(intro_music, ALLEGRO_PLAYMODE_LOOP);
  al_set_audio_stream_playmode(level_music, ALLEGRO_PLAYMODE_LOOP);
  bool intro_music_playing = false, level_music_playing = false;
  al_set_mixer_gain(audio_mixer, user_setting_audio_volume);

  al_attach_mixer_to_voice(audio_mixer, voice);
  al_attach_audio_stream_to_mixer(intro_music, audio_mixer);
  al_attach_audio_stream_to_mixer(level_music, audio_mixer);
  al_set_audio_stream_playing(intro_music, intro_music_playing);
  al_set_audio_stream_playing(level_music, level_music_playing);

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  std::vector<BlackHole*> black_holes;
  std::vector<Bullet*> bullets;
  std::vector<Entity*> entities;
  std::vector<Interviewer*> interviewers;
  std::vector<Star*> stars;
  srand(time(NULL));
  // srand(0);
  int current_level = 1;
  BlackHole::G = 6.67430e-11;
  for (int i = 0; i < current_level; i++) {
    BlackHole* bh = new BlackHole();
    black_holes.push_back(bh);
  }

  Manager manager(resolution.x - resolution.x*0.0608, resolution.y / 2);
  entities.push_back(&manager);

  Resume resume(0, resolution.y / 2, &black_holes, &manager);
  entities.push_back(&resume);

  for (int i = 0; i < 100; i++) {
    entities.push_back(new Star());
  }

  unsigned long long int score = 0;

  Meter rocket_fuel_gauge("ROCKET FUEL", line_height, line_height, resume.rocket_fuel/resume.rocket_fuel_max);
  Meter launch_velocity_gauge("LAUNCH VELOCITY", line_height, line_height*4, (float)(resume.v_init/resume.v_max));
  Meter time_dilation_gauge("TIME DILATION FACTOR", line_height, line_height*7  , 0);
  entities.push_back(&rocket_fuel_gauge);
  entities.push_back(&launch_velocity_gauge);
  entities.push_back(&time_dilation_gauge);

  GameState state = intro_screen;
  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;
  std::string level_string = "Level ";
  level_string += std::to_string(current_level);
  GameContext context(state);
  context.reset_time();
  context.resolution = resolution;
  context.prestige_level = 1;
  context.audio_volume = user_setting_audio_volume;

  std::stringstream vol_ss;
  vol_ss << "Volume " << " < " << round(context.audio_volume*100) << " >";
  std::string vol_str = vol_ss.str();

  std::stringstream res_ss;
  res_ss << "Screen Resolution " << " < " << resolution.display_string << " >";
  std::string res_str = res_ss.str();

  std::vector<MenuItem> menu {
    MenuItem("Continue", true, [&context, &audio_mixer, &intro_music, &level_music, &intro_music_playing, &level_music_playing]() {
      al_set_audio_stream_playing(level_music, false);
      al_set_audio_stream_playing(intro_music, false);
      al_set_mixer_gain(audio_mixer, context.audio_volume);
      context.show_menu = !context.show_menu;
      if (!context.show_menu) {
        al_set_audio_stream_playing(intro_music, intro_music_playing);
        al_set_audio_stream_playing(level_music, level_music_playing);
        context.menu_confirm_action();
      }
    }),
    MenuItem(vol_str.c_str(), false, []() { return; }),
    MenuItem(res_str.c_str(), false, []() { return; }),
    MenuItem("How to play", false, [&context]() { context.show_controls = true; }),
    MenuItem("Quit", false, [&done]() { done = true; }),
  };

  context.menu = menu;

#define KEY_SEEN     1
#define KEY_RELEASED 2
  unsigned char key[ALLEGRO_KEY_MAX];
  memset(key, 0, sizeof(key));

  context.menu_confirm_action = [&]() {
    user_settings_file.open(user_settings_filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
    if (user_settings_file) {
      user_settings_file << resolution.x << std::endl;
      user_settings_file << resolution.y << std::endl;
      user_settings_file << resolution.display_string << std::endl;
      user_settings_file << context.audio_volume << std::endl;
      user_settings_file.close();
    }

    if (resolution.x != context.resolution.x && resolution.y != context.resolution.y) {
      int button = al_show_native_message_box(
        disp,
        "Warning",
        "Are you sure?",
        "The game must be reset to change the screen resolution.",
        NULL,
        ALLEGRO_MESSAGEBOX_OK_CANCEL
      );
      if (button == 1) {
        resolution.x = context.resolution.x;
        resolution.y = context.resolution.y;
        resolution.display_string = context.resolution.display_string;

        user_settings_file.open(user_settings_filename,  std::fstream::in | std::fstream::out | std::fstream::trunc);
        user_settings_file << resolution.x << std::endl;
        user_settings_file << resolution.y << std::endl;
        user_settings_file << resolution.display_string << std::endl;
        user_settings_file << context.audio_volume << std::endl;
        user_settings_file.close();

        font = al_load_font("resources/Comfortaa/static/Comfortaa-Regular.ttf", resolution.y*0.02, 0);
        must_init(font, "load font");
        line_height = al_get_font_line_height(font);

        al_resize_display(disp, resolution.x, resolution.y);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        current_level = 1;
        level_string = "Level ";
        level_string += std::to_string(current_level);
        clear_entities<BlackHole>(black_holes);
        clear_entities<Star>(stars);
        entities.clear();
        score = 0;
        manager.respawn();
        resume.reinitialize();
        rocket_fuel_gauge.reinitialize();
        rocket_fuel_gauge.position.x = line_height;
        rocket_fuel_gauge.position.y = line_height;
        launch_velocity_gauge.reinitialize();
        launch_velocity_gauge.position.x = line_height;
        launch_velocity_gauge.position.y = line_height * 4;
        time_dilation_gauge.reinitialize();
        time_dilation_gauge.position.x = line_height;
        time_dilation_gauge.position.y = line_height * 7;
        entities.push_back(&manager);
        entities.push_back(&resume);
        entities.push_back(&rocket_fuel_gauge);
        entities.push_back(&launch_velocity_gauge);
        entities.push_back(&time_dilation_gauge);
        black_holes.push_back(new BlackHole());
        for (int i = 0; i < 100; i++) {
          entities.push_back(new Star());
        }
        resume.reset();
        context.state = GameState::intro_screen;
        context.reset_time();
        context.prestige_level = 1;
        context.menu_selected_index = 0;
        std::vector<MenuItem>::iterator menu_itr;
        for (menu_itr = context.menu.begin(); menu_itr < context.menu.end(); menu_itr++) {
          (*menu_itr).selected = false;
        }
        context.menu[context.menu_selected_index].selected = true;
        memset(key, 0, sizeof(key));
        al_flip_display();
      }
    }
  };

  al_clear_to_color(al_map_rgb(0, 0, 0));
  ALLEGRO_BITMAP* logo_img = al_load_bitmap("resources/JSS-cover-img.png");
  must_init(logo_img, "logo image");
  al_draw_scaled_bitmap(logo_img,
    0, 0,
    al_get_bitmap_width(logo_img),
    al_get_bitmap_height(logo_img),
    resolution.x/2 - resolution.x/20,
    resolution.y/2 - resolution.x/20,
    resolution.x/10,
    resolution.x/10,
    0
  );
  al_flip_display();

  al_start_timer(timer);
  while(1) {
    al_wait_for_event(queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      if (!context.show_menu) {
        context.show_controls = false;
        if(key[ALLEGRO_KEY_W] || key[ALLEGRO_KEY_UP])
          resume.handle_w();
        if(key[ALLEGRO_KEY_S] || key[ALLEGRO_KEY_DOWN])
          resume.handle_s();
        if(key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT])
          resume.handle_a();
        if(key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT])
          resume.handle_d();
        if(key[ALLEGRO_KEY_R])
          resume.reset();
        if(key[ALLEGRO_KEY_SPACE])
          resume.handle_space();

        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
          key[i] &= KEY_SEEN;

        redraw = true;
      }
      break;

    case ALLEGRO_EVENT_KEY_DOWN:
      key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
      if (context.show_menu) {
        context.show_controls = false;
        if(key[ALLEGRO_KEY_W] || key[ALLEGRO_KEY_UP]) {
          context.menu_item_up();
        }
        if(key[ALLEGRO_KEY_S] || key[ALLEGRO_KEY_DOWN]) {
          context.menu_item_down();
        }
        if(key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_LEFT]) {
          context.menu_item_left();
        }
        if(key[ALLEGRO_KEY_D] || key[ALLEGRO_KEY_RIGHT]) {
          context.menu_item_right();
        }
        if(key[ALLEGRO_KEY_ENTER]) {
          context.menu_action();
        }
        if(key[ALLEGRO_KEY_ESCAPE]) {
          context.show_menu = false;
          context.show_controls = false;
          context.menu_selected_index = 0;
          std::vector<MenuItem>::iterator menu_itr;
          for (menu_itr = context.menu.begin(); menu_itr < context.menu.end(); menu_itr++) {
            (*menu_itr).selected = false;
          }
          context.menu[context.menu_selected_index].selected = true;
          al_set_mixer_gain(audio_mixer, context.audio_volume);
          al_set_audio_stream_playing(intro_music, intro_music_playing);
          al_set_audio_stream_playing(level_music, level_music_playing);
          context.menu_confirm_action();
        }
        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
          key[i] &= KEY_SEEN;
      }
      else if(key[ALLEGRO_KEY_ESCAPE]) {
        // context.show_menu = !context.show_menu;
        context.show_menu = true;
        al_set_audio_stream_playing(level_music, false);
        al_set_audio_stream_playing(intro_music, false);
        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
          key[i] &= KEY_SEEN;
        // done = true;
      }

      break;
    case ALLEGRO_EVENT_KEY_UP:
      key[event.keyboard.keycode] &= KEY_RELEASED;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    }

    if(done)
      break;

    if (context.show_menu && !context.show_controls) {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_draw_rectangle(
        resolution.x/2 - resolution.x/5,
        resolution.y/2 - resolution.y/5,
        resolution.x/2 + resolution.x/5,
        resolution.y/2 + resolution.y/5,
        al_map_rgb(255,255,255),
        resolution.y*0.01
      );
      al_draw_filled_rectangle(
        resolution.x/2 - resolution.x/5,
        resolution.y/2 - resolution.y/5,
        resolution.x/2 + resolution.x/5,
        resolution.y/2 + resolution.y/5,
        al_map_rgb(0,0,0)
      );
      std::vector<MenuItem>::iterator menu_itr;
      int i = 1;
      for (menu_itr = context.menu.begin(); menu_itr < context.menu.end(); menu_itr++) {
        if ((*menu_itr).selected) {
          al_draw_text(font,
            al_map_rgb(255, 10, 10),
            resolution.x/2 - resolution.x/10,
            resolution.y/2 - resolution.y/10 + line_height*(++i),
            ALLEGRO_ALIGN_LEFT,
            (*menu_itr).label.c_str());

        } else {
          al_draw_text(font,
            al_map_rgb(255, 255, 255),
            resolution.x/2 - resolution.x/10,
            resolution.y/2 - resolution.y/10 + line_height*(++i),
            ALLEGRO_ALIGN_LEFT,
            (*menu_itr).label.c_str());
        }
      }
      al_draw_text(font,
                   al_map_rgb(255, 255, 255),
                   resolution.x/2,
                   resolution.y/2 - resolution.y/5,
                   ALLEGRO_ALIGN_CENTRE,
                   "Paused");
      al_flip_display();
    }

    if (context.show_controls) {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_draw_rectangle(
        resolution.x/2 - resolution.x/5,
        resolution.y/2 - resolution.y/5,
        resolution.x/2 + resolution.x/5,
        resolution.y/2 + resolution.y/5,
        al_map_rgb(255,255,255),
        resolution.y*0.01
      );
      al_draw_filled_rectangle(
        resolution.x/2 - resolution.x/5,
        resolution.y/2 - resolution.y/5,
        resolution.x/2 + resolution.x/5,
        resolution.y/2 + resolution.y/5,
        al_map_rgb(0,0,0)
      );
      al_draw_text(font,
        al_map_rgb(255, 255, 255),
        resolution.x/2 - resolution.x/8,
        resolution.y/2 - resolution.y/10,
        ALLEGRO_ALIGN_LEFT,
        "W/Up arrow: UP");
      al_draw_text(font,
        al_map_rgb(255, 255, 255),
        resolution.x/2 - resolution.x/8,
        resolution.y/2 - resolution.y/10 + line_height,
        ALLEGRO_ALIGN_LEFT,
        "A/Left arrow: ANGLE COUNTERCLOCKWISE");
      al_draw_text(font,
        al_map_rgb(255, 255, 255),
        resolution.x/2 - resolution.x/8,
        resolution.y/2 - resolution.y/10 + line_height*2,
        ALLEGRO_ALIGN_LEFT,
        "S/Down arrow: DOWN");
      al_draw_text(font,
        al_map_rgb(255, 255, 255),
        resolution.x/2 - resolution.x/8,
        resolution.y/2 - resolution.y/10 + line_height*3,
        ALLEGRO_ALIGN_LEFT,
        "D/Right arrow: ANGLE CLOCKWISE");
      al_draw_text(font,
        al_map_rgb(255, 255, 255),
        resolution.x/2 - resolution.x/8,
        resolution.y/2 - resolution.y/10 + line_height*4,
        ALLEGRO_ALIGN_LEFT,
        "Spacebar: LAUNCH");
      al_draw_text(font,
        al_map_rgb(255, 255, 255),
        resolution.x/2 - resolution.x/8,
        resolution.y/2 - resolution.y/10 + line_height*5,
        ALLEGRO_ALIGN_LEFT,
        "R: Reset");
      al_flip_display();
    }

    if (!context.show_menu && context.state == GameState::intro_screen) {
      std::chrono::milliseconds timespan(3000);
      std::this_thread::sleep_for(timespan);

      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_draw_text(font,
                   al_map_rgb(255, 255, 255),
                   resolution.x/2,
                   resolution.y/2,
                   ALLEGRO_ALIGN_CENTRE,
                   "Get a job");
      al_flip_display();
      std::this_thread::sleep_for(timespan);
      context.state = GameState::normal;
      al_stop_samples();
      intro_music_playing = true;
      level_music_playing = false;
      al_set_audio_stream_playing(level_music, level_music_playing);
      al_set_audio_stream_playing(intro_music, intro_music_playing);
      // al_play_sample(intro_music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
    }

    if (!context.show_menu && context.state == GameState::interlude && redraw && al_is_event_queue_empty(queue)) {
      al_clear_to_color(al_map_rgb(0, 0, 0));
      // ***********************************************************************
      // source: https://stackoverflow.com/questions/4713131
      auto b_itr = bullets.begin();
      while(b_itr != bullets.end()) {
        if((*b_itr)->marked_for_removal) {
          delete (*b_itr);
          b_itr = bullets.erase(b_itr);
        }
        else {
          if ((*b_itr)->x > resume.x && (*b_itr)->x < resume.x + resume.width
              && (*b_itr)->y > resume.y && (*b_itr)->y < resume.y + resume.height) {
            resume.fail = true;
            break;
          }
          b_itr++;
        }
      }
      // ***********************************************************************
      if (resume.fail) {
        context.state = GameState::interlude_fail;
        resume.interlude = false;
        resume.win = true;
        resume.fail = false;
      }
      else if (!resume.fail && context.time_remaining <= 0) {
        context.state = GameState::interlude_win;
        resume.interlude = false;
        resume.win = true;
      }

      std::vector<Entity*>::iterator itr = entities.begin();
      for (itr = entities.begin(); itr < entities.end(); itr++) {
        (*itr)->update();
        (*itr)->draw();
      }

      std::vector<Interviewer*>::iterator int_itr;
      for (int_itr = interviewers.begin(); int_itr < interviewers.end(); int_itr++) {
        (*int_itr)->update();
        (*int_itr)->draw();
      }

      for (b_itr = bullets.begin(); b_itr < bullets.end(); b_itr++) {
        (*b_itr)->update();
        (*b_itr)->draw();
      }
      al_draw_text(font,
                   al_map_rgb(255, 255, 255),
                   resolution.x/2,
                   line_height,
                   ALLEGRO_ALIGN_CENTRE,
                   "INTERVIEW");
      int text_width = al_get_text_width(font, "INTERVIEW");
      std::stringstream ss;
      ss << "Time remaining: " << std::setprecision(4) << context.time_remaining;
      std::string time_str = ss.str();
      al_draw_text(font,
                  al_map_rgb(255, 255, 255),
                  resolution.x/2 - text_width/2,
                  line_height*2,
                  ALLEGRO_ALIGN_LEFT,
                  time_str.c_str());
      context.time_remaining -= context.tick_rate; // has problems with tick rate consistency
      al_flip_display();
      redraw = false;
    }

    if (!context.show_menu && context.state == GameState::normal && redraw && al_is_event_queue_empty(queue)) {
      al_clear_to_color(al_map_rgb(0, 0, 0));

      double time_dilation_factor = 1;

      rocket_fuel_gauge.percentage = resume.rocket_fuel/resume.rocket_fuel_max;
      launch_velocity_gauge.percentage = (float)resume.v_init/resume.v_max;

      std::vector<Entity*>::iterator itr;
      for (itr = entities.begin(); itr < entities.end(); itr++) {
        (*itr)->update();
        (*itr)->draw();
      }

      std::vector<BlackHole*>::iterator bh_itr;
      for (bh_itr = black_holes.begin(); bh_itr < black_holes.end(); bh_itr++) {
        (*bh_itr)->update();
        (*bh_itr)->draw();
        double dx = (*bh_itr)->x - resume.x;
        double dy = (*bh_itr)->y - resume.y;
        double r = sqrt(pow(dx,2) + pow(dy,2));
        time_dilation_factor += (1 - (1 / sqrt(1 - (2*BlackHole::G*(*bh_itr)->m*(2e14/current_level)/(((*bh_itr)->radius + r)*c_squared)))));
      }

      time_dilation_factor += (1 - (1 / sqrt(1 - resume.get_scalar_velocity_squared()/c_squared)));
      if (time_dilation_factor != 0 && time_dilation_factor == time_dilation_factor) {
        context.time_remaining -= context.tick_rate / time_dilation_factor; // has problems with tick rate consistency
      }
      context.reference_time_remaining -= context.tick_rate; // has problems with tick rate consistency
      time_dilation_gauge.percentage = 1 - time_dilation_factor;
      if (time_dilation_gauge.percentage > 1) time_dilation_gauge.percentage = 1;

      if (context.time_remaining <= 0 || context.reference_time_remaining <= 0) {
        context.state = GameState::failure;
      }

      al_draw_text(font,
                   al_map_rgb(255, 255, 255),
                   resolution.x/2,
                   line_height,
                   ALLEGRO_ALIGN_CENTRE,
                   level_string.c_str());

      int text_width = al_get_text_width(font,level_string.c_str());
      std::stringstream ss;
      ss << "Score: " << score;
      std::string score_str = ss.str();
      al_draw_text(font,
                  al_map_rgb(255, 255, 255),
                  resolution.x/2 - text_width/2,
                  line_height*2,
                  ALLEGRO_ALIGN_LEFT,
                  score_str.c_str());

      ss.str("");
      ss << "Time remaining: " << std::setprecision(4) << context.time_remaining;
      std::string time_str = ss.str();
      al_draw_text(font,
                  al_map_rgb(255, 255, 255),
                  resolution.x/2 - text_width/2,
                  line_height*3,
                  ALLEGRO_ALIGN_LEFT,
                  time_str.c_str());
      ss.str("");
      ss << "Reference time: " << std::setprecision(4) << context.reference_time_remaining;
      time_str = ss.str();
      al_draw_text(font,
                  al_map_rgb(255, 255, 255),
                  resolution.x/2 - text_width/2,
                  line_height*4,
                  ALLEGRO_ALIGN_LEFT,
                  time_str.c_str());

      al_flip_display();
      redraw = false;
    }

    if (resume.win) {
      score += context.time_remaining * current_level * context.prestige_level;
      context.reset_time();

      if ((current_level%5) == 0) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2,
                     ALLEGRO_ALIGN_CENTRE,
                     "\"Hi! We'd like to bring you in for an interview to tell you about");
        al_draw_text(font,
                    al_map_rgb(255, 255, 255),
                    resolution.x/2,
                    resolution.y/2 + line_height,
                    ALLEGRO_ALIGN_CENTRE,
                    "the company and learn a little more about your background.\"");
        al_flip_display();
        std::chrono::milliseconds timespan(6000);
        std::this_thread::sleep_for(timespan);

        context.state = GameState::interlude;
        context.time_remaining = 30;
        resume.interlude = true;
        resume.reset();
        entities.clear();
        entities.push_back(&resume);
        for (int i = 0; i < current_level / 5; i++) {
          std::random_device rd;
          std::mt19937 gen(rd());
          std::uniform_int_distribution<int> x_pos_distr(200, resolution.x - 200);
          std::normal_distribution<float> y_pos_distr(resolution.y * 0.2, 20);
          std::normal_distribution<float> fire_rate(current_level%5+4, 2);
          int x = ((unsigned int)x_pos_distr(gen))%(resolution.x);
          int y = ((unsigned int)y_pos_distr(gen))%(resolution.y);// + (radius/2);
          interviewers.push_back(std::move(new Interviewer(x, y, abs(fire_rate(gen)), &bullets)));
        }
      }

      if (!context.show_menu && context.state == GameState::interlude_win && current_level%36 == 0) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2,
                     ALLEGRO_ALIGN_CENTRE,
                     "\"Thanks so much for your interest in this company! You made it to the final round of our candidate selection process.\"");
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2 + line_height,
                     ALLEGRO_ALIGN_CENTRE,
                     "\"Unfortunately, we decided to go with another candidate.\"");
        al_draw_text(font,
                    al_map_rgb(255, 255, 255),
                    resolution.x/2,
                    resolution.y/2 + line_height*2,
                    ALLEGRO_ALIGN_CENTRE,
                    "Congratulations on making it this far.");
        al_draw_text(font,
                    al_map_rgb(255, 255, 255),
                    resolution.x/2,
                    resolution.y/2 + line_height*3,
                    ALLEGRO_ALIGN_CENTRE,
                    "The job hunt continues...");
        al_flip_display();
        std::chrono::milliseconds timespan(6000);
        std::this_thread::sleep_for(timespan);

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2,
                     ALLEGRO_ALIGN_CENTRE,
                     "You will return to Level 1.");
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2 + line_height,
                     ALLEGRO_ALIGN_CENTRE,
                     "Your powerups remain intact.");
        al_flip_display();
        std::this_thread::sleep_for(timespan);

        current_level = 1;
        context.state = GameState::normal;
        context.prestige_level++;
        level_string = "Level ";
        level_string += std::to_string(current_level);
        clear_entities<Bullet>(bullets);
        clear_entities<Interviewer>(interviewers);
        clear_entities<BlackHole>(black_holes);
        clear_entities<Star>(stars);
        entities.clear();
        entities.push_back(&manager);
        entities.push_back(&resume);
        entities.push_back(&rocket_fuel_gauge);
        entities.push_back(&launch_velocity_gauge);
        entities.push_back(&time_dilation_gauge);
        for (int i = 0; i < 100; i++) {
          entities.push_back(new Star());
        }
        resume.reset();
        for (int i = 0; i < current_level; i++) {
          black_holes.push_back(new BlackHole());
        }
        resume.interlude = false;
        continue;
      }

      if (!context.show_menu && context.state == GameState::interlude_fail && current_level%36 == 0) {
        // final level
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2,
                     ALLEGRO_ALIGN_CENTRE,
                     "\"Thanks so much for your interest in this company! You made it to the final round of our candidate selection process.\"");
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2 + line_height,
                     ALLEGRO_ALIGN_CENTRE,
                     "\"Unfortunately, we decided to go with another candidate.\"");
        al_flip_display();
        std::chrono::milliseconds timespan(6000);
        std::this_thread::sleep_for(timespan);

        std::stringstream final_score_ss;
        final_score_ss << "Your final score was " << score << ".";
        std::string final_score_str = final_score_ss.str();

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2,
                     ALLEGRO_ALIGN_CENTRE,
                     "You will return to Level 1.");
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2 + line_height,
                     ALLEGRO_ALIGN_CENTRE,
                     "Your progress has been reset.");
        al_draw_text(font,
                    al_map_rgb(255, 255, 255),
                    resolution.x/2,
                    resolution.y/2 + line_height*2,
                    ALLEGRO_ALIGN_CENTRE,
                    final_score_str.c_str());
        al_flip_display();
        std::this_thread::sleep_for(timespan);
        current_level = 1;
        context.state = GameState::normal;
        level_string = "Level ";
        level_string += std::to_string(current_level);
        score = 0;
        clear_entities<Bullet>(bullets);
        clear_entities<Interviewer>(interviewers);
        clear_entities<BlackHole>(black_holes);
        clear_entities<Star>(stars);
        entities.clear();
        entities.push_back(&manager);
        entities.push_back(&resume);
        entities.push_back(&rocket_fuel_gauge);
        entities.push_back(&launch_velocity_gauge);
        entities.push_back(&time_dilation_gauge);
        for (int i = 0; i < 100; i++) {
          entities.push_back(new Star());
        }
        resume.reset();
        for (int i = 0; i < current_level; i++) {
          black_holes.push_back(new BlackHole());
        }
        resume.interlude = false;
        continue;
      }

      if (!context.show_menu && context.state == GameState::interlude_win && current_level%36 != 0) {
        context.state = GameState::normal;
        // init_level(entities, &resume, &manager);
        clear_entities<Bullet>(bullets);
        clear_entities<Interviewer>(interviewers);
        entities.clear();
        entities.push_back(&manager);
        entities.push_back(&resume);
        entities.push_back(&rocket_fuel_gauge);
        entities.push_back(&launch_velocity_gauge);
        entities.push_back(&time_dilation_gauge);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2,
                     ALLEGRO_ALIGN_CENTRE,
                     "\"Thanks so much for your interest in this company! Unfortunately, we will not be moving forward at this time.\"");
        al_draw_text(font,
                    al_map_rgb(255, 255, 255),
                    resolution.x/2,
                    resolution.y/2 + line_height,
                    ALLEGRO_ALIGN_CENTRE,
                    "Your persistence has rewarded you with a new ability.");
        score += current_level/5 * context.prestige_level * 100;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> powerup_dist(0, powerups.size());
        size_t new_powerup = powerup_dist(gen) % powerups.size();
        //unsigned int new_powerup = powerups[rand()%(powerups.size())];
        switch (new_powerup) {
        case Powerup::rocket_boost:
          resume.rocket_boost_enable();
          al_draw_text(font,
                       al_map_rgb(255, 255, 255),
                       resolution.x/2,
                       resolution.y/2 + line_height * 2,
                       ALLEGRO_ALIGN_CENTRE,
                       "You gain ROCKET BOOST.");
          break;
        case Powerup::gravity_reduction:
          BlackHole::G *= 0.90;
          al_draw_text(font,
                       al_map_rgb(255, 255, 255),
                       resolution.x/2,
                       resolution.y/2 + line_height * 2,
                       ALLEGRO_ALIGN_CENTRE,
                       "You gain GRAVITY REDUCTION.");
          break;
        case Powerup::gravity_increase:
          resume.v_init *= 1.15;
          resume.v_max *= 1.20;
          if (resume.v_init > resume.v_max) resume.v_init = resume.v_max;
          BlackHole::G *= 1.05;
          al_draw_text(font,
                      al_map_rgb(255, 255, 255),
                      resolution.x/2,
                      resolution.y/2 + line_height*2,
                      ALLEGRO_ALIGN_CENTRE,
                      "Your velocity has increased, but gravity is now stronger.");
          break;
        case Powerup::max_speed_reduction:
          resume.v_max *= 0.95;
          resume.v_init *= 1.20;
          if (resume.v_init > resume.v_max) resume.v_init = resume.v_max;
          al_draw_text(font,
                      al_map_rgb(255, 255, 255),
                      resolution.x/2,
                      resolution.y/2 + line_height*2,
                      ALLEGRO_ALIGN_CENTRE,
                      "Your launch velocity has increased, but your max velocity has decreased.");
          break;
        case Powerup::max_speed_increase:
          resume.v_max *= 1.15;
          al_draw_text(font,
                      al_map_rgb(255, 255, 255),
                      resolution.x/2,
                      resolution.y/2 + line_height*2,
                      ALLEGRO_ALIGN_CENTRE,
                      "Your max velocity has increased.");
          break;
        case Powerup::init_speed_reduction:
          resume.v_init *= 0.90;
          resume.v_max *= 1.20;
          al_draw_text(font,
                      al_map_rgb(255, 255, 255),
                      resolution.x/2,
                      resolution.y/2 + line_height*2,
                      ALLEGRO_ALIGN_CENTRE,
                      "Your max velocity has increased, but your launch velocity has decreased.");
          break;
        case Powerup::init_speed_increase:
          resume.v_init *= 1.20;
          if (resume.v_init > resume.v_max) resume.v_init = resume.v_max;
          al_draw_text(font,
                      al_map_rgb(255, 255, 255),
                      resolution.x/2,
                      resolution.y/2 + line_height*2,
                      ALLEGRO_ALIGN_CENTRE,
                      "Your launch velocity has increased.");
          break;
        default:
          resume.rocket_boost_enable();
          al_draw_text(font,
                       al_map_rgb(255, 255, 255),
                       resolution.x/2,
                       resolution.y/2 + line_height*2,
                       ALLEGRO_ALIGN_CENTRE,
                       "You gain ROCKET BOOST.");
          break;
        }

        current_level--;
        al_flip_display();
        std::chrono::milliseconds timespan(6000);
        std::this_thread::sleep_for(timespan);

        al_stop_samples();
        intro_music_playing = false;
        level_music_playing = true;
        al_set_audio_stream_playing(intro_music, intro_music_playing);
        al_set_audio_stream_playing(level_music, level_music_playing);
        // al_play_sample(level_music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
      }

      if (!context.show_menu && context.state == GameState::interlude_fail) {
        context.state = GameState::normal;
        // std::vector<Bullet*>::iterator itr = bullets.begin();
        // for (itr = bullets.begin(); itr < bullets.end(); itr++) {
        //   delete (*itr);
        // }
        // bullets.clear();
        // init_level(entities, &resume, &manager);
        clear_entities<Bullet>(bullets);
        clear_entities<Interviewer>(interviewers);
        entities.clear();
        entities.push_back(&manager);
        entities.push_back(&resume);
        entities.push_back(&rocket_fuel_gauge);
        entities.push_back(&launch_velocity_gauge);
        entities.push_back(&time_dilation_gauge);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font,
                     al_map_rgb(255, 255, 255),
                     resolution.x/2,
                     resolution.y/2,
                     ALLEGRO_ALIGN_CENTRE,
                     "\"Thanks so much for your interest in this company! Unfortunately, we will not be moving forward at this time.\"");
        al_draw_text(font,
                    al_map_rgb(255, 255, 255),
                    resolution.x/2,
                    resolution.y/2 + line_height,
                    ALLEGRO_ALIGN_CENTRE,
                    "You do not gain any new abilities.");

        current_level--;
        al_flip_display();
        std::chrono::milliseconds timespan(6000);
        std::this_thread::sleep_for(timespan);
        al_stop_samples();
        intro_music_playing = false;
        level_music_playing = true;
        al_set_audio_stream_playing(intro_music, intro_music_playing);
        al_set_audio_stream_playing(level_music, level_music_playing);
        // al_play_sample(level_music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
      }

      current_level++;
      level_string = "Level ";
      level_string += std::to_string(current_level);
      manager.respawn();
      clear_entities<BlackHole>(black_holes);
      clear_entities<Star>(stars);
      for (int i = 0; i < current_level; i++) {
        black_holes.push_back(new BlackHole());
      }
      for (int i = 0; i < 100; i++) {
        entities.push_back(new Star());
      }
      resume.reset();
    }

    if (!context.show_menu && context.state == GameState::failure) {
      al_clear_to_color(al_map_rgb(0, 0, 0));

      std::stringstream final_score_ss;
      final_score_ss << "Your final score was " << score << ".";
      std::string final_score_str = final_score_ss.str();
      al_draw_text(font,
                  al_map_rgb(255, 255, 255),
                  resolution.x/2,
                  resolution.y/2,
                  ALLEGRO_ALIGN_CENTRE,
                  final_score_str.c_str());
      al_flip_display();
      std::chrono::milliseconds timespan(6000);
      std::this_thread::sleep_for(timespan);

      current_level = 1;
      level_string = "Level ";
      level_string += std::to_string(current_level);
      clear_entities<BlackHole>(black_holes);
      clear_entities<Star>(stars);
      entities.clear();
      score = 0;
      entities.push_back(&manager);
      entities.push_back(&resume);
      entities.push_back(&rocket_fuel_gauge);
      entities.push_back(&launch_velocity_gauge);
      entities.push_back(&time_dilation_gauge);
      black_holes.push_back(new BlackHole());
      for (int i = 0; i < 100; i++) {
        entities.push_back(new Star());
      }
      resume.reinitialize();
      resume.reset();
      context.state = GameState::intro_screen;
      context.reset_time();
      al_flip_display();
    }
  }

  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  al_stop_samples();
  al_set_audio_stream_playing(intro_music, false);
  al_set_audio_stream_playing(level_music, false);
  al_destroy_voice(voice);
  al_destroy_mixer(audio_mixer);
  al_destroy_audio_stream(intro_music);
  al_destroy_audio_stream(level_music);
  // al_destroy_sample(intro_music);
  // al_destroy_sample(level_music);

  clear_entities<BlackHole>(black_holes);
  clear_entities<Star>(stars);

  user_settings_file.open(user_settings_filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
  if (user_settings_file) {
    user_settings_file << resolution.x << std::endl;
    user_settings_file << resolution.y << std::endl;
    user_settings_file << resolution.display_string << std::endl;
    user_settings_file << context.audio_volume << std::endl;
    user_settings_file.close();
  }

  return 0;
}
