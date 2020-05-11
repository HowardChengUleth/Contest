#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
  int W;
  cin >> W;

  bool bad = false;
  int min_d = 1000, max_d = -1000;
  for (int i = 0; i < W; i++) {
    int y1, y2;
    cin >> y1 >> y2;
    bad |= y1 < y2;
    min_d = min(min_d, y1-y2);
    max_d = max(max_d, y1-y2);
  }

  bad |= min_d != max_d;

  cout << ((bad) ? "no" : "yes") << endl;

}

int main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    if (i) cout << endl;

    solve();
  }
  return 0;
}
