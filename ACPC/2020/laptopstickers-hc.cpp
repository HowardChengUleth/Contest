//
// Comments:
//
// Inputs/Outputs: section numbers should be removed
// 
// Inputs: for the bounds on a and b, do you mean L and H instead of l and h?
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

    /*
    assert(0 <= a && a < l);
    assert(0 <= b && b < h);
    */
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
