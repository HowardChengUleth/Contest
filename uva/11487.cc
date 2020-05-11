#include <algorithm>
#include <map>
#include <queue>
#include <cctype>
#include <iostream>

using namespace std;

struct State
{
  int r, c;
  char next;

  int toint() const
  {
    return (r*10+c)*26 + (next-'A');
  }

  bool operator<(const State &s) const
  {
    return toint() < s.toint();
  }
};

const int MOD = 20437;

const int dr[4] = { -1,  0, 1, 0 };
const int dc[4] = {  0, -1, 0, 1 };

bool solve(int id)
{
  int n;
  cin >> n;
  if (!n) return false;
  cout << "Case " << id << ": ";

  State start;
  char last = 'A';
  
  char grid[10][10];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
      if (grid[i][j] == 'A') {
	start.r = i;
	start.c = j;
	start.next = 'A';
      }
      if (isalpha(grid[i][j])) {
	last = max(last, grid[i][j]);
      }
    }
  }

  map<State, int> ways, dist;
  queue<State> q;

  dist[start] = 0;
  ways[start] = 1;
  q.push(start);

  while (!q.empty()) {
    State curr = q.front();
    q.pop();

    if (grid[curr.r][curr.c] == curr.next) {
      if (curr.next == last) {
	cout << dist[curr] << ' ' << ways[curr] << endl;
	return true;
      }

      State next = curr;
      next.next++;
      if (dist.find(next) == dist.end()) {
	dist[next] = dist[curr];
	ways[next] = ways[curr];
	q.push(next);
      } else {
	ways[next] = (ways[next] + ways[curr]) % MOD;
      }
      continue;
    }

    for (int d = 0; d < 4; d++) {
      State next = curr;
      next.r += dr[d];
      next.c += dc[d];

      if (!(0 <= next.r && next.r < n && 0 <= next.c && next.c < n)) continue;
      if (grid[next.r][next.c] == '#') continue;
      if (isalpha(grid[next.r][next.c]) && grid[next.r][next.c] > next.next)
	continue;

      if (dist.find(next) == dist.end()) {
	dist[next] = dist[curr] + 1;
	ways[next] = ways[curr];
	q.push(next);
      } else {
	ways[next] = (ways[next] + ways[curr]) % MOD;
      }
    }
  }
  
  cout << "Impossible" << endl;
  return true;
}

int main(void)
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
