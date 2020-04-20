extern crate rand;
use rand::Rng;
use crate::point::Point;

pub enum PieceVariant {
	I,
	I2,
	O,
	T,
	T2,
	T3,
	T4,
	S,
	S2,
	Z,
	Z2,
	J,
	J2,
	J3,
	J4,
	L,
	L2,
	L3,
	L4,
}

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
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:4, y:0 },
						Point { x:4, y:1 },
						Point { x:4, y:2 },
						Point { x:4, y:3 },
					],
					variant: PieceVariant::I
				};
			},
			1 => {
				return Piece {
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:4, y:0 },
						Point { x:4, y:1 },
						Point { x:5, y:0 },
						Point { x:5, y:1 },
					],
					variant: PieceVariant::O
				};
			}
			2 => {
				return Piece {
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:4, y:0 },
						Point { x:4, y:1 },
						Point { x:4, y:2 },
						Point { x:5, y:1 },
					],
					variant: PieceVariant::T
				};
			}
			3 => {
				return Piece {
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:5, y:0 },
						Point { x:5, y:1 },
						Point { x:4, y:1 },
						Point { x:4, y:2 },
					],
					variant: PieceVariant::S
				};
			}
			4 => {
				return Piece {
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:4, y:0 },
						Point { x:4, y:1 },
						Point { x:5, y:1 },
						Point { x:5, y:2 },
					],
					variant: PieceVariant::Z2
				};
			}
			5 => {
				return Piece {
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:4, y:0 },
						Point { x:5, y:0 },
						Point { x:5, y:1 },
						Point { x:5, y:2 },
					],
					variant: PieceVariant::L
				};
			}
			6 => {
				return Piece {
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:4, y:2 },
						Point { x:5, y:0 },
						Point { x:5, y:1 },
						Point { x:5, y:2 },
					],
					variant: PieceVariant::J3
				};
			}
			_ => {
				return Piece {
					origin : Point { x:4, y:0 },
					squares : [
						Point { x:4, y:0 },
						Point { x:4, y:1 },
						Point { x:4, y:2 },
						Point { x:4, y:3 },
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
					Point { x:self.origin.x, y:self.origin.y - 1 },
					Point { x:self.origin.x, y:self.origin.y - 2 },
					Point { x:self.origin.x, y:self.origin.y - 3 },
				];
				self.variant = PieceVariant::I;
			},
			PieceVariant::O => {},
			PieceVariant::T => {
				self.squares = [
					Point { x:self.origin.x , y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 2, y:self.origin.y },
					Point { x:self.origin.x + 1 , y:self.origin.y + 1},
				];
				self.variant = PieceVariant::T2;
			},
			PieceVariant::T2 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y - 1 },
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y + 1},
					Point { x:self.origin.x + 1, y:self.origin.y },
				];
				self.variant = PieceVariant::T3;
			},
			PieceVariant::T3 => {
				self.squares = [
					Point { x:self.origin.x , y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 2, y:self.origin.y },
					Point { x:self.origin.x + 1 , y:self.origin.y - 1},
				];
				self.variant = PieceVariant::T4;
			},
			PieceVariant::T4 => {
				self.squares = [
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y + 1},
					Point { x:self.origin.x + 1, y:self.origin.y + 2},
					Point { x:self.origin.x , y:self.origin.y + 1 },
				];
				self.variant = PieceVariant::T;
			},
			PieceVariant::S => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y + 1 },
					Point { x:self.origin.x + 2, y:self.origin.y + 1},
				];
				self.variant = PieceVariant::S2;
			},
			PieceVariant::S2 => {
				self.squares = [
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y + 1},
					Point { x:self.origin.x, y:self.origin.y + 1},
					Point { x:self.origin.x, y:self.origin.y + 2},
				];
				self.variant = PieceVariant::S;
			},
			PieceVariant::Z => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y + 1 },
					Point { x:self.origin.x + 1, y:self.origin.y + 1 },
					Point { x:self.origin.x + 1, y:self.origin.y + 2 },
				];
				self.variant = PieceVariant::Z2;
			},
			PieceVariant::Z2 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y + 1},
					Point { x:self.origin.x + 1, y:self.origin.y + 1},
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 2, y:self.origin.y },
				];
				self.variant = PieceVariant::Z;
			},
			PieceVariant::J => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 2, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y - 1},
				];
				self.variant = PieceVariant::J2;
			},
			PieceVariant::J2 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y - 1 },
					Point { x:self.origin.x, y:self.origin.y - 2 },
					Point { x:self.origin.x - 1, y:self.origin.y },
				];
				self.variant = PieceVariant::J3;
			},
			PieceVariant::J3 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x - 1, y:self.origin.y },
					Point { x:self.origin.x - 2, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y + 1},
				];
				self.variant = PieceVariant::J4;
			},
			PieceVariant::J4 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x - 1, y:self.origin.y },
					Point { x:self.origin.x - 1, y:self.origin.y + 1 },
					Point { x:self.origin.x - 1, y:self.origin.y + 2},
				];
				self.variant = PieceVariant::J;
			},
			PieceVariant::L => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 2, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y + 1},
				];
				self.variant = PieceVariant::L2;
			},
			PieceVariant::L2 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y - 1 },
					Point { x:self.origin.x, y:self.origin.y - 2 },
					Point { x:self.origin.x + 1, y:self.origin.y },
				];
				self.variant = PieceVariant::L3;
			},
			PieceVariant::L3 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x - 1, y:self.origin.y },
					Point { x:self.origin.x - 2, y:self.origin.y },
					Point { x:self.origin.x, y:self.origin.y - 1},
				];
				self.variant = PieceVariant::L4;
			},
			PieceVariant::L4 => {
				self.squares = [
					Point { x:self.origin.x, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y },
					Point { x:self.origin.x + 1, y:self.origin.y + 1 },
					Point { x:self.origin.x + 1, y:self.origin.y + 2},
				];
				self.variant = PieceVariant::L;
			},
		}
	}
}
