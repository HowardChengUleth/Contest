#include <bits/stdc++.h>

using namespace std;

int w, h, n;
int height[1000] = {0};
int row[200000] = {0};

bool place(int p)
{
  if (height[p] >= h) {
    return false;
  } 

  int add_height = height[p];
  row[add_height]++;
  height[p]++;
  if (row[add_height] == w) {
    h++;
  }
  return true;
}

int main()
{
  cin >> w >> h >> n;

  queue<int> pos;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    pos.push(x);
  }

  int ans = 0;
  int failed = 0;
  while (!pos.empty()) {
    int p = pos.front();
    pos.pop();
    if (!place(p)) {
      pos.push(p);
      ans++;
      failed++;
    } else {
      failed = 0;
    }
    if (failed > pos.size()) {
      cout << -1 << endl;
      return 0;
    }
  }

  cout << ans << endl;
  
  return 0;
}
