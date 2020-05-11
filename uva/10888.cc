#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <cassert>
#include <climits>

using namespace std;

const int MAX_N = 15;

void update_labels(int lx[MAX_N], int ly[MAX_N], bool S[MAX_N], bool T[MAX_N], 
		   int slack[MAX_N], int N)
{
  int delta;
  bool delta_init = false;

  for (int y = 0; y < N; y++) {
    if (T[y]) continue;
    delta = delta_init ? min(delta, slack[y]) : slack[y];
    delta_init = true;
  }
  for (int x = 0; x < N; x++) {
    if (S[x]) lx[x] -= delta;
  }
  for (int y = 0; y < N; y++) {
    if (T[y]) {
      ly[y] += delta;
    } else {
      slack[y] -= delta;
    }
  }
}

void add_to_tree(int x, int prevx, int G[MAX_N][MAX_N], bool S[MAX_N], 
		 int prev[MAX_N], int lx[MAX_N], int ly[MAX_N], 
		 int slack[MAX_N], int slackx[MAX_N], int N)
{
  S[x] = true;
  prev[x] = prevx;
  for (int y = 0; y < N; y++) {
    int temp = (G[x][y] == INT_MIN) ? INT_MAX : lx[x] + ly[y] - G[x][y];
    if (temp < slack[y]) {
      slack[y] = temp;
      slackx[y] = x;
    }
  }
}

int max_weight_matching(int G[MAX_N][MAX_N], int N, int matching[MAX_N])
{
  int revmatch[MAX_N];        // match from right to left
  int max_match = 0;          // number of vertices in current matching

  fill(matching, matching+N, -1);
  fill(revmatch, revmatch+N, -1);

  // find an initial feasible labelling
  int lx[MAX_N], ly[MAX_N];
  fill(ly, ly+N, 0);
  for (int x = 0; x < N; x++) {
    lx[x] = *max_element(G[x], G[x]+N);
  }

  // now repeatedly find alternating tree, augment, and relabel
  while (max_match < N) {
    queue<int> q;
    bool S[MAX_N], T[MAX_N];
    int prev[MAX_N];
    fill(S, S+N, false);
    fill(T, T+N, false);
    fill(prev, prev+N, -1);

    // find root of alternating tree
    int root = find(matching, matching+N, -1) - matching;
    q.push(root);
    prev[root] = -2;
    S[root] = true;

    int slack[MAX_N], slackx[MAX_N];
    for (int y = 0; y < N; y++) {
      slack[y] = (G[root][y] == INT_MIN) ? INT_MAX : 
	lx[root] + ly[y] - G[root][y];
      slackx[y] = root;
    }

    bool path_found = false; 
    int x, y;
    while (!path_found) {

      // build alternating tree with BFS
      while (!path_found && !q.empty()) {
	x = q.front();
	q.pop();
	for (y = 0; y < N; y++) {
	  // go through edges in equality graph
	  if (G[x][y] == lx[x] + ly[y] && !T[y]) {
	    if (revmatch[y] == -1) {
	      path_found = true;
	      break;
	    }
	    T[y] = true;
	    q.push(revmatch[y]);
	    add_to_tree(revmatch[y], x, G, S, prev, lx, ly, slack, slackx, N);
	  }
	}
      }
      if (path_found) break;

      // no augmenting path, update the labels
      update_labels(lx, ly, S, T, slack, N);
      while (!q.empty()) {
	q.pop();
      }
      for (y = 0; y < N; y++) {
	if (!T[y] && slack[y] == 0) {
	  if (revmatch[y] == -1) {
	    x = slackx[y];
	    path_found = true;
	    break;
	  } else {
	    T[y] = true;
	    if (!S[revmatch[y]]) {
	      q.push(revmatch[y]);
	      add_to_tree(revmatch[y], slackx[y], G, S, prev, lx, ly, slack,
			  slackx, N);
	    }
	  }
	}
      }
    }

    assert(path_found);
    max_match++;
    
    // augment along the path
    for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
      ty = matching[cx];
      revmatch[cy] = cx;
      matching[cx] = cy;
    }
  }

  // return the final answer
  int weight = 0;
  for (int x = 0; x < N; x++) {
    weight += G[x][matching[x]];
  }
  return weight;
}

int min_weight_matching(int G[MAX_N][MAX_N], int N, int matching[MAX_N])
{
  int M = INT_MIN;
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (G[i][j] != INT_MAX) {
	M = max(M, G[i][j]);
      }
    }
  }

  int newG[MAX_N][MAX_N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      newG[i][j] = (G[i][j] == INT_MAX) ? INT_MIN : M - G[i][j];
    }
  }
  int weight = max_weight_matching(newG, N, matching);
  return N*M - weight;
}

void bfs(int r, int c, char layout[40][40], int h, int w, 
	 int boxindex[], int locindex[], int G[MAX_N][MAX_N])
{
  queue< pair<int,int> > q;
  map< pair<int,int>, int > dist;

  pair<int,int> loc(r, c);

  q.push(loc);
  dist[loc] = 0;
  while (!q.empty()) {
    loc = q.front();
    int rr = loc.first, cc = loc.second;
    q.pop();

    if (layout[loc.first][loc.second] == 'X') {
      G[boxindex[r*w+c]][locindex[loc.first*w+loc.second]] = dist[loc];
    }

    pair<int,int> newloc = make_pair(rr-1, cc);
    if (rr > 0 && layout[rr-1][cc] != '#' && 
	dist.find(newloc) == dist.end()) {
      q.push(newloc);
      dist[newloc] = dist[loc] + 1;
    }
    newloc = make_pair(rr+1, cc);
    if (rr < h-1 && layout[rr+1][cc] != '#' && 
	dist.find(newloc) == dist.end()) {
      q.push(newloc);
      dist[newloc] = dist[loc] + 1;
    }
    newloc = make_pair(rr, cc-1);
    if (cc > 0 && layout[rr][cc-1] != '#' && 
	dist.find(newloc) == dist.end()) {
      q.push(newloc);
      dist[newloc] = dist[loc] + 1;
    }
    newloc = make_pair(rr, cc+1);
    if (cc < w-1 && layout[rr][cc+1] != '#' && 
	dist.find(newloc) == dist.end()) {
      q.push(newloc);
      dist[newloc] = dist[loc] + 1;
    }
  }
}

void do_case(void)
{
  int h, w;
  cin >> h >> w;

  char layout[40][40];
  int boxindex[40*40+2], locindex[40*40+2];
  fill(boxindex, boxindex+40*40+2, -1);
  fill(locindex, locindex+40*40+2, -1);
  int num_box = 0, num_loc = 0;
  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
      cin >> layout[r][c];
      
      if (layout[r][c] == 'B') {
	boxindex[r*w+c] = num_box++;
      } else if (layout[r][c] == 'X') {
	locindex[r*w+c] = num_loc++;
      }
    }
  }

  int G[MAX_N][MAX_N];
  for (int i = 0; i < MAX_N; i++) {
    fill(G[i], G[i]+MAX_N, INT_MAX);
  }

  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
      if (layout[r][c] != 'B') continue;
      bfs(r, c, layout, h, w, boxindex, locindex, G);
    }
  }

  int matching[MAX_N];
  cout << min_weight_matching(G, num_box, matching) << endl;
}

int main(void)
{
  int cases;
  cin >> cases;
  while (cases-- > 0) {
    do_case();
  }
  return 0;
}

