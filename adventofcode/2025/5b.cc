#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<int64_t, int64_t> pii;

vector<pii> fresh;

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

  sort(begin(fresh), end(fresh));

  int64_t ans = 0;

  int64_t last = -100;

  for (auto [s, e] : fresh) {
    int64_t start = max(s, last+1);
    ans += max(e - start + 1, int64_t(0));
    last = max(last, e);
  }

  cout << ans << endl;
  return 0;
}
