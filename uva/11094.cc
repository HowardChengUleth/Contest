#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string grid[20];
int id[20][20];
int M, N;
char land;

void flood(int r, int c, int label)
{
  id[r][c] = label;

  if (r > 0 && grid[r-1][c] == land && id[r-1][c] < 0) {
    flood(r-1, c, label);
  }

  if (r < M-1 && grid[r+1][c] == land && id[r+1][c] < 0) {
    flood(r+1, c, label);
  }

  int nc = (c + N-1) % N;
  if (grid[r][nc] == land && id[r][nc] < 0) {
    flood(r, nc, label);
  }

  nc = (c+1) % N;
  if (grid[r][nc] == land && id[r][nc] < 0) {
    flood(r, nc, label);
  }
}

int main(void)
{
  while (cin >> M >> N) {
    for (int i = 0; i < M; i++) {
      cin >> grid[i];
    }
    int x, y;
    cin >> x >> y;
    land = grid[x][y];
    
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
	id[i][j] = -1;
      }
    }

    int label = 0;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
	if (grid[i][j] == land && id[i][j] < 0) {
	  flood(i, j, label++);
	}
      }
    }

    int count[400] = {0};
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
	if (id[i][j] >= 0 && id[i][j] != id[x][y]) {
	  count[id[i][j]]++;
	}
      }
    }

    cout << *max_element(count, count+400) << endl;
    
  }
  return 0;
}
