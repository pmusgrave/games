extern crate rand;
use rand::Rng;
use crate::point::Point;

pub struct Piece {
	pub origin: Point,
	pub squares: [Point; 4],
	variant: PieceVariant,
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
					variant: PieceVariant::I
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
					variant: PieceVariant::O
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
					variant: PieceVariant::T
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
					variant: PieceVariant::S
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
					variant: PieceVariant::Z
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
					variant: PieceVariant::J
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
					variant: PieceVariant::L
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
					variant: PieceVariant::I
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

	pub fn rotate(&mut self) {
		match self.variant {
			PieceVariant::I => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 2, y:self.origin.y },
					Point { x:self.origin.x + 3, y:self.origin.y },
				];
				self.variant = PieceVariant::I2;
			},
			PieceVariant::I2 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y + 1 },
					Point { x:self.origin.x, y:self.origin.y + 2 },
					Point { x:self.origin.x, y:self.origin.y + 3 },
				];
				self.variant = PieceVariant::I;
			}
			PieceVariant::O => {},
			PieceVariant::T => {},
			PieceVariant::S => {},
			PieceVariant::Z => {},
			PieceVariant::J => {},
			PieceVariant::L => {},
		}
	}
}

pub enum PieceVariant {
	I,
	I2,
	O,
	T,
	S,
	Z,
	J,
	L,
}
