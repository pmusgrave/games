// follow ncurses convention and access with y,x
// let mut grid = [[false; 10]; 20];
#[derive(Default)]
pub struct State {
	pub grid: [[bool; 10]; 20],
	pub level: u32,
}

impl State {
	fn default() -> Self {
		State {
			grid: [[false; 10]; 20],
			level: 1,
		}
	}
	
	pub fn clear_grid(&mut self) {
		self.grid = [[false; 10]; 20];
	}
}