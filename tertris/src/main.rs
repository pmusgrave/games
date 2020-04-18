mod point;
mod piece;
mod state;
extern crate ncurses;
use ncurses::*;
use point::Point;
use piece::Piece;
use state::State;

static BOARD_HEIGHT: i32 = 22;
static BOARD_WIDTH: i32 = 22;

fn main() {
	// Init ncurses
	setlocale(LcCategory::all, "");
	initscr();
	raw();
	keypad(stdscr(), true);
	halfdelay(3);
	noecho();
	curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
	refresh();

	// Init game board
	let mut state: State = State::new();
	let y: usize = 0;
	let x: usize = 3;
	let board_origin = Point { x:0, y:0 };
	let win = create_game_board(board_origin);

	let mut current_piece = Piece {
		origin : Point { x:x, y:y },
		squares : [
			Point { x:x , y:y },
			Point { x:x , y:y + 1},
			Point { x:x + 1 , y:y },
			Point { x:x + 1, y:y + 1},
		],
	};

	let mut pieces: Vec<Piece> = vec![];

	let mut ch = getch();
	while ch != KEY_F(1)
	{
		update(&mut state, &pieces, &mut current_piece);
		render(&mut state, win);

		ch = getch();
		match ch {
			KEY_LEFT => {
				if !collision_left(&state, &current_piece) {
					current_piece.move_left();
				}
			},
			KEY_RIGHT => {
				if !collision_right(&state, &current_piece) {
					current_piece.move_right();
				}
			},
			KEY_UP => {},
			KEY_DOWN => {},
			_ => {
				if !collision_down(&state, &current_piece) {
					current_piece.move_down();
				}
				else {
					let locked_piece = current_piece;
					pieces.push(locked_piece);
					current_piece = Piece {
						origin : Point { x:x, y:y },
						squares : [
							Point { x:x , y:y },
							Point { x:x , y:y + 1},
							Point { x:x + 1 , y:y },
							Point { x:x + 1, y:y + 1},
						],
					};
				}
			},
		}
	}

	endwin();
}

fn create_game_board(origin: Point) -> WINDOW {
	let win = newwin(BOARD_HEIGHT, 
		BOARD_WIDTH, 
		origin.y as i32, 
		origin.x as i32);
	box_(win,0,0);
	wrefresh(win);
	win
}

fn collision_down(state: &State, piece: &Piece) -> bool {
	for square in piece.squares.iter() {
		if square.y >= 19 
		|| (state.grid[square.y + 1][square.x] 
			&& !is_square_of_current_piece(
				&Point {
					x: square.x,
					y: square.y + 1,
				},
				piece))
		{
			return true;
		}
	}

	false
}

fn collision_left(state: &State, piece: &Piece) -> bool {
	for square in piece.squares.iter() {
		if square.x == 0 
		|| (state.grid[square.y][square.x - 1] 
			&& !is_square_of_current_piece(
				&Point {
					x: square.x - 1,
					y: square.y,
				},
				piece))
		{
			return true;
		}
	}

	false
}

fn collision_right(state: &State, piece: &Piece) -> bool {
	for square in piece.squares.iter() {
		if square.x >= 9 
		|| (state.grid[square.y][square.x + 1] 
			&& !is_square_of_current_piece(
				&Point {
					x: square.x + 1,
					y: square.y,
				},
				piece))
		{
			return true;
		}
	}

	false
}

fn is_square_of_current_piece(square: &Point, piece: &Piece) -> bool {
	for s in piece.squares.iter() {
		if s.y == square.y && s.x == square.x {
			return true;			
		}
	}

	false
}

fn update(state: &mut State, locked_pieces: &Vec<Piece>, current_piece: &mut Piece) {
	state.clear_grid();
	for piece in locked_pieces {
		for square in piece.squares.iter() {
			state.grid[square.y][square.x] = true;
		}
	}

	for square in current_piece.squares.iter() {
		state.grid[square.y][square.x] = true;
	}
}

fn render(state: &State, win: WINDOW) {
	delwin(win);
	let mut max_x = 0;
	let mut max_y = 0;
	getmaxyx(stdscr(), &mut max_y, &mut max_x);

	// let start_y = (max_y - BOARD_HEIGHT) / 2;
	// let start_x = (max_x - BOARD_WIDTH) / 2;
	let new_win = create_game_board(Point{ x:0, y:0 });

	for (y, row) in state.grid.iter().enumerate() {
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
