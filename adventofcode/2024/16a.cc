#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<string> vs;

int M, N;
vs grid;
void read_grid()
{
  string s;
  while (getline(cin, s)) {
    grid.push_back(s);
  }
  M = grid.size();
  N = grid[0].size();
}

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };


ll dijkstra(int r, int c, int dir)
{
  typedef tuple<int,int,int> ti3;

  map<ti3, int> dist;
  priority_queue<pair<int, ti3>, vector<pair<int, ti3>>,
		 greater<pair<int, ti3>>> pq;

  dist[ti3(r, c, dir)] = 0;
  pq.emplace(0, ti3(r, c, dir));

  while (!pq.empty()) {
    auto [curr_d, curr_tuple] = pq.top();
    pq.pop();
    auto [curr_r, curr_c, curr_dir] = curr_tuple;

    if (grid[curr_r][curr_c] == 'E') {
      return curr_d;
    }
    if (dist[curr_tuple] < curr_d) {
      continue;
    }

    // try moving forward
    int next_r = curr_r + dr[curr_dir];
    int next_c = curr_c + dc[curr_dir];
    if (inside(next_r, next_c) && grid[next_r][next_c] != '#') {
      ti3 next(next_r, next_c, curr_dir);
      int next_d = curr_d + 1;
      if (dist.find(next) == dist.end() || next_d < dist[next]) {
	dist[next] = next_d;
	pq.emplace(next_d, next);
      }
    }
    
    // try turning
    ti3 next(curr_r, curr_c, (curr_dir+1) % 4);
    int next_d = curr_d + 1000;
    if (dist.find(next) == dist.end() || next_d < dist[next]) {
      dist[next] = next_d;
      pq.emplace(next_d, next);
    }

    get<2>(next) = (curr_dir+3) % 4;
    if (dist.find(next) == dist.end() || next_d < dist[next]) {
      dist[next] = next_d;
      pq.emplace(next_d, next);
    }


  }

  assert(false);
  return -1;
}

int main()
{
  read_grid();

  int start_r, start_c;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] == 'S') {
	start_r = r;
	start_c = c;
      }
    }
  }

  ll ans = dijkstra(start_r, start_c, 1);
  cout << ans << endl;
  
  return 0;
}
