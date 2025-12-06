#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int M, N;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

int main()
{
  vector<string> lines;
  string s;
  while (getline(cin, s)) {
    lines.push_back(s);
  }

  int M = lines.size();

  vector<vector<int64_t>> args;

  for (int i = 0; i < M-1; i++) {
    istringstream iss(lines[i]);
    vector<int64_t> v;

    int64_t x;
    while (iss >> x) {
      v.push_back(x);
    }

    args.push_back(v);
  }

  vector<char> ops;
  istringstream iss(lines[M-1]);
  char op;
  while (iss >> op) {
    ops.push_back(op);
  }
  
  int N = args[0].size();

  cout << "N = " << N << endl;
  cout << "ops.size() = " << ops.size() << endl;
  assert(ops.size() == N);
  
  int64_t ans = 0;

  for (int j = 0; j < N; j++) {
    int64_t res = (ops[j] == '*') ? 1 : 0;
    for (int i = 0; i < M-1; i++) {
      if (ops[j] == '*') {
	res *= args[i][j];
      } else {
	res += args[i][j];
      }
    }
    cout << "res[" << j << "] = " << res << endl;
    ans += res;
  }
  
  cout << ans << endl;
  return 0;
}
