#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cstdint>

using namespace std;

int main(){
  uint32_t value;
  uint32_t numToGen;
  int min;
  int max;

  //takes input
  cin >> value >> numToGen >> min >> max;

  for(int i = 0; i < numToGen; i++)
  {
    //shifts the number to 'randomize' it
    value ^= value << 13;
    value ^= value >> 17;
    value ^= value << 5;

    //clamps the number
    cout << min + (value % (max - min + 1)) << endl;
  }
}