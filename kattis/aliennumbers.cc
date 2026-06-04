#include <bits/stdc++.h>

using namespace std;

void solve()
{
  string num_str, src, target;

  cin >> num_str >> src >> target;

  int src_base = src.length();
  int target_base = target.length();
  
  int num = 0;
  for (auto ch : num_str) {
    num *= src_base;
    num += src.find(ch);
  }

  string ans;
  while (num > 0) {
    ans += target[num % target_base];
    num /= target_base;
  }
  reverse(begin(ans), end(ans));
  cout << ans << endl;
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
