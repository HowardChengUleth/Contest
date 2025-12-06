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
  int N = lines[M-1].size();
  string::size_type col_s = 0;
  string::size_type col_e = lines[M-1].find_first_of("*+", col_s+1);

  int64_t ans = 0;
  while (col_s < string::size_type(N) && col_s != string::npos) {
    char op = lines[M-1][col_s];
    if (col_e == string::npos) {
      col_e = N;
    }

    vector<int64_t> args;
    for (string::size_type j = col_s; j < col_e; j++) {
      int64_t x = 0;
      for (int i = 0; i < M-1; i++) {
	if (isdigit(lines[i][j])) {
	  x = x*10 + lines[i][j] - '0';
	}
      }
      if (x) {
	args.push_back(x);
      }
    }

    int64_t res = (op == '*') ? 1 : 0;
    for (auto x : args) {
      if (op == '*') {
	res *= x;
      } else {
	res += x;
      }
    }

    ans += res;
    col_s = col_e;
    col_e = lines[M-1].find_first_of("*+", col_s+1);
  }

  cout << ans << endl;
  cout << "===" << endl;

  return 0;
}
