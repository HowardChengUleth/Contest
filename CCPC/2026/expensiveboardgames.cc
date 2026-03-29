//
// There are n items, and there are n days to return them.
//
// Observation: you never want to return nothing on a day, so this becomes
// a problem of trying to assign each item to a return day.  i.e. this is
// an assignment/bipartite matching problem.
//
// For each item and each return day, we can figure out the penalty for
// that item.  We want the minimum total cost.
//
// Use the Hungarian algorithm to solve this in O(n^3) time.
//
// 

#include <bits/stdc++.h>
typedef int64_t ll;

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

using namespace std;

const int MAX_N = 500;

void update_labels(ll lx[MAX_N], ll ly[MAX_N], bool S[MAX_N], bool T[MAX_N], 
		   ll slack[MAX_N], int N)
{
  ll delta;
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

void add_to_tree(int x, int prevx, ll G[MAX_N][MAX_N], bool S[MAX_N], 
		 int prev[MAX_N], ll lx[MAX_N], ll ly[MAX_N], 
		 ll slack[MAX_N], ll slackx[MAX_N], int N)
{
  S[x] = true;
  prev[x] = prevx;
  for (int y = 0; y < N; y++) {
    ll temp = (G[x][y] == LLONG_MIN) ? LLONG_MAX : lx[x] + ly[y] - G[x][y];
    if (temp < slack[y]) {
      slack[y] = temp;
      slackx[y] = x;
    }
  }
}

ll max_weight_matching(ll G[MAX_N][MAX_N], int N, int matching[MAX_N])
{
  int revmatch[MAX_N];        // match from right to left
  int max_match = 0;          // number of vertices in current matching

  fill(matching, matching+N, -1);
  fill(revmatch, revmatch+N, -1);

  // find an initial feasible labelling
  ll lx[MAX_N], ly[MAX_N];
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

    ll slack[MAX_N], slackx[MAX_N];
    for (int y = 0; y < N; y++) {
      slack[y] = (G[root][y] == LLONG_MIN) ? LLONG_MAX : 
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
  ll weight = 0;
  for (int x = 0; x < N; x++) {
    weight += G[x][matching[x]];
  }
  return weight;
}

ll min_weight_matching(ll G[MAX_N][MAX_N], int N, int matching[MAX_N])
{
  ll M = LLONG_MIN;
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (G[i][j] != LLONG_MAX) {
	M = max(M, G[i][j]);
      }
    }
  }

  ll newG[MAX_N][MAX_N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      newG[i][j] = (G[i][j] == LLONG_MAX) ? LLONG_MIN : M - G[i][j];
    }
  }
  ll weight = max_weight_matching(newG, N, matching);
  return N*M - weight;
}

int main(void)
{
  ll G[MAX_N][MAX_N];
  int matching[MAX_N];

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    ll d, p;
    cin >> d >> p;

    d--;
    for (int j = 0; j < n; j++) {
      G[i][j] = p * max(ll(0), ll(j - d));
    }
  }

  ll w = min_weight_matching(G, n, matching);
  cout << w << endl;
  return 0;
}
