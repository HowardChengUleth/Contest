#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int isprime(int n)
{
  if (n < 2) return false;
  if (n > 2 && n % 2 == 0) return false;
  for (int p = 3; p*p <= n; p += 2) {
    if (n % p == 0) return false;
  }
  return true;
}

int solve(int S, int T)
{
  queue<int> q;
  int dist[1001];
  fill(dist, dist+1001, -1);

  dist[S] = 0;
  q.push(S);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    if (curr == T) {
      break;
    }

    for (int p = 2; p < curr; p++) {
      if (!isprime(p)) continue;
      if (curr % p != 0) continue;
      int next = curr + p;
      if (next > T || dist[next] >= 0) continue;
      dist[next] = dist[curr] + 1;
      q.push(next);
    }
  }
    
  return dist[T];
}

int main()
{
  int S, T;
  int num = 1;

  while (cin >> S >> T && (S || T)) {
    cout << "Case " << num++ << ": " << solve(S, T) << endl;
  }

  return 0;
}
