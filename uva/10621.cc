#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

class State : public pair<int, int>
{
  // first element: squared distance apart
  // second element: encoded positions

public:
  State(int jackx = 0, int jacky = 0, int jillx = 0, int jilly = 0) 
  {
    first = (jackx - jillx)*(jackx - jillx) + (jacky - jilly)*(jacky - jilly);
    second = (jackx << 15) | (jacky << 10) | (jillx << 5) | jilly;
  }
  
  void coords(int &jackx, int &jacky, int &jillx, int &jilly) const
  {
    jackx = second >> 15;
    jacky = (second >> 10) & 31;
    jillx = (second >> 5) & 31;
    jilly = second & 31;
  }

  int sq_dist(void) const
  {
    return first;
  }
};

bool visited[32][32][32][32];
pair<State, pair<char, char> > pred[32][32][32][32];

/* keep adding states that can be reached, but always explore the one
   that has the maximum distance (until destination is reached). */
void find_path(char grid[32][32], const State &src, const State &dest)
{
  int dx[5] = {0,0,0,1,-1};
  int dy[5] = {0,-1,1,0,0};
  string dirs = " NSEW";

  priority_queue<State> pq;
  int jackx, jacky, jillx, jilly;

  for (int i1 = 0; i1 < 32; i1++) {
    for (int i2 = 0; i2 < 32; i2++) {
      for (int i3 = 0; i3 < 32; i3++) {
	for (int i4 = 0; i4 < 32; i4++) {
	  visited[i1][i2][i3][i4] = false;
	}
      }
    }
  }

  src.coords(jackx, jacky, jillx, jilly);
  visited[jacky][jackx][jilly][jillx] = true;
  pq.push(src);
  double best_dist = src.sq_dist();

  while (!pq.empty()) {
    State curr = pq.top();
    pq.pop();

    if (curr.sq_dist() < best_dist) {
      best_dist = curr.sq_dist();
    }
    if (curr == dest) {
      break;
    }

    int jackx2, jacky2, jillx2, jilly2;
    curr.coords(jackx, jacky, jillx, jilly);

    for (int i = 0; i < 5; i++) {
      if (i == 0 && grid[jacky][jackx] != 'S' ||
	  i > 0 && grid[jacky][jackx] == 'S') continue;
      jackx2 = jackx + dx[i];
      jacky2 = jacky + dy[i];
      if (grid[jacky2][jackx2] == '*' ||
	  grid[jacky2][jackx2] == 'h' ||
	  grid[jacky2][jackx2] == 's') continue;
      for (int j = 0; j < 5; j++) {
	if (j == 0 && grid[jilly][jillx] != 's' ||
	    j > 0 && grid[jilly][jillx] == 's') continue;
	jillx2 = jillx + dx[j];
	jilly2 = jilly + dy[j];
	if (grid[jilly2][jillx2] == '*' ||
	    grid[jilly2][jillx2] == 'H' ||
	    grid[jilly2][jillx2] == 'S') continue;
	State next(jackx2, jacky2, jillx2, jilly2);
	if (!visited[jacky2][jackx2][jilly2][jillx2]) {
	  visited[jacky2][jackx2][jilly2][jillx2] = true;
	  pred[jacky2][jackx2][jilly2][jillx2] = 
	    make_pair(curr, make_pair(dirs[i], dirs[j]));
	  pq.push(next);
	}
      }
    }
  }

  cout << fixed << setprecision(2) << sqrt(best_dist) << endl;

  string jack_dir, jill_dir;
  State curr = dest;

  while (curr != src) {
    curr.coords(jackx, jacky, jillx, jilly);
    if (pred[jacky][jackx][jilly][jillx].second.first != ' ') {
      jack_dir += pred[jacky][jackx][jilly][jillx].second.first;
    }
    if (pred[jacky][jackx][jilly][jillx].second.second != ' ') {
      jill_dir += pred[jacky][jackx][jilly][jillx].second.second;
    }
    curr = pred[jacky][jackx][jilly][jillx].first;
  }
  
  for (int i = jack_dir.length()-1; i >= 0; i--) {
    cout << jack_dir[i];
  }
  cout << endl;

  for (int i = jill_dir.length()-1; i >= 0; i--) {
    cout << jill_dir[i];
  }
  cout << endl;

}

int main(void)
{
  int n;
  bool first = true;
  char grid[32][32];
  int Hx, Hy, hx, hy, Sx, Sy, sx, sy;

  while (cin >> n && n > 0) {
    if (!first) {
      cout << endl;
    }
    first = false;

    for (int i = 0; i <= n+1; i++) {
      fill(grid[i], grid[i]+n+2, '*');
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
	cin >> grid[i][j];
	switch (grid[i][j]) {
	  case 'H':
	    Hx = j; Hy = i;
	    break;
	  case 'S':
	    Sx = j; Sy = i;
	    break;
	  case 'h':
	    hx = j; hy = i;
	    break;
	  case 's':
	    sx = j; sy = i;
	    break;
	} 
      }
    }

    find_path(grid, State(Hx, Hy, hx, hy), State(Sx, Sy, sx, sy));
  }
  return 0;
}
