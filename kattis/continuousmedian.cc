#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int N;
  cin >> N;

  priority_queue<int> bot, top;

  long long sum = 0;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;

    if (bot.empty() || x <= bot.top()) {
      bot.push(x);
    } else {
      top.push(-x);
    }

    if (bot.size() >= top.size() + 2) {
      top.push(-bot.top());
      bot.pop();
    } else if (top.size() > bot.size()) {
      bot.push(-top.top());
      top.pop();
    }

    if (bot.size() == top.size()) {
      sum += (bot.top() - top.top()) / 2;
    } else {
      sum += bot.top();
  }
  cout << sum << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
