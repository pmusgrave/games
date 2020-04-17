extern crate ncurses;
use ncurses::*;

fn main() {
  initscr();
  printw("hello, world");
  refresh();
  getch();
  endwin();
}
