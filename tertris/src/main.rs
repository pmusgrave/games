mod point;
mod piece;
mod state;
extern crate timer;
extern crate chrono;
extern crate ncurses;
use ncurses::*;
use std::thread;
use std::sync::{Arc, Mutex};
use point::Point;
use piece::Piece;
use piece::PieceVariant;
use state::State;

static BOARD_HEIGHT: i32 = 22;
static BOARD_WIDTH: i32 = 22;

fn main() {
	// Init ncurses
	setlocale(LcCategory::all, "");
	initscr();
	raw();
	keypad(stdscr(), true);
	halfdelay(1);
	noecho();
	curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
	refresh();

	// Init game board
	let mut state: State = State::new();
	let board_origin = Point { x:0, y:0 };
	let win = create_game_board(board_origin);
	let mut current_piece = Piece::new();
	let mut locked_squares: Vec<Point> = vec![];

	// init timer to handle piece advance rate
	let timer = timer::Timer::new();
	let advance_piece = Arc::new(Mutex::new(false));
	let guard = {
		let advance_piece = advance_piece.clone();
	  timer.schedule_repeating(chrono::Duration::milliseconds(state.tick_rate), move || {
	  	*advance_piece.lock().unwrap() = true;
	  })
	};	

	let mut ch = getch();
	while ch != KEY_F(1)
	{
		update(&mut state, &mut locked_squares, &mut current_piece);
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
			KEY_UP => {
				while !collision_down(&state, &current_piece) {
					current_piece.move_down();
				} 
			},
			KEY_DOWN => {
				if !collision_down(&state, &current_piece) {
					current_piece.move_down();
				} 
			},
			122 => { // not sure why, there's a bug when I don't use magic numbers
				current_piece.rotate(&state);
			},
			_ => {
				if *advance_piece.lock().unwrap() {
					*advance_piece.lock().unwrap() = false;
					if !collision_down(&state, &current_piece) {
						current_piece.move_down();
					}
					else {
						for square in &current_piece.squares {
							locked_squares.push(Point { x: square.x, y: square.y });
						}
						current_piece = Piece::new();
					}
				}
			},
		}
	}

	drop(guard);
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

fn update(
	mut state: &mut State,
	mut locked_squares: &mut Vec<Point>,
	current_piece: &mut Piece) 
{
	state.clear_grid();
	for point in locked_squares.iter() {
		state.grid[point.y][point.x] = true;
	}

	for square in current_piece.squares.iter() {
		state.grid[square.y][square.x] = true;
	}

	for (y, row) in state.grid.iter().enumerate() {
		let mut row_is_full = true;
		for (x, _element) in row.iter().enumerate() {
			let square = Point { x: x, y: y };
			if state.grid[y][x] == false || is_square_of_current_piece(&square, &current_piece) {
				row_is_full = false;
				break;
			}
		}
		if row_is_full {
			state.lines += 1;
			locked_squares.retain(|s| s.y != y);
			for locked_square in locked_squares.iter_mut() {
				if locked_square.y < 19 && locked_square.y < y {
					locked_square.y += 1;	
				}
			}
		}

		state.level = state.lines % 10;
		if state.level < 9 {
			state.tick_rate = 1000 - (state.level as i64)*100;
		}
		else {
			state.tick_rate = 1000 / (state.level as i64);
		};
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
