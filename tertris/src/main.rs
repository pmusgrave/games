extern crate ncurses;
use ncurses::*;

static BOARD_HEIGHT: i32 = 19;
static BOARD_WIDTH: i32 = 12;

fn main() {
	// follow ncurses convention and access with y,x
	let mut grid = [[false; 10]; 20];
	
	setlocale(LcCategory::all, "");
	initscr();
	raw();
	keypad(stdscr(), true);
	noecho();
	curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

	refresh();

	// mvwprintw(win, 1, 1, "■");
	// mvwprintw(win, 1, 2, "■");
	// mvwprintw(win, 1, 3, "■");
	// mvwprintw(win, 1, 4, "■");
	// wrefresh(win);

	let mut y:usize= 0;
	let mut x:usize = 0;
	let win = create_game_board(0,0);

	let mut ch = getch();
	while ch != KEY_F(1)
	{
		y += 1;
		// x += 1;
		if x >= 7 {
			x = 0;
		}
		if y >= 17 {
			y = 0;
		}
		let mut grid = clear_grid();
		grid[y][x] = true;
		grid[y][x+1] = true;
		grid[y][x+2] = true;
		grid[y][x+3] = true;
		
		render(&mut grid, win);

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

fn render(grid: &mut [[bool; 10]; 20], win: WINDOW) {
	delwin(win);
	let mut max_x = 0;
	let mut max_y = 0;
	getmaxyx(stdscr(), &mut max_y, &mut max_x);

	let start_y = (max_y - BOARD_HEIGHT) / 2;
	let start_x = (max_x - BOARD_WIDTH) / 2;
	let new_win = create_game_board(0, 0);

	for (y, row) in grid.iter().enumerate() {
		for (x, element) in row.iter().enumerate() {
			if *element {
				mvwprintw(new_win, y as i32 + 1, x as i32 + 1, "■");
			}
		}
	}

	wrefresh(new_win);
}

fn clear_grid() -> [[bool; 10]; 20] {
	return [[false; 10]; 20];
}