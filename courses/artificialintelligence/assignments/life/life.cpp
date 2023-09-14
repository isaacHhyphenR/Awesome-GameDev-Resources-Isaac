#include <fstream>;
#include <iostream>;

using namespace std;

int main(){
  int columns = 1;
  int lines = 1;
  int turns = 1;
  int turnsElapsed = 0;

  cout << "hello";

  char grid[1][1];
  
  while (turnsElapsed < turns)
  {
  }

  cout << grid;

  return 0;
};


struct Cell {
	char state = '.';
	Vector2 position; //the position of this cell
	Vector2 neighbours[4]; //the positions of neighbours
	Cell(Vector2 pos) //determines the neighbours
	{
		position = pos;
        neighbours[0] = Vector2(position.x, position.y - 1);
		neighbours[1] = Vector2(position.x + 1, position.y);
        neighbours[2] = Vector2(position.x, position.y + 1);
        neighbours[3] = Vector2(position.x - 1, position.y);
	}
};

struct Vector2
{
    Vector2() {}
	Vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	int x;
	int y;
};