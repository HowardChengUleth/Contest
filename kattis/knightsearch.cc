#include <bits/stdc++.h>

using namespace std;


const string fav = "ICPCASIASG";
const int fav_len = 10;

string grid[100];
int N;

// found[r][c][k] = 1 if you can find fav[0..k] ending at (r,c)
//                = 0 if you can't
//                = -1 if uninitialized
int found[100][100][fav_len];

bool canend(int r, int c, int k)
{
  const int dr[] = { 1, 2, -1, -2,  1,  2, -1, -2 };
  const int dc[] = { 2, 1,  2,  1, -2, -1, -2, -1 };
  if (found[r][c][k] != -1) {
    return found[r][c][k];
  }
  if (k == 0) {
    return found[r][c][k] = (grid[r][c] == fav[k]);
  }
  if (grid[r][c] != fav[k]) {
    return found[r][c][k] = false;
  }

  for (int d = 0; d < 8; d++) {
    int r2 = r + dr[d], c2 = c + dc[d];
    if (0 <= r2 && r2 < N && 0 <= c2 && c2 < N && canend(r2, c2, k-1)) {
      return found[r][c][k] = true;
    }
  }
  
  return found[r][c][k] = false;
}

int main()
{
  cin >> N;
  for (int r = 0; r < N; r++) {
    grid[r] = string(N, ' ');
    for (int c = 0; c < N; c++) {
      cin >> grid[r][c];
      fill(found[r][c], found[r][c]+fav_len, -1);
    }
  }

  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      if (canend(r, c, fav_len-1)) {
	cout << "YES" << endl;
	return 0;
      }
    }
  }

  cout << "NO" << endl;
  return 0;
}
