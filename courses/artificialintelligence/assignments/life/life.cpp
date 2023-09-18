#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
  Cell* neighbours[NUM_NEIGHBOURS] = {nullptr, nullptr, nullptr, nullptr, nullptr,
                                      nullptr, nullptr, nullptr};  // the positions of neighbours
  explicit Cell(char startState)
  {
      state = startState;
  }
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

void PrintGrid(vector<vector<Cell>> grid);

int main() {
  int columns = 1;
  int rows = 1;
  int turns = 1;
  int turnsElapsed = 0;

  // set's the grid's size;
  // This is separate form initializing the grid state because the input is row based,
  // but the grid is column based to make the coordinate order correspond to traditional XY
  cin >> columns >> rows >> turns;
  vector<vector<Cell>> grid(columns);
  for(int c = 0; c < columns; c++)
  {
    for(int r = 0; r < rows; r++)
    { //fills it with dead cells for now
      Cell newCell = Cell('.');
      grid[c].push_back(newCell);
    }
  }
  //sets the initial state of the cells based on input
  for(int r = 0; r < rows; r++)
  {
    //takes a row of input
    string input;
    cin >> input;
    stringstream inputStream(input);
    char state;
    //plugs the input into the corresponding grid spaces
    for( int c = 0; c < columns; c++)
    {
      inputStream.get(state);
      grid[c][r].state = state;
    }
  }

  // Tells each cell who it neighbours
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      int north = c-1;
      int east = r+1;
      int south = c+1;
      int west = r-1;
      //if a cell is on the edge of the grid, it wraps around and neighbours the far edge
      if(north == -1)
      {
        north = columns - 1;
      }
      if(east == rows)
      {
        east = 0;
      }
      if(south == columns)
      {
        south = 0;
      }
      if(west == -1)
      {
        west = rows - 1;
      }
      //uses the calculated coordinates to assign neighbours
      grid[c][r].neighbours[0] = &grid[north][r];
      grid[c][r].neighbours[1] = &grid[north][east];
      grid[c][r].neighbours[2] = &grid[c][east];
      grid[c][r].neighbours[3] = &grid[south][east];
      grid[c][r].neighbours[4] = &grid[south][r];
      grid[c][r].neighbours[5] = &grid[south][west];
      grid[c][r].neighbours[6] = &grid[c][west];
      grid[c][r].neighbours[7] = &grid[north][west];
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

  //output
  PrintGrid(grid);

  return 0;
};

void PrintGrid(vector<vector<Cell>> grid)
{
  int columns = (int)grid.size();
  int rows = (int)grid[0].size();
  // prints the results
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      cout << grid[c][r].state;
    }
    cout << endl;
  }
}