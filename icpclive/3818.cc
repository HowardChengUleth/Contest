#include <iostream>
#include <queue>

using namespace std;

bool solve()
{
  int m, n;
  cin >> m >> n;
  if (!m && !n) return false;

  priority_queue<int> pq;

  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    pq.push(-x);
  }

  int ans = 0;
  while (pq.size() >= 2) {
    int x1 = -pq.top(); pq.pop();
    int x2 = -pq.top(); pq.pop();
    ans += x1 + x2;
    pq.push(-x1-x2);
  }

  cout << ans << endl;
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
