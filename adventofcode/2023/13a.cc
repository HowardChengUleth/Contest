#include <bits/stdc++.h>

using namespace std;

vector<string> A;
int M, N;

bool read_grid()
{
  A.clear();
  string line;
  while (getline(cin, line) && line != "") {
    A.push_back(line);
  }
  return A.size() > 0;
}

bool check_horiz(int r)
{
  for (int c = 0; c < N; c++) {
    for (int i = 0; i < M; i++) {
      if (!(r+i < M && r-1-i >= 0)) break;
      if (A[r+i][c] != A[r-1-i][c]) return false;
    }
  }
  return true;
}

bool check_vert(int c)
{
  for (int r = 0; r < M; r++) {
    for (int i = 0; i < N; i++) {
      if (!(c+i < N && c-1-i >= 0)) break;
      if (A[r][c+i] != A[r][c-1-i]) return false;
    }
  }
  return true;
}

int main()
{
  int ans = 0;
  while (read_grid()) {
    M = A.size();
    N = A[0].size();

    for (int i = 1; i <= M-1; i++) {
      if (check_horiz(i)) {
	ans += 100*i;
      }
    }
    for (int j = 1; j <= N-1; j++) {
      if (check_vert(j)) {
	ans += j;
      }
    }
  }
  cout << ans << endl;

  return 0;
}
