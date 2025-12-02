#include <bits/stdc++.h>

using namespace std;

set<int64_t> find_invalid(int64_t start, int64_t end)
{
  set<int64_t> v;
  
  for (int i = 1; i <= 999999; i++) {
    ostringstream oss;
    oss << i;

    string s = oss.str() + oss.str();
    int64_t x = stoll(s);
    if (start <= x && x <= end) {
      v.insert(x);
    }
    if (x > end) {
      break;
    }

    do {
      s += oss.str();
      x = stoll(s);
      if (start <= x && x <= end) {
	v.insert(x);
      }
    } while (x <= end);
  }
  return v;
}

int main()
{
  string line;
  cin >> line;

  replace(begin(line), end(line), ',', ' ');
  replace(begin(line), end(line), '-', ' ');

  istringstream iss(line);
  int64_t start, end;

  int64_t ans = 0;
  while (iss >> start >> end) {
    auto ids = find_invalid(start, end);

    cout << start << ' ' << end << ": ";
    for (auto x : ids) {
      cout << x << ' ';
      ans += x;
    }
    cout << endl;
  }

  cout << ans << endl;

  return 0;
}
