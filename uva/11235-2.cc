#include <iostream>
#include <utility>
#include <cassert>

using namespace std;

struct Node
{
  Node *left, *right;

  int start, end;
  pair<int,int> front, back, overall;

  Node()
  {
    left = right = NULL;
    start = end = -1;
    front = back = overall = make_pair(0, 0);
  }

  Node(int val, int index)
  {
    left = right = NULL;
    start = end = index;
    front = back = overall = make_pair(1, val);
  }

  Node(int ss, int ee, Node *ll, Node *rr)
  {
    start = ss;
    end = ee;
    left = ll;
    right = rr;
    if (left->front.second == right->front.second) {
      front = make_pair(left->front.first + right->front.first,
			left->front.second);
			
    } else {
      front = left->front;
    }
    if (right->back.second == left->back.second) {
      back = make_pair(right->back.first + left->back.first,
		       right->back.second);
    } else {
      back = right->back;
    }
    overall = max(ll->overall, rr->overall);
    if (left->back.second == right->front.second) {
      overall = max(overall, make_pair(left->back.first + right->front.first,
				       left->back.second));
    }
  }
};

Node *create_tree(int a[], int start, int end)
{
  if (start > end) {
    assert(false);
    return NULL;
  } else if (start == end) {
    return new Node(a[start], start);
  }
  int mid = (start + end)/2;
  Node *ll = create_tree(a, start, mid);
  Node *rr = create_tree(a, mid+1, end);
  return new Node(start, end, ll, rr);
}

void search_tree(Node *tree, int start, int end, Node &result)
{
  if (tree == NULL) {
    result = Node();
    return;
  }

  if (tree->start == start && tree->end == end) {
    result = *tree;
    return;
  }

  if (tree->left && tree->left->start <= start && end <= tree->left->end) {
    search_tree(tree->left, start, end, result);
    return;
  }
  if (tree->right && tree->right->start <= start && end <= tree->right->end) {
    search_tree(tree->right, start, end, result);
    return;
  }
  assert(tree->left && start <= tree->left->end &&
	 tree->right && end >= tree->right->start);

  Node left_result, right_result;
  search_tree(tree->left, start, tree->left->end, left_result);
  search_tree(tree->right, tree->right->start, end, right_result);

  result.front = left_result.front;
  if (left_result.front.second == right_result.front.second) {
    result.front.first = left_result.front.first + right_result.front.first;
  }
  result.back = right_result.back;
  if (right_result.back.second == left_result.back.second) {
    result.back.first = left_result.back.first + right_result.back.first;
  }
  
  result.overall = max(left_result.overall, right_result.overall);
  if (left_result.back.second == right_result.front.second) {
    result.overall = max(result.overall,
			 make_pair(left_result.back.first + 
				   right_result.front.first,
				   left_result.back.second));
  }

}

void delete_tree(Node *root)
{
  if (root == NULL) return;
  delete_tree(root->left);
  delete_tree(root->right);
  delete root;
}

bool do_case()
{
  int n, q;
  cin >> n >> q;
  if (n == 0) return false;
  
  int a[100000];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  Node *tree = create_tree(a, 0, n-1);

  while (q--) {
    int start, end;
    cin >> start >> end;
    start--;  end--;
    Node result;
    search_tree(tree, start, end, result);
    cout << result.overall.first << endl;
  }

  delete_tree(tree);
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
