#include <iostream>

using namespace std;

void solve()
{
  int X;
  cin >> X;
  X /= 100;

  int w[10][1001];
  for (int h = 9; h >= 0; h--) {
    for (int i = 0; i < X; i++) {
      cin >> w[h][i];
    }
  }

  int best[10][1001];
  for (int h = 9; h >= 0; h--) {
    best[h][0] = -1;
  }
  best[0][0] = 0;

  for (int i = 1; i <= X; i++) {
    for (int h = 0; h <= 9; h++) {
      int temp;
      best[h][i] = -1;

      // stay the same
      if (best[h][i-1] >= 0) {
	temp = best[h][i-1] + 30 - w[h][i-1];
	if (best[h][i] == -1 || temp < best[h][i]) {
	  best[h][i] = temp;
	}
      }

      // climb
      if (h > 0 && best[h-1][i-1] >= 0) {
	temp = best[h-1][i-1] + 60 - w[h-1][i-1];
	if (best[h][i] == -1 || temp < best[h][i]) {
	  best[h][i] = temp;
	}
      }
      
      // sink
      if (h < 9 && best[h+1][i-1] >= 0) {
	temp = best[h+1][i-1] + 20 - w[h+1][i-1];
	if (best[h][i] == -1 || temp < best[h][i]) {
	  best[h][i] = temp;
	}
      }
    }
  }

  cout << best[0][X] << endl << endl;
}

int main(void)
{
  int N;
  cin >> N;
  while (N--) {
    solve();
  }
  return 0;
}
