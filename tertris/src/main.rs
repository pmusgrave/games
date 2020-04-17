extern crate ncurses;
use ncurses::*;

static BOARD_HEIGHT: i32 = 20;
static BOARD_WIDTH: i32 = 10;

fn main() {
	setlocale(LcCategory::all, "");
  initscr();
  raw();
  keypad(stdscr(), true);
  noecho();
  curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

  refresh();

  let mut max_x = 0;
  let mut max_y = 0;
  getmaxyx(stdscr(), &mut max_y, &mut max_x);

  let mut start_y = (max_y - BOARD_HEIGHT) / 2;
  let mut start_x = (max_x - BOARD_WIDTH) / 2;
  let mut win = create_game_board(0, 0);

  mvwprintw(win, 1, 1, "■");
  mvwprintw(win, 1, 2, "■");
  mvwprintw(win, 1, 3, "■");
  mvwprintw(win, 1, 4, "■");
  wrefresh(win);

  let mut ch = getch();
  while ch != KEY_F(1)
  {
    ch = getch();
  }

  endwin();
}

fn create_game_board(x: i32, y: i32) -> WINDOW {
	let win = newwin(BOARD_HEIGHT, BOARD_WIDTH, y, x);
	box_(win,0,0);
	wrefresh(win);
	win
}

fn destroy_win(win: WINDOW) {
  let ch = ' ' as chtype;
  wborder(win, ch, ch, ch, ch, ch, ch, ch, ch);
  wrefresh(win);
  delwin(win);
}
