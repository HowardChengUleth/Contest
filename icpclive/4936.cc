// just do it

#include <tr1/array>
#include <iostream>

using namespace std;
using namespace std::tr1;

int main(void)
{
  int R, C;
  while (cin >> R >> C) {
    array< array<int, 30>, 30 > grid;

    int label = 1;
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
	char ch;
	cin >> ch;
	if (ch == 'X') {
	  grid[i][j] = -1;
	} else {
	  grid[i][j] = label++;
	}
      }
    }

    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
	if (grid[i][j] < 0) continue;
	int t, r, b, l;
	t = (i > 0 && grid[i-1][j] > 0) ? grid[i-1][j] : 0;
	r = (j < C-1 && grid[i][j+1] > 0) ? grid[i][j+1] : 0;
	b = (i < R-1 && grid[i+1][j] > 0) ? grid[i+1][j] : 0;
	l = (j > 0 && grid[i][j-1] > 0) ? grid[i][j-1] : 0;
	cout << grid[i][j] << ' '
	     << t << ' ' << r << ' ' << b << ' ' << l << endl;
      }
    }

    cout << endl;

  }
   

  return 0;
}
