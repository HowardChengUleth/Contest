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

bool check_horiz(int r, int bad = 0)
{
  int bad_count = 0;
  for (int c = 0; c < N; c++) {
    for (int i = 0; i < M; i++) {
      if (!(r+i < M && r-1-i >= 0)) break;
      if (A[r+i][c] != A[r-1-i][c]) bad_count++;
    }
  }
  return bad == bad_count;
}

bool check_vert(int c, int bad = 0)
{
  int bad_count = 0;
  for (int r = 0; r < M; r++) {
    for (int i = 0; i < N; i++) {
      if (!(c+i < N && c-1-i >= 0)) break;
      if (A[r][c+i] != A[r][c-1-i]) bad_count++;
    }
  }
  return bad == bad_count;
}

int find_line()
{
  int ans2_r = -1, ans2_c = -1;
  for (int i = 1; i <= M-1; i++) {
    if (check_horiz(i, 1)) {
      ans2_r = i;
    }
  }
  for (int j = 1; j <= N-1; j++) {
    if (check_vert(j, 1)) {
      ans2_c = j;
    }
  }

  assert((ans2_c == -1 && ans2_r > 0) || (ans2_c > 0 && ans2_r == -1));
  if (ans2_r > 0) {
    return ans2_r * 100;
  } else {
    return ans2_c;
  }
}

int main()
{
  int ans = 0;
  while (read_grid()) {
    M = A.size();
    N = A[0].size();
    ans += find_line();
  }
  cout << ans << endl;

  return 0;
}
