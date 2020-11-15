//
// Just simulate.  Not much else to do
//

#include <bits/stdc++.h>

using namespace std;

int main()
{
  char grid[50][50];
  int H, L, K;

  cin >> L >> H >> K;
  for (int r = 0; r < H; r++) {
    for (int c = 0; c < L; c++) {
      grid[r][c] = '_';
    }
  }

  for (int i = 0; i < K; i++) {
    char ch = 'a' + i;

    int l, h, a, b;
    cin >> l >> h >> a >> b;

    for (int r = b; r < min(b+h, H); r++) {
      for (int c = a; c < min(a+l, L); c++) {
	grid[r][c] = ch;
      }
    }
  }

  for (int r = 0; r < H; r++) {
    for (int c = 0; c < L; c++) {
      cout << grid[r][c];
    }
    cout << endl;
  }
  
  return 0;
}
