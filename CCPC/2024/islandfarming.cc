#include <bits/stdc++.h>
#include <cassert>

using namespace std;

int C, N, M, D;

int solve(int num_planted)
{
  int day = 0;

  int coconuts = C;
  int trees = 0;
  
  queue<int> mature;
  while (true) {
    // process mature trees
    if (!mature.empty() && mature.front() == day) {
      trees++;
      mature.pop();
    }

    // produce coconuts
    coconuts += trees;
    
    if (trees >= N && coconuts >= M) {
      break;
    }

    // only plant trees if we can, but don't plant more than needed
    if (coconuts > 0 && trees + mature.size() < num_planted) {
      coconuts--;
      mature.push(day + D);
    }
    day++;
  }

  return day;
}

int main()
{
  cin >> C >> N >> M >> D;

  int ans = INT_MAX;
  for (int i = N; i <= 100; i++) {
    ans = min(ans, solve(i));
  }
  cout << ans << endl;
  return 0;
}
