extern crate rand;
use rand::Rng;
use crate::point::Point;

pub struct Piece {
	pub origin: Point,
	pub squares: [Point; 4],
}

impl Piece {
	pub fn new() -> Self {
		let mut rng = rand::thread_rng();
		let piece_rng: u8 = rng.gen_range(0,7);
		match piece_rng {
			0 => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:0, y:0 },
						Point { x:0, y:1 },
						Point { x:0, y:2 },
						Point { x:0, y:3 },
					],
				};
			},
			1 => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:0, y:0 },
						Point { x:0, y:1 },
						Point { x:1, y:0 },
						Point { x:1, y:1 },
					],
				};
			}
			2 => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:1, y:0 },
						Point { x:1, y:1 },
						Point { x:1, y:2 },
						Point { x:0, y:1 },
					],
				};
			}
			3 => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:1, y:0 },
						Point { x:1, y:1 },
						Point { x:0, y:1 },
						Point { x:0, y:2 },
					],
				};
			}
			4 => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:0, y:0 },
						Point { x:0, y:1 },
						Point { x:1, y:1 },
						Point { x:1, y:2 },
					],
				};
			}
			5 => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:0, y:0 },
						Point { x:1, y:0 },
						Point { x:1, y:1 },
						Point { x:1, y:2 },
					],
				};
			}
			6 => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:0, y:2 },
						Point { x:1, y:0 },
						Point { x:1, y:1 },
						Point { x:1, y:2 },
					],
				};
			}
			_ => {
				return Piece {
					origin : Point { x:0, y:0 },
					squares : [
						Point { x:0, y:0 },
						Point { x:0, y:1 },
						Point { x:0, y:2 },
						Point { x:0, y:3 },
					],
				};
			},
		}
	}

	pub fn move_down(&mut self) {
		self.origin.y += 1;
		for square in &mut self.squares {
			square.y += 1;
		}
	}

	pub fn move_left(&mut self) {
		self.origin.x -= 1;
		for square in &mut self.squares {
			square.x -= 1;
		}
	}

	pub fn move_right(&mut self) {
		self.origin.x += 1;
		for square in &mut self.squares {
			square.x += 1;
		}
	}
}

pub enum PieceVariant {
	I,
	O,
	T,
	S,
	Z,
	J,
	L,
}
