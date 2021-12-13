#include <bits/stdc++.h>

using namespace std;

const int N = 2000;
bool A[N][N];

int maxX, maxY;

void fold(char dir, int val)
{
  if (dir == 'x') {
    for (int y = 0; y <= maxY; y++) {
      A[val][y] = 0;
    }
    for (int x = val+1; x <= maxX; x++) {
      int x2 = 2*val - x;
      for (int y = 0; y <= maxY; y++) {
	A[x2][y] |= A[x][y];
	A[x][y] = 0;
      }
    }
    maxX = val-1;
  }

  if (dir == 'y') {
    for (int x = 0; x <= maxX; x++) {
      A[x][val] = 0;
    }
    for (int y = val+1; y <= maxY; y++) {
      int y2 = 2*val - y;
      for (int x = 0; x <= maxX; x++) {
	A[x][y2] |= A[x][y];
	A[x][y] = 0;
      }
    }
    maxY = val-1;
  }
}

int main()
{
  string s;
  while (getline(cin, s) && s != "") {
    istringstream iss(s);
    int x, y;
    char ch;
    
    iss >> x >> ch >> y;
    maxX = max(maxX, x);
    maxY = max(maxY, y);
    assert(0 <= x && x < N && 0 <= y && y < N);
    A[x][y] = true;
  }

  while (getline(cin, s)) {
    replace(begin(s), end(s), '=', ' ');
    istringstream iss(s);
    string word;
    char dir;
    int val;
    
    iss >> word >> word >> dir >> val;
    fold(dir, val);

  }

  for (int y = 0; y <= maxY; y++) {
    for (int x = 0; x <= maxX; x++) {
      cout << (A[x][y] ? '#' : '.');
    }
    cout << endl;
  }


  return 0;
}
