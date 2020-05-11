#include <iostream>
#include <stack>
#include <queue>
#include <cctype>

using namespace std;

struct Node {
  char label;
  int left, right;            // -1 for NULL

  Node(char c = ' ', int l = -1, int r = -1) 
    : label(c), left(l), right(r) { }
};

// returns the index of the root
int build_tree(Node tree[], const string &s)
{
  int len = s.length();
  stack<int> operands;

  for (int i = 0; i < len; i++) {
    if (islower(s[i])) {
      // leaf node, just push
      tree[i] = s[i];
      operands.push(i);
    } else {
      // operator
      int a = operands.top(); operands.pop();
      int b = operands.top(); operands.pop();
      tree[i] = Node(s[i], b, a);
      operands.push(i);
    }
  }

  return len-1;
}

void solve(const string &s)
{
  Node tree[10000];
  int root = build_tree(tree, s);

  string result;

  // now do bfs
  queue<int> q;
  q.push(root);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    result += tree[curr].label;
    if (tree[curr].left != -1) {
      q.push(tree[curr].left);
    }
    if (tree[curr].right != -1) {
      q.push(tree[curr].right);
    }
  }

  reverse(result.begin(), result.end());
  cout << result << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    string s;
    cin >> s;
    solve(s);
  }
  return 0;
}
