// This is kind of a reading comprehension problem.
//
// You start with a grid g, and repeatedly generate the next grid.  Note
// that there are only 2^9 = 512 possible grids so the sequence must
// repeat eventually in a cycle, but this sequence can also have a non-cyclic
// part before entering the cycle.
//
// k_g(h) is the number of times the grid "h" appears in the sequence.
// This number is finite if h is not part of the cycle, and infinite otherwise.
// So the question is asking: generate the sequence of grids from the given
// starting grid, and see when the cycle starts.  The answer is the index
// of the starting point - 1.
//

#include <iostream>
#include <algorithm>

using namespace std;

struct Grid {
  int g[5][5]; // 5x5 and put 0's on the border to avoid going out of bounds

  Grid() 
  {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
	g[i][j] = 0;
      }
    }
  }
  
  void next() 
  {
    int old[5][5];

    for (int i = 0; i < 5; i++) {
      copy(g[i], g[i]+5, old[i]);
    }

    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
	g[i][j] = (old[i-1][j] + old[i+1][j] + old[i][j-1] + old[i][j+1]) % 2;
      }
    }
  }

  // each grid has a signature (0-511) to help remember if it has been seen
  int sig() const 
  {
    int s = 0;
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
	s = s*2 + g[i][j];
      }
    }
    return s;
  }
};

istream &operator>>(istream &is, Grid &g)
{
  char c;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      is >> c;
      g.g[i][j] = c - '0';
    }
  }
  return is;
}

void do_case(void)
{
  Grid G;
  cin >> G;

  // when did I see a grid for the first time, -1 = not seen yet
  int first[512];
  fill(first, first+512, -1);
  
  int step = 0;
  first[G.sig()] = step++;
  G.next();
  while (first[G.sig()] == -1) {
    first[G.sig()] = step++;
    G.next();
  }
  cout << first[G.sig()]-1 << endl;
}

int main(void)
{
  int t;
  cin >> t;
  while (t-- > 0) {
    do_case();
  }
  return 0;
}
