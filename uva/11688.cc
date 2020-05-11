// Instead of actually building the tree and moving pointers, it is sufficient
// to remember the heights at each node in the original tree and process.
//
// For each node to be rotated to the root, we can solve the problem
// by propagating the values upwards.  But each calculation takes linear
// time and this leads to O(n^2) which is too slow.
//
// Instead, it is possible to do it from top down while remembering how
// many left and right rotations need to be done for each node to become
// root, and work out the remaining details.  This can be done in one
// pass with DFS from the root.  See below.

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 100001;

int N;
int lc[MAX_N], rc[MAX_N];
int height[MAX_N];         // height[0] = rotheight[0] = 0
int rotheight[MAX_N];

void calc_height(int root)
{
  if (!root) {
    height[root] = 0;
  } else {
    calc_height(lc[root]);
    calc_height(rc[root]);
    height[root] = 1 + max(height[lc[root]], height[rc[root]]);
  }
}

// lh = max height of the left branch if we do left rotation at node's
//      ancestors
// rh = max height of the right branch if we do right rotation at node's
//      ancestors
// lrot = number of left rotations from the real root to get to node in tree
//        traversal (i.e. number of left rotations to push root up to the
//        real root of the tree)
// rrot = number of right rotations from the real root to get to node

void rotate(int node, int lh = 0, int rh = 0, int lrot = 0, int rrot = 0)
{
  // when we rotate node to root, we will be the new root
  //
  // so the answer is either 1 + lh or 1 + rh
  // but also 1+lrot+height[lc[node]] and similarly for the right branch,
  // because each left rotation increases the height of the left branch
  // by 1 but leaves the right branch untouched, and similarly for right
  // rotations.
  rotheight[node] = max(max(1+lh, 1+rh), 
			max(1+lrot+height[lc[node]], 
			    1+rrot+height[rc[node]]));

  // right rotation
  //
  // left branch: no effect
  // right branch: whatever I have there, it will be 1 higher
  if (lc[node]) {
    rotate(lc[node], lh, max(rh, 1+rrot+height[rc[node]]),
	   lrot, 1+rrot);
  }

  // left rotation, similar
  if (rc[node]) {
    rotate(rc[node], max(lh, 1+lrot+height[lc[node]]), rh,
	   1+lrot, rrot);
  }
}

bool do_case()
{
  cin >> N;
  if (!N) return false;

  bool hasparent[MAX_N] = {false};
  for (int i = 1; i <= N; i++) {
    cin >> lc[i] >> rc[i];
    hasparent[lc[i]] = hasparent[rc[i]] = true;
  }
  int root = find(hasparent+1, hasparent+N+1, false) - hasparent;

  calc_height(root);
  rotate(root);

  for (int i = 1; i <= N; i++) {
    cout << rotheight[i] << endl;
  }

  return true;
}

int main()
{
  while (do_case())
    ;
  return 0;
}
