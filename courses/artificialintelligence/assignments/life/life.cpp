#include <fstream>
#include <iostream>

using namespace std;

const int NUM_NEIGHBOURS = 8;

struct Vector2 {
  Vector2() {}
  Vector2(int _x, int _y) {
    x = _x;
    y = _y;
  }
  int x;
  int y;
};

struct Cell {
  char state = '.';
  char tempState = '.';  // stores the state it will be next turn
  Vector2 position;      // the position of this cell
  Cell* neighbours[NUM_NEIGHBOURS] = {nullptr, nullptr, nullptr, nullptr, nullptr,
                                      nullptr, nullptr, nullptr};  // the positions of neighbours
  // Cell(){};
  void CalculateState()  // determines whether to live or die
  {
    // counts living neighbors
    int livingNeighbours = 0;
    for (int i = 0; i < NUM_NEIGHBOURS; i++) {
      if (neighbours[i] != nullptr && neighbours[i]->state == '#') {
        livingNeighbours++;
      }
    }
    // sets state to alive if rules met, otherwise die
    if (state == '#' && (livingNeighbours == 2 || livingNeighbours == 3)) {
      tempState = '#';
    } else if (state == '.' && livingNeighbours == 3) {
      tempState = '#';
    } else {
      tempState = '.';
    }
  }
  void EndOfTurn()  // cleans up at the end of the turn
  {
    state = tempState;
  }
};

int main() {
  int columns = 1;
  int rows = 1;
  int turns = 1;
  int turnsElapsed = 0;

  // gets input
  cout << "How many columns will the grid have?";
  cin >> columns;
  cout << "How many rows will the grid have?";
  cin >> rows;
  cout << "How many turns will the game run for?";
  cin >> turns;

  Cell grid[columns][rows];
  // sets up the cell neighbours
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      grid[c][r].position = Vector2(c, r);
      if (c > 0)  // north
      {
        grid[c][r].neighbours[0] = &grid[c - 1][r];
      }
      if (c > 0 && r < rows - 1)  // northeast
      {
        grid[c][r].neighbours[1] = &grid[c - 1][r + 1];
      }
      if (r < rows - 1)  // east
      {
        grid[c][r].neighbours[2] = &grid[c][r + 1];
      }
      if (c < columns - 1 && r < rows - 1)  // southeast
      {
        grid[c][r].neighbours[3] = &grid[c + 1][r + 1];
      }
      if (c < columns - 1)  // south
      {
        grid[c][r].neighbours[4] = &grid[c + 1][r];
      }
      if (c < columns - 1 && r > 0)  // southwest
      {
        grid[c][r].neighbours[5] = &grid[c + 1][r - 1];
      }
      if (r > 0)  // west
      {
        grid[c][r].neighbours[6] = &grid[c][r - 1];
      }
      if (c > 0 && r > 0)  // northwest
      {
        grid[c][r].neighbours[7] = &grid[c - 1][r - 1];
      }
    }
  }

  // executes the game
  while (turnsElapsed < turns) {
    turnsElapsed++;
    // every cell figures out what it will do
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++) {
        grid[c][r].CalculateState();
      }
    }
    // every cell now actually does that thing since the buffer is no longer needed
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++) {
        grid[c][r].EndOfTurn();
      }
    }
  }

  // prints the results
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      cout << grid[c][r].state;
    }
    cout << endl;
  }

  return 0;
};
