#include <bits/stdc++.h>

using namespace std;


int N;
string A[50];
int best;
int line_count;
set<pair<int,int>> pos1;

void check(int r, int c, int dr, int dc)
{
  pair<int,int> empty;
  int Xcount = 0;
  for (int i = 0; i < N; i++) {
    char p = A[r][c];
    if (p == 'X') {
      Xcount++;
    } else if (p == 'O') {
      return;
    } else {
      empty = make_pair(r, c);
    }
    r += dr;
    c += dc;
  }

  int num = N - Xcount;
  if (num < best) {
    best = num;
    line_count = 1;
  } else if (num == best) {
    line_count++;
  }
  if (num == 1) {
    pos1.insert(empty);
  }
}

void solve()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  line_count = 0;
  pos1.clear();
  best = 500000;
  
  for (int r = 0; r < N; r++) {
    check(r, 0, 0, 1);
  }
  for (int c = 0; c < N; c++) {
    check(0, c, 1, 0);
  }

  if (best > N) {
    cout << "Impossible" << endl;
    return;
  }
  cout << best << ' ';
  if (best == 1) {
    cout << pos1.size() << endl;
  } else {
    cout << line_count << endl;
  }
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
