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

typedef pair<int64_t,int64_t> pii;

vector<pii> red;

int main()
{
  string line;
  while (getline(cin, line)) {
    replace(begin(line), end(line), ',', ' ');
    istringstream iss(line);
    int r, c;
    iss >> r >> c;
    red.emplace_back(r, c);
  }

  int64_t ans = 0;
  N = red.size();
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      int64_t dr = abs(red[i].first - red[j].first) + 1;
      int64_t dc = abs(red[i].second - red[j].second) + 1;
      ans = max(ans, dr*dc);
    }
  }

  cout << ans << endl;
  return 0;
}
