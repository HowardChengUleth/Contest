#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, H;
  cin >> N >> H;

  vector<int> bot, top;
  bot.reserve(N/2);
  top.reserve(N/2);
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    if (i % 2 == 0) {
      bot.push_back(x);
    } else {
      top.push_back(x);
    }
  }
  sort(begin(top), end(top));
  sort(begin(bot), end(bot));

  map<int, int> ans;
  for (int h = 1; h <= H; h++) {
    int cross = 0;
    cross += N/2 - (upper_bound(begin(bot), end(bot), h-1) - begin(bot));
    cross += N/2 - (upper_bound(begin(top), end(top), H-h) - begin(top));
    ans[cross]++;
  }
  auto [ x, y ] = *ans.begin();
  cout << x << ' ' << y << endl;
  return 0;
}
