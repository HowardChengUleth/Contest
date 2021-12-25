#include <bits/stdc++.h>

using namespace std;

vector<string> A;
int m, n;

typedef pair<int,int> pii;

bool move_ch(char ch, int dr, int dc)
{
  vector<pii> ready;
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {
      if (A[r][c] != ch) continue;
      int r2 = (r+dr) % m, c2 = (c+dc) % n;
      if (A[r2][c2] == '.') {
	ready.emplace_back(r, c);
      }
    }
  }

  if (ready.size() == 0) {
    return false;
  }

  for (auto [r, c] : ready) {
    int r2 = (r+dr) % m, c2 = (c+dc) % n;
    A[r][c] = '.';
    A[r2][c2] = ch;
  }
  return true;
}

bool do_step()
{
  bool b1 = move_ch('>', 0, 1);
  bool b2 = move_ch('v', 1, 0);
  
  return b1 || b2;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    A.push_back(line);
  }
  m = A.size();
  n = A[0].length();

  int step = 1;
  while (do_step()) {
    step++;
  }

  cout << step << endl;
  
  return 0;
}
