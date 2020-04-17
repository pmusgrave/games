use crate::point::Point;

pub struct Piece {
	pub origin: Point,
	pub squares: [Point; 4],
}

impl Piece {
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
