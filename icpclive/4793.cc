// Exhaustive search, with some pruning:
//
// - make sure we are at the checkpoints at exactly the prescribed times
// - if I am too far away from the next checkpoint, prune
// - keep track of the number of useable exits for each cell, and update
//   that for each cell as we visit the cells.  If a neighbour has no
//   useable exits, then prune.  If a neighbour has only one useable exit,
//   we must move there because if that neighbour is visited from the other
//   exit, we cannot get out from there.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int dr[4] = {-1, 1,  0, 0};
const int dc[4] = { 0, 0, -1, 1};


// we will actually store 5 checkpoints: (0,0) is checkpoint 0, (0,1) is
// checkpoint 4.  times[i] stores when we are supposed to be at checkpoint i
pair<int,int> checkpoint[5];
int times[5];

int result;
int m, n;

// deg[i][j] = number of nbrs of (i,j) that are not visited
int deg[8][8];
bool visited[8][8];

bool inbound(int r, int c)
{
  return (0 <= r && r < m && 0 <= c && c < n);
}

int paths(int r, int c, int step)
{
  // let's see if I should be at a checkpoint
  int cp = find(times, times+5, step) - times;
  if (cp != 5) {
    // I should be at a checkpoint
    if (checkpoint[cp] != make_pair(r, c)) {
      return 0;
    }
    if (cp == 4) {
      // I am done
      return 1;
    }
  } else {
    // I should not be at a checkpoint
    if (find(checkpoint, checkpoint+5, make_pair(r,c)) != checkpoint+5) {
      return 0;
    }

    // find the next checkpoint I am supposed to be at, and see if it is
    // too far away
    for (int i = 1; i <= 4; i++) {
      if (times[i] > step) {
	// next checkpoint found
	if (abs(r - checkpoint[i].first) + abs(c - checkpoint[i].second) >
	    times[i]) {
	  return 0;
	}
	break;
      }
    }
  }

  int total = 0;
  
  // mark myself as visited, and also decrease the degree of all my neighbours
  visited[r][c] = true;
  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    if (!inbound(nr, nc)) continue;
    deg[nr][nc]--;
  }

  // if any of my neighbours are unvisited and have degree 0, I can quit
  // because either I can't get there (if I don't move there next), or
  // I can't exit from there (if I move there next).  That's why (0,1) is
  // artificially connected to an imaginary exit
  //
  // Also, if someone has degree 1, then we must go in that direction.
  int deg1 = 0;
  int r1, c1;
  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    if (!inbound(nr, nc) || visited[nr][nc]) continue;
    if (deg[nr][nc] == 0) {
      goto getout;
    }
    if (deg[nr][nc] == 1) {
      r1 = nr;
      c1 = nc;
      if (++deg1 > 1) {
	// multiple degree 1 neighbours: no way to continue
	goto getout;
      }
    }
  }

  if (deg1 == 1) {
    // just go that way
    total += paths(r1, c1, step+1);
  } else {
    // try all the ways
    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];
      if (!inbound(nr, nc) || visited[nr][nc]) continue;
      total += paths(nr, nc, step+1);
    }
  }
  
  // clear myself as visited, and also increase the degree of all my neighbours
 getout:
  visited[r][c] = false;
  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    if (!inbound(nr, nc)) continue;
    deg[nr][nc]++;
  }

  return total;
}

bool do_case(int case_num)
{
  cin >> m >> n;
  if (!m && !n) {
    return false;
  }

  checkpoint[0] = make_pair(0,0);
  times[0] = 1;
  for(int i = 1; i <= 3; i++) {
    cin >> checkpoint[i].first >> checkpoint[i].second;
    times[i] = (i*m*n)/4;
  }
  checkpoint[4] = make_pair(0, 1);
  times[4] = m*n;

  for (int i = 0; i < m; i++) {
    fill(visited[i], visited[i]+n, false);
  }
  
  fill(deg[0]+1, deg[0]+n-1, 3);
  fill(deg[m-1]+1, deg[m-1]+n-1, 3);
  for (int r = 1; r < m-1; r++) {
    deg[r][0] = deg[r][n-1] = 3;
    fill(deg[r]+1, deg[r]+n-1, 4);
  }
  deg[0][0] = deg[0][n-1] = deg[m-1][0] = deg[m-1][n-1] = 2;

  // incrementing 1 to connect to an imaginary exit
  deg[0][1]++;

  cout << "Case " << case_num << ": " << paths(0, 0, 1) << endl;
  return true;
}



int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}

