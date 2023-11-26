#include <bits/stdc++.h>

using namespace std;

int r, c;

char grid[252][252];

bool inside(int i, int j)
{
  return grid[i][j] == '*' || grid[i][j] == ' ';
}

int DFS(int i, int j)
{
  const int dr[] = {-1, 1, 0, 0};
  const int dc[] = {0, 0, -1, 1};

  int spines = grid[i][j] == '*';
  grid[i][j] = '.';
  for (int d = 0; d < 4; d++) {
    int i2 = i + dr[d], j2 = j + dc[d];
    if (inside(i2, j2)) {
      spines += DFS(i2, j2);
    }
  }
  return spines;
}

int main()
{
  cin >> r >> c;
  for (int i = 0; i < 252; i++) {
    fill(grid[i], grid[i]+252, '.');
  }

  char ch;
  cin.get(ch);
  
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      cin.get(grid[i][j]);
    }
    cin.get(ch);
  }

  int cactus = 0;
  int spines = 0;
  for (int i = 0; i <= r+1; i++) {
    for (int j = 0; j <= c+1; j++) {
      if (inside(i, j)) {
	cactus++;
	spines = max(spines, DFS(i, j));
      }
    }
  }

  cout << cactus << ' ' << spines << endl;
  return 0;
}
