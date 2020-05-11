#include <bits/stdc++.h>

using namespace std;

int n, m;
map<string,int> nameI;

int G[110][110];
int cost[110], dist[110];

int main()
{
  cin >> n >> m;
  nameI["English"] = 0;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    nameI[s] = i;
  }

  n++;
  for (int i = 0; i < m; i++) {
    string l1, l2;
    int c;
    cin >> l1 >> l2 >> c;
    int i1 = nameI[l1], i2 = nameI[l2];
    G[i1][i2] = G[i2][i1] = c;
  }

  queue<int> q;
  fill(cost, cost+n, -1);
  fill(dist, dist+n, -1);

  q.push(0);
  cost[0] = dist[0] = 0;
  while (!q.empty()) {
    int curr = q.front();
    int d2 = dist[curr]+1;
    q.pop();

    for (int v = 0; v < n; v++) {
      if (!G[curr][v]) continue;
      if (dist[v] < 0) {
	dist[v] = d2;
	cost[v] = G[curr][v];
	q.push(v);
      } else if (dist[v] == d2) {
	cost[v] = min(cost[v], G[curr][v]);
      }
    }
  }

  int sum = 0;
  for (int i = 0; i < n; i++) {
    if (cost[i] < 0) {
      cout << "Impossible" << endl;
      return 0;
    }
    sum += cost[i];
  }

  cout << sum << endl;

  return 0;
}
