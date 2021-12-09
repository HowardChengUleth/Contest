#include <bits/stdc++.h>

using namespace std;

vector<string> A;
int m, n;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

bool lowpoint(int i, int j)
{
  for (int d = 0; d < 4; d++) {
    int i2 = i + dr[d], j2 = j + dc[d];
    if (0 <= i2 && i2 < m && 0 <= j2 && j2 < n && A[i2][j2] <= A[i][j])
      return false;
  }
  return true;
}

int main()
{

  string s;
  while (cin >> s) {
    A.push_back(s);
  }

  m = A.size();
  n = A[0].size();
 
  int ans = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (lowpoint(i, j)) {
	ans += 1 + A[i][j] - '0';
      }
    }
  }
  cout << ans << endl;

  return 0;
}
