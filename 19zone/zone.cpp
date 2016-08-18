/*
 * 将对象根据它们的位置存储在数据结构中，来有效的定位对象。
 * 类似AOI中的十字链表
 * */

// version 01 

void handleMelee(Unit* units[], int numUnits) {
	for (int a = 0; a < numUnits - 1; a++) {
		for (int b = a + 1; b < numUnits; b++) {
			if (units[a]->position() == units[b]->position()) {
				handleAttack(units[a], units[b]);
			}
		}
	}
}

// version 02

class Unit
{
	friend class Grid;

public:
	Unit(Grid* grid, double x, double y) : grid_(grid), x_(x), y_(y)， prev_(NULL), next_(NULL)
	{
		grid_->add(this);
	}

	void move(double x, double y) {
		grid_->move(this, x, y);
	}

private:
	double x_, y_;
	Grid* grid_;

	Unit* prev_;
	Unit* next_;
};

class Grid
{
public:
	Grid() {
		// Clear the grid.
		for (int x = 0; x < NUM_CELLS; x++) {
			for (int y = 0; y < NUM_CELLS; y++) {
				cells_[x][y] = NULL;
			}
		}
	}

	void add(Unit* unit) {
		// Determine which grid cell it's in.
		int cellX = (int)(unit->x_ / Grid::CELL_SIZE);
		int cellY = (int)(unit->y_ / Grid::CELL_SIZE);

		// Add to the front of list for the cell it's in.
		unit->prev_ = NULL;
		unit->next_ = cells_[cellX][cellY];
		cells_[cellX][cellY] = unit;

		if (unit->next_ != NULL) {
			unit->next_->prev_ = unit;
		}
	}


	void handleMelee() {
		for (int x = 0; x < NUM_CELLS; x++) {
			for (int y = 0; y < NUM_CELLS; y++) {
				handleCell(cells_[x][y]);
			}
		}
	}

	void Grid::handleUnit(Unit* unit, Unit* other) {
		while (other != NULL) {
			if (distance(unit, other) < ATTACK_DISTANCE) {
				handleAttack(unit, other);
			}

			other = other->next_;
		}
	}

	void Grid::handleCell(int x, int y) {
		Unit* unit = cells_[x][y];
		while (unit != NULL) {
			// Handle other units in this cell.
			handleUnit(unit, unit->next_);

			// Also try the neighboring cells.
			if (x > 0 && y > 0) handleUnit(unit, cells_[x - 1][y - 1]);
			if (x > 0) handleUnit(unit, cells_[x - 1][y]);
			if (y > 0) handleUnit(unit, cells_[x][y - 1]);
			if (x > 0 && y < NUM_CELLS - 1) {
				handleUnit(unit, cells_[x - 1][y + 1]);
			}

			unit = unit->next_;
		}
	}

	void move(Unit* unit, double x, double y) {
		int oldCellX = (int)(unit->x_ / Grid::CELL_SIZE);
		int oldCellY = (int)(unit->y_ / Grid::CELL_SIZE);

		int cellX = (int)(x / Grid::CELL_SIZE);
		int cellY = (int)(y / Grid::CELL_SIZE);

		unit->x_ = x;
		unit->y_ = y;

		if (oldCellX == cellX && oldCellY == cellY) 
			return;

		if (unit->prev_ != NULL) {
			unit->prev_->next_ = unit->next_;
		}

		if (unit->next_ != NULL) {
			unit->next_->prev_ = unit->prev_;
		}

		if (cells_[oldCellX][oldCellY] == unit) {
			cells_[oldCellX][oldCellY] = unit->next_;
		}

		add(unit);
	}

	static const int NUM_CELLS = 10;
	static const int CELL_SIZE = 20;
private:
	Unit* cells_[NUM_CELLS][NUM_CELLS];
};

