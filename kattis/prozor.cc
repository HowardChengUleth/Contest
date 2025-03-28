#include <bits/stdc++.h>

using namespace std;

char grid[100][100];
int csum[100][100];

int main()
{
  int R, S, K;
  cin >> R >> S >> K;

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < S; j++) {
      cin >> grid[i][j];
    }
  }

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < S; j++) {
      csum[i][j] = (grid[i][j] == '*');
      if (i > 0) {
	csum[i][j] += csum[i-1][j];
      }
      if (j > 0) {
	csum[i][j] += csum[i][j-1];
      }
      if (i > 0 && j > 0) {
	csum[i][j] -= csum[i-1][j-1];
      }
    }
  }

  int best_i, best_j, best_fly = 0;
  for (int i = 0; i+K-1 < R; i++) {
    for (int j = 0; j+K-1 < S; j++) {
      // square with upperleft = (i,j)
      int fly = csum[i+K-2][j+K-2];   // only the interior counts

      fly -= csum[i][j+K-2];
      fly -= csum[i+K-2][j];
      fly += csum[i][j];

      if (fly > best_fly) {
	best_i = i;
	best_j = j;
	best_fly = fly;
      }
    }
  }

  cout << best_fly << endl;

  for (int t = 1; t < K-1; t++) {
    grid[best_i][best_j+t] = '-';
    grid[best_i+K-1][best_j+t] = '-';
    grid[best_i+t][best_j] = '|';
    grid[best_i+t][best_j+K-1] = '|';
    grid[best_i][best_j] = '+';
    grid[best_i+K-1][best_j] = '+';
    grid[best_i][best_j+K-1] = '+';
    grid[best_i+K-1][best_j+K-1] = '+';
  }

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < S; j++) {
      cout << grid[i][j];
    }
    cout << endl;
  }

  return 0;
}
