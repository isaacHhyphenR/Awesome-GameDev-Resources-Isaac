#include <iostream>
#include <vector>

using namespace std;


////////STRUCTS
struct Vector2
{
  int x;
  int y;
  explicit Vector2(int _x, int _y)
  {
    x = _x;
    y = _y;
  }
};

struct Node
{
  bool visited = false;
  char left = '|';
  char bottom = '_';
};

struct Grid
{
  int width;
  int height;
  vector<Node*> nodes;
  explicit Grid(int _width, int _height) //creates a vector of nodes
  {
    width = _width;
    height = _height;
    for(int x = 0; x < width; x++) //The vector is 1d
    {
      for(int y = 0; y < height; y ++)
      {
        Node *newNode = new Node();
        nodes.push_back(newNode);
      }
    }
  }
  ///returns a pointer to the node at the given coordinate
  Node* GetNodeAt(int x, int y)
  {
    int index = width * y + x; //converts 2d coordinates into a 1d index
    return nodes[index];
  }
  ///Returns all the neighbors of the node at Pos that are not yet visited
  vector<Vector2> GetUnvisitedNeighborsOf(int x, int y)
  {
    vector<Vector2> unvisitedNeighbors;
    //checks whether each potential neighbor is both A: a valid coordinate & B: unvisited
    if(y-1 >= 0 && !GetNodeAt(x, y-1)->visited) //up
    {
      unvisitedNeighbors.emplace_back(x,y-1);
    }
    if(x+1 < width && !GetNodeAt(x+1, y)->visited) //right
    {
      unvisitedNeighbors.emplace_back(x+1,y);
    }
    if(y+1 < height && !GetNodeAt(x, y+1)->visited) //down
    {
      unvisitedNeighbors.emplace_back(x,y+1);
    }
    if(x-1 >= 0 && !GetNodeAt(x-1, y)->visited) //left
    {
      unvisitedNeighbors.emplace_back(x-1,y);
    }

    return unvisitedNeighbors;
  }

  ///Prints out the contents of the grid
  void PrintGrid()
  {
    //prints the top border of the grid
    for(int x = 0; x < width; x++)
    {
      cout << ' ' << '_';
    }
    cout << ' ' << ' '  << endl;
    //prints the contents of the grid
    for(int y = 0; y < height; y++)
    {
      for(int x = 0; x < width; x++)
      {
        Node* currentNode = GetNodeAt(x,y);
        cout << currentNode->left << currentNode->bottom;
      }
      //prints the right border of the grid
      cout << '|' << ' ' << endl;
    }
  }
};

////////RANDOM
const int NUM_RANDOM_NUMBERS = 100; //how many random numbers in the random number list
int RAND_LIST[NUM_RANDOM_NUMBERS] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};
int randomIndex; //which random number we're currently using

int GetRandomNeighborIndex(int numNeighbors);

int main(){
  int columns;
  int rows;
  cin >> columns >> rows >> randomIndex;

  Grid grid = Grid(columns, rows);
  //Creates a vector to store the coordinates of each node, adds the top left node
  vector<Vector2> stack;
  stack.emplace_back(0,0);
  grid.GetNodeAt(0,0)->visited = true;

  //conducts the generative process until every node has been visited
  while(!stack.empty())
  {
    int currentX = stack.back().x;
    int currentY = stack.back().y;

    //Gets the unvisited neighbors
    vector<Vector2> unvisitedNeighbors = grid.GetUnvisitedNeighborsOf(currentX, currentY);

    //if the current node has no valid neighbours, revert to previous current node
    if(unvisitedNeighbors.empty())
    {
      stack.pop_back();
    }
    //if there's a valid neighbour, open the wall between them & move the head to that position
    else
    {
      int nextNodeIndex = 0;
      //if there's multiple neighbours, choose a 'random' one
      if(unvisitedNeighbors.size() > 1)
      {
        nextNodeIndex = GetRandomNeighborIndex((int)unvisitedNeighbors.size());
      }
      //breaks down the next node for human ease of reading
      int nextX = unvisitedNeighbors[nextNodeIndex].x;
      int nextY = unvisitedNeighbors[nextNodeIndex].y;
      //Breaks the relevant wall
      if(nextY < currentY) //up
      {
        grid.GetNodeAt(nextX,nextY)->bottom = ' ';
      }
      else if(nextX > currentX) //right
      {
        grid.GetNodeAt(nextX,nextY)->left = ' ';
      }
      else if(nextY > currentY) //down
      {
        grid.GetNodeAt(currentX,currentY)->bottom = ' ';
      }
      else if(nextX < currentX) //left
      {
        grid.GetNodeAt(currentX,currentY)->left = ' ';
      }

      //moves the head, marks the new head as visited
      stack.emplace_back(nextX,nextY);
      grid.GetNodeAt(nextX, nextY)->visited = true;
    }
  }


  //prints the output
  grid.PrintGrid();
}


int GetRandomNeighborIndex(int numNeighbors)
{
  int rand = RAND_LIST[randomIndex];
  rand %= numNeighbors;
  randomIndex++;
  if(randomIndex >= NUM_RANDOM_NUMBERS)
  {
    randomIndex = 0;
  }
  return rand;
}
