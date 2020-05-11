/*
 * Maximum/minimum weight bipartite matching
 *
 * Author: Howard Cheng
 * Reference:
 *  http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=hungarianAlgorithm
 *
 * This file contains routines for computing the maximum/minimum weight
 * bipartite matching.
 *
 * It is assumed that each half of the graph has exactly N vertices, labelled
 * 0 to N-1.  The weight between vertex i on the left and vertex j on the
 * right is stored in G[i][j].  The cost of the optimal matching is returned,
 * and matching[i] is the vertex on the right that is matched to vertex i
 * on the left.
 *
 * If an edge is absent, the corresponding edge weight should be:
 *
 *   INT_MIN   if maximum weight matching is desired
 *   INT_MAX   if minimum weight matching is desired
 *
 * This is an implementation of the Hungarian algorithm.  The complexity
 * is O(N^3).
 *
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <cassert>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

const int MAX_N = 20;

void update_labels(double lx[MAX_N], double ly[MAX_N],
		   bool S[MAX_N], bool T[MAX_N], 
		   double slack[MAX_N], int N)
{
  double delta;
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

void add_to_tree(int x, int prevx, double G[MAX_N][MAX_N], bool S[MAX_N], 
		 int prev[MAX_N], double lx[MAX_N], double ly[MAX_N], 
		 double slack[MAX_N], int slackx[MAX_N], int N)
{
  S[x] = true;
  prev[x] = prevx;
  for (int y = 0; y < N; y++) {
    double temp = (G[x][y] == DBL_MIN) ? DBL_MAX : lx[x] + ly[y] - G[x][y];
    if (temp < slack[y]) {
      slack[y] = temp;
      slackx[y] = x;
    }
  }
}

const double EPS = 1e-6;

double max_weight_matching(double G[MAX_N][MAX_N], int N, int matching[MAX_N])
{
  int revmatch[MAX_N];        // match from right to left
  int max_match = 0;          // number of vertices in current matching

  fill(matching, matching+N, -1);
  fill(revmatch, revmatch+N, -1);

  // find an initial feasible labelling
  double lx[MAX_N], ly[MAX_N];
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

    double slack[MAX_N];
    int slackx[MAX_N];
    for (int y = 0; y < N; y++) {
      slack[y] = (G[root][y] == DBL_MIN) ? DBL_MAX : 
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
	  if (fabs(G[x][y] - (lx[x] + ly[y])) < EPS && !T[y]) {
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
	if (!T[y] && fabs(slack[y]) < EPS) {
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
  double weight = 0;
  for (int x = 0; x < N; x++) {
    weight += G[x][matching[x]];
  }
  return weight;
}

double min_weight_matching(double G[MAX_N][MAX_N], int N, int matching[MAX_N])
{
  double M = DBL_MIN;
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (G[i][j] != DBL_MAX) {
	M = max(M, G[i][j]);
      }
    }
  }

  double newG[MAX_N][MAX_N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      newG[i][j] = (G[i][j] == DBL_MAX) ? DBL_MIN : M - G[i][j];
    }
  }
  /*
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << fixed << setprecision(3) << setw(12) << newG[i][j];
    }
    cout << endl;
    }
  */
  double weight = max_weight_matching(newG, N, matching);

  /*
  cout << "weight = " << weight << endl;
  for (int i = 0; i < N; i++) {
    cout << matching[i] << ' ';
  }
  cout << endl;
  */
  return N*M - weight;
}

int main(void)
{
  double G[20][20];
  int matching[20];

  int m, n;
  while (cin >> n >> m && (m || n)) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
	cin >> G[i][j];
      }
    }
    for (int i = n; i < m; i++) {
      fill(G[i], G[i]+m, 0);
    }

    double w = min_weight_matching(G, m, matching) / n + EPS;
    cout << fixed << setprecision(2) << w << endl;
  }

  return 0;
}
