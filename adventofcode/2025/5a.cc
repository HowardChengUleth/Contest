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

typedef pair<int64_t, int64_t> pii;

vector<pii> fresh;

bool is_fresh(int64_t id)
{
  for (auto [s, e] : fresh) {
    if (s <= id && id <= e) {
      return true;
    }
  }
  return false;
}

int main()
{
  string s;
  while (getline(cin, s) && s != "") {
    replace(begin(s), end(s), '-', ' ');
    istringstream iss(s);
    int64_t start, end;
    iss >> start >> end;
    fresh.emplace_back(start, end);
  }

  int ans = 0;
  int64_t id;
  
  while (cin >> id) {
    if (is_fresh(id)) {
      ans++;
    }
  }

  cout << ans << endl;
  return 0;
}
