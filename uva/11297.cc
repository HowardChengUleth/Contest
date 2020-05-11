#include <iostream>
#include <utility>
#include <climits>
#include <cassert>

using namespace std;

int grid[500][500];

struct Node
{
  Node *ul, *ur, *ll, *lr;
  int left, right, upper, lower;
  int min, max;
  Node(int l = -1, int r = -1, int u = -1, int low = -1, int val = -1)
  {
    ul = ur = ll = lr = NULL;
    left = l;
    right = r;
    upper = u;
    lower = low;
    min = max = val;
  }
};

Node *createTree(int left, int right, int upper, int lower)
{
  if (left > right || upper > lower) {
    return NULL;
  }

  if (left == right && upper == lower) {
    return new Node(left, right, upper, lower, grid[upper][left]);
  }
  
  int midlr = (left + right) / 2;
  int midul = (upper + lower) / 2;

  Node *root = new Node(left, right, upper, lower);
  root->ul = createTree(left, midlr, upper, midul);
  root->ur = createTree(midlr+1, right, upper, midul);
  root->ll = createTree(left, midlr, midul+1, lower);
  root->lr = createTree(midlr+1, right, midul+1, lower);

  root->min = INT_MAX;
  root->max = INT_MIN;

  if (root->ul) {
    root->min = min(root->min, root->ul->min);
    root->max = max(root->max, root->ul->max);
  }
  if (root->ur) {
    root->min = min(root->min, root->ur->min);
    root->max = max(root->max, root->ur->max);
  }
  if (root->ll) {
    root->min = min(root->min, root->ll->min);
    root->max = max(root->max, root->ll->max);
  }
  if (root->lr) {
    root->min = min(root->min, root->lr->min);
    root->max = max(root->max, root->lr->max);
  }
  return root;
}

void printTree(Node *root)
{
  if (root == NULL) return;

  cout << "(" << root->upper << ", " << root->left << ") - ("
       << root->lower << ", " << root->right << "): "
       << root->max << ' ' << root->min << endl;
  printTree(root->ul);
  printTree(root->ur);
  printTree(root->ll);
  printTree(root->lr);

}

void deleteTree(Node *root)
{
  if (root == NULL) {
    return;
  }
  deleteTree(root->ul);
  deleteTree(root->ur);
  deleteTree(root->ll);
  deleteTree(root->lr);
  delete root;
}

void updateTree(Node *root, int row, int col, int val)
{
  if (root == NULL) {
    return;
  }
  if (root->left == root->right && root->upper == root->lower) {
    assert(row == root->upper && col == root->left);
    root->min = root->max = val;
    return;
  }

  int midlr = (root->left + root->right) / 2;
  int midul = (root->upper + root->lower) / 2;

  if (row <= midul && col <= midlr) {
    updateTree(root->ul, row, col, val);
  } else if (row <= midul && col > midlr) {
    updateTree(root->ur, row, col, val);
  } else if (row > midul && col <= midlr) {
    updateTree(root->ll, row, col, val);
  } else {
    updateTree(root->lr, row, col, val);
  }
  root->min = INT_MAX;
  root->max = INT_MIN;

  if (root->ul) {
    root->min = min(root->min, root->ul->min);
    root->max = max(root->max, root->ul->max);
  }
  if (root->ur) {
    root->min = min(root->min, root->ur->min);
    root->max = max(root->max, root->ur->max);
  }
  if (root->ll) {
    root->min = min(root->min, root->ll->min);
    root->max = max(root->max, root->ll->max);
  }
  if (root->lr) {
    root->min = min(root->min, root->lr->min);
    root->max = max(root->max, root->lr->max);
  }
}

void queryTree(Node *root, int left, int right, int upper, int lower,
	       int &big, int &small)
{
  big = INT_MIN;
  small = INT_MAX;

  if (root == NULL) {
    return;
  }

  if (left <= root->left && root->right <= right &&
      upper <= root->upper && root->lower <= lower) {
    big = root->max;
    small = root->min;
    return;
  }

  int midlr = (root->left + root->right) / 2;
  int midul = (root->upper + root->lower) / 2;

  int loc_big, loc_small;
  if (left <= midlr && upper <= midul) {
    queryTree(root->ul, left, right, upper, lower, loc_big, loc_small);
    big = max(big, loc_big);
    small = min(small, loc_small);
  }
  if (right > midlr && upper <= midul) {
    queryTree(root->ur, left, right, upper, lower, loc_big, loc_small);
    big = max(big, loc_big);
    small = min(small, loc_small);
  }
  if (left <= midlr && lower > midul) {
    queryTree(root->ll, left, right, upper, lower, loc_big, loc_small);
    big = max(big, loc_big);
    small = min(small, loc_small);
  }
  if (right > midlr && lower > midul) {
    queryTree(root->lr,  left, right, upper, lower, loc_big, loc_small);
    big = max(big, loc_big);
    small = min(small, loc_small);
  }
}

int main(void)
{
  int N, M;
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> grid[i][j];
    }
  }

  Node *tree = createTree(0, M-1, 0, N-1);
  int Q;
  cin >> Q;
  while (Q--) {
    char c;
    cin >> c;
    if (c == 'c') {
      int r, c, v;
      cin >> r >> c >> v;
      r--;  c--;
      updateTree(tree, r, c, v);
    } else {
      int big, small;
      int r1, c1, r2, c2;
      cin >> r1 >> c1 >> r2 >> c2;
      r1--; c1--; r2--; c2--;
      queryTree(tree, c1, c2, r1, r2, big, small);
      cout << big << ' ' << small << endl;
    }
  }

  deleteTree(tree);
  
  return 0;
}
