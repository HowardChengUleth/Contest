#include <bits/stdc++.h>

using namespace std;

// The idea is to fill one column at a time.  For each column, try all
// possible 2^h patterns.  Note that the first column can only affect
// up to the first 2 columns.
//
// So we can do DP where the state would be what column are we on and
// what are the first 2 columns (2^(2h) states)

int w, h, k;

int best[50][256][256];
int next_col[50][256][256];
int ones[256];

const int INF = 1000000;

// assuming the left column has pattern c1 and the middle column has c2
// and right column has c3, check if the middle column is okay
bool check_col(int c1, int c2, int c3)
{
  for (int i = 0; i < h; i++) {
    if (c2 & (1 << i)) continue;
    int mines = 0;
    if (i > 0) {
      mines += (c1 & (1 << (i-1))) ? 1 : 0;
      mines += (c2 & (1 << (i-1))) ? 1 : 0;
      mines += (c3 & (1 << (i-1))) ? 1 : 0;
    }
    mines += (c1 & (1 << i)) ? 1 : 0;
    mines += (c3 & (1 << i)) ? 1 : 0;
    if (i < h) {
      mines += (c1 & (1 << (i+1))) ? 1 : 0;
      mines += (c2 & (1 << (i+1))) ? 1 : 0;
      mines += (c3 & (1 << (i+1))) ? 1 : 0;
    }

    if (mines != k) {
      return false;
    }
  }
  return true;
}

int search(int c, int c1, int c2)
{
  assert(w - c >= 2);
  
  int &ans = best[c][c1][c2];
  if (ans >= 0) return ans;

  if (w - c == 2) {
    if (check_col(c1, c2, 0)) {
      return ans = ones[c1] + ones[c2];
    } else {
      return ans = INF;
    }
  }

  ans = INF;
  for (int c3 = 0; c3 < (1 << h); c3++) {
    if (!check_col(c1, c2, c3)) continue;
    int temp = search(c+1, c2, c3) + ones[c1];
    if (temp < ans) {
      ans = temp;
      next_col[c][c1][c2] = c3;
    }
  }
  return ans;
}

void fillA(char A[8][50], int c, int pat)
{
  for (int r = 0; r < h; r++) {
    A[r][c] = (pat & 1) ? '#' : '.';
    pat >>= 1;
  }
}

int main()
{
  for (int i = 0; i < 256; i++) {
    ones[i] = __builtin_popcount(i);
  }
  
  cin >> w >> h >> k;
  for (int c = 0; c < w; c++) {
    for (int c1 = 0; c1 < (1 << h); c1++) {
      for (int c2 = 0; c2 < (1 << h); c2++) {
	best[c][c1][c2] = -1;
      }
    }
  }
  
  int ans = w*h+1;
  int best_c1, best_c2;

  if (w == 1) {
    for (int c1 = 0; c1 < (1 << h); c1++) {
      if (check_col(0, c1, 0)) {
	if (ones[c1] < ans) {
	  ans = ones[c1];
	  best_c1 = c1;
	  best_c2 = 0;
	}
      }
    }
  } else {
    for (int c1 = 0; c1 < (1 << h); c1++) {
      for (int c2 = 0; c2 < (1 << h); c2++) {
	if (!check_col(0, c1, c2)) continue;
	int t = search(0, c1, c2);
	if (t < ans) {
	  ans = t;
	  best_c1 = c1;
	  best_c2 = c2;
	}
      }
    }
  }

  cout << ans << endl;
  char A[8][50];
  fillA(A, 0, best_c1);
  fillA(A, 1, best_c2);
  for (int i = 2; i < w; i++) {
    int c1 = best_c1;
    best_c1 = best_c2;
    best_c2 = next_col[i-2][c1][best_c2];
    fillA(A, i, best_c2);
  }
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cout << A[i][j];
    }
    cout << endl;
  }
  
  
  return 0;
}
