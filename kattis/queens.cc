#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  vector<int> row(N, 0), col(N, 0), diag1(2*N-1, 0), diag2(2*N-1, 0);

  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    row[y]++;
    col[x]++;
    diag1[x+y]++;
    diag2[x-y+(N-1)]++;
  }

  bool bad = false;
  for (auto v : row) {
    bad |= v > 1;
  }
  for (auto v : col) {
    bad |= v > 1;
  }
  for (auto v : diag1) {
    bad |= v > 1;
  }
  for (auto v : diag2) {
    bad |= v > 1;
  }

  cout << (bad ? "INCORRECT" : "CORRECT") << endl;
  return 0;
}
