// follow ncurses convention and access with y,x

// #[derive(Default)]
pub struct State {
	pub grid: [[bool; 10]; 20],
	pub lines: u32,
	pub level: u32,
	pub tick_rate: i64,
	pub paused: bool,
}

impl State {
	pub fn new() -> Self {
		State {
			grid: [[false; 10]; 20],
			lines: 0,
			level: 1,
			tick_rate: 1000,
			paused: false,
		}
	}

	pub fn clear_grid(&mut self) {
		self.grid = [[false; 10]; 20];
	}
}
