mod point;
mod piece;
mod state;
extern crate timer;
extern crate chrono;
extern crate ncurses;
use ncurses::*;
use std::sync::{Arc, Mutex};
use point::Point;
use piece::Piece;
use state::State;

use std::{thread, time};

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

	print_score_board(&state);

	let advance_piece = Arc::new(Mutex::new(true));

	let mut ch = getch();
	while ch != KEY_F(1)
	{
		if state.paused {
			print_paused_box();
		}
		else{
			update(&mut state, &mut locked_squares, &mut current_piece);
			render(&mut state, win);	
		}
		

		ch = getch();
		match ch {
			27 => { // escape key
				state.paused = !state.paused;
			},
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
				for square in &current_piece.squares {
					locked_squares.push(Point { x: square.x, y: square.y });
				}
				current_piece = Piece::new();
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

					// timer to handle piece advance rate
					let tick_rate = state.tick_rate as u64;
					{
						let advance_piece = advance_piece.clone();
						thread::spawn(move || {
							let delay = time::Duration::from_millis(tick_rate);
							thread::sleep(delay);
							*advance_piece.lock().unwrap() = true;
						});
					}

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

fn print_paused_box() {
	let paused_box_origin = Point { x:7, y:7 };
	let paused_box = newwin(
		3,
		8,
		paused_box_origin.y as i32,
		paused_box_origin.x as i32);
	box_(paused_box,0,0);
	mvwprintw(paused_box, 1, 1, "Paused");
	wrefresh(paused_box);
}

fn print_score_board(state: &State) {
	let score_board_origin = Point { x:(BOARD_WIDTH + 1) as usize, y:1 };
	let score_board = newwin(
		5,
		15,
		score_board_origin.y as i32,
		score_board_origin.x as i32);
	box_(score_board,0,0);
	let level_str = format!("Level: {}", state.level);
	let lines_str = format!("Lines: {}", state.lines);
	mvwprintw(score_board, 1, 1, &level_str);
	mvwprintw(score_board, 2, 1, &lines_str);
	wrefresh(score_board);
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
	locked_squares: &mut Vec<Point>,
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

		state.level = state.lines / 10;
		if state.level < 9 {
			state.tick_rate = 1000 - (state.level as i64)*100;
		}
		else {
			state.tick_rate = 1000 / (state.level as i64);
		};
	}

	print_score_board(&state);
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
