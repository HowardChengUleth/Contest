#include <iostream>
#include <queue>
#include <map>

using namespace std;

typedef pair<int,int> Loc;
typedef pair<Loc, int> State;

bool reachable(Loc loc, int steps, int dr, int dc, char maze[300][300],
	       int R, int C)
{
  for (int i = 0; i < steps; i++) {
    loc.first += dr;
    loc.second += dc;
    if (!(0 <= loc.first && loc.first < R && 
	  0 <= loc.second && loc.second < C &&
	  maze[loc.first][loc.second] != '#')) {
      return false;
    }
  }
  return true;
}

void do_case(void)
{
  int R, C;
  cin >> R >> C;
  
  char maze[300][300];
  Loc start, end(-1,-1);
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      cin >> maze[r][c];
      if (maze[r][c] == 'S') {
	start = make_pair(r, c);
      } else if (maze[r][c] == 'E') {
	end = make_pair(r, c);
      }
    }
  }

  queue<State> q;
  map<State,int> dist;
  
  State start_state(start, 1);
  q.push(start_state);
  dist[start_state] = 0;
  while (!q.empty()) {
    State curr = q.front();
    Loc curr_loc = curr.first;
    int curr_steps = curr.second;
    q.pop();

    if (curr_loc == end) {
      cout << dist[curr] << endl;
      return;
    }

    int next_steps = (curr_steps == 3) ? 1 : curr_steps + 1;
    int dr[4] = {0, 0, -1, 1};
    int dc[4] = {-1, 1, 0, 0};
    for (int i = 0; i < 4; i++) {
      Loc next_loc(curr_loc.first + curr_steps * dr[i], 
		   curr_loc.second + curr_steps * dc[i]);
      State next(next_loc, next_steps);
      if (dist.find(next) == dist.end() &&
	  reachable(curr_loc, curr_steps, dr[i], dc[i], maze, R, C)) {
	q.push(next);
	dist[next] = dist[curr] + 1;
      }
    }
  }
  cout << "NO" << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    do_case();
  }
  return 0;
}
