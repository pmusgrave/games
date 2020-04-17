extern crate ncurses;
use ncurses::*;

static BOARD_HEIGHT: i32 = 22;
static BOARD_WIDTH: i32 = 22;

struct Point {
	x: usize,
	y: usize,
}

struct Piece {
	origin: Point,
	squares: [Point; 4],
}

impl Piece {
	fn move_down(&mut self) {
		self.origin.y += 1;
		for square in &mut self.squares {
			square.y += 1;
		}
	}

	fn move_left(&mut self) {
		self.origin.x -= 1;
		for square in &mut self.squares {
			square.x -= 1;
		}
	}

	fn move_right(&mut self) {
		self.origin.x += 1;
		for square in &mut self.squares {
			square.x += 1;
		}
	}
}

fn main() {
	// follow ncurses convention and access with y,x
	let mut grid = [[false; 10]; 20];
	
	setlocale(LcCategory::all, "");
	initscr();
	raw();
	keypad(stdscr(), true);
	halfdelay(3);
	noecho();
	curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

	refresh();

	let mut y: usize = 0;
	let mut x: usize = 0;
	let board_origin = Point { x:0, y:0 };
	let win = create_game_board(board_origin.y as i32, board_origin.x as i32);

	let mut test_piece = Piece {
		origin : Point { x:x, y:y },
		squares : [
			Point { x:x , y:y },
			Point { x:x +1, y:y },
			Point { x:x +2, y:y },
			Point { x:x +3, y:y },
		],
	};

	// let mut pieces: Vec<Piece>;

	let mut ch = getch();
	while ch != KEY_F(1)
	{
		y += 1;
		// x += 1;
		if x >= 7 {
			x = 0;
		}
		if y >= 20 {
			y = 0;
		}
		// let mut grid = clear_grid();
		// grid[y][x] = true;
		// grid[y][x+1] = true;
		// grid[y][x+2] = true;
		// grid[y][x+3] = true;

		let mut grid = update(&mut test_piece);
		render(&mut grid, win);

		ch = getch();
		match ch {
			KEY_LEFT => {
				if test_piece.origin.x > 0 {
					test_piece.move_left();
				}
			},
			KEY_RIGHT => {
				if test_piece.origin.x < 6 {
					test_piece.move_right();
				}
			},
			KEY_UP => {},
			KEY_DOWN => {},
			_ => {
				if test_piece.origin.y < 19 {
					test_piece.move_down();
				}
			},
		}
	}

	endwin();
}

fn create_game_board(x: i32, y: i32) -> WINDOW {
	let win = newwin(BOARD_HEIGHT, BOARD_WIDTH, y, x);
	box_(win,0,0);
	wrefresh(win);
	win
}

fn update(current_piece: &mut Piece) -> [[bool; 10]; 20] {
	let mut grid = clear_grid();
	for square in current_piece.squares.iter() {
		grid[square.y][square.x] = true;
	}

	grid
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
				// mvwprintw(new_win, y as i32 + 1, x as i32 + 1, "■");
				mvwprintw(new_win, y as i32 + 1, (x as i32)*2 + 1, "▓");
				mvwprintw(new_win, y as i32 + 1, (x as i32)*2 + 2, "▓");
			}
		}
	}

	wrefresh(new_win);
}

fn clear_grid() -> [[bool; 10]; 20] {
	return [[false; 10]; 20];
}