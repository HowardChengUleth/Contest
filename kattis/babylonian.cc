#include <bits/stdc++.h>

using namespace std;

void solve()
{
  string s;
  cin >> s;

  // add 0's as needed...after last , and between ,,
  if (s.back() == ',') {
    s += '0';
  }
  for (auto pos = s.find(",,"); pos != string::npos; pos = s.find(",,")) {
    s.replace(pos, 2, ",0,");
  }

  // change , to space
  replace(begin(s), end(s), ',', ' ');

  // now take it apart
  istringstream iss(s);
  long long ans = 0;
  int x;
  while (iss >> x) {
    ans = 60*ans + x;
  }

  cout << ans << endl;

}

int main()
{
  int N;
  cin >> N;
  while (N--) {
    solve();
  }

  return 0;
}
