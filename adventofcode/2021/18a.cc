#include <bits/stdc++.h>

using namespace std;

struct Node
{
  int val;
  Node *left, *right;

  Node(int v, Node *ll, Node *rr)
    : val{v}, left{ll}, right{rr}
  {
  }
};

Node *parse(string s, int start, int end)
{
  if (s[start] == '[') {
    int level = 0;
    for (int i = start+1; i < end; i++) {
      if (s[i] == '[') level++;
      else if (s[i] == ']') level--;
      else if (s[i] == ' ' && !level) {
	Node *left = parse(s, start+1, i);
	Node *right = parse(s, i+1, end-1);
	return new Node(-1, left, right);
      }
    }
    assert(false);
  } else {
    assert(isdigit(s[start]));
    return new Node(s[start]-'0', nullptr, nullptr);
  }
}

void print(Node *root)
{
  if (root) {
    if (root->left && root->right) {
      cout << "[";
      print(root->left);
      cout << ",";
      print(root->right);
      cout << "]";
    } else {
      cout << root->val;
    }
  }
}

Node *add(Node *op1, Node *op2)
{
  return new Node(-1, op1, op2);
}

bool explode(Node *root, int level, int &lval, int &rval)
{
  if (!(root->left && root->right)) {
    return false;
  }

  if (root->left->val >= 0 && root->right->val >= 0 && level >= 4) {
    lval = root->left->val;
    rval = root->right->val;
    delete root->left;
    delete root->right;
    root->left = root->right = nullptr;
    root->val = 0;
    return true;
  } else {
    bool done = explode(root->left, level+1, lval, rval);
    if (done) {
      if (rval >= 0) {
	Node *p = root->right;
	while (p->left) {
	  p = p->left;
	}
	p->val += rval;
	rval = -1;
      }
      return true;
    }
    done = explode(root->right, level+1, lval, rval);
    if (done) {
      if (lval >= 0) {
	Node *p = root->left;
	while (p->right) {
	  p = p->right;
	}
	p->val += lval;
	lval = -1;
      }
      return true;
    }
    return false;
  }
}

bool split(Node *root)
{
  if (root->left && root->right) {
    if (split(root->left)) {
      return true;
    } else {
      return split(root->right);
    }
  } else if (root->val < 10) {
    return false;
  } else {
    int lval = root->val / 2;
    int rval = root->val - lval;
    root->left = new Node(lval, nullptr, nullptr);
    root->right = new Node(rval, nullptr, nullptr);
    root->val = -1;
    return true;
  }
}

Node *reduce(Node *root)
{
  bool done = false;
  while (!done) {
    done = true;
    int lval, rval;
    if (explode(root, 0, lval, rval)) {
      done = false;
    } else if (split(root)) {
      done = false;
    }
  }

  return root;
}

long long mag(Node *root)
{
  if (root->left && root->right) {
    return 3*mag(root->left) + 2*mag(root->right);
  } else {
    return root->val;
  }

}

int main()
{
  vector<Node *> input;

  string s;
  while (getline(cin, s)) {
    replace(begin(s), end(s), ',', ' ');
    input.push_back(parse(s, 0, s.length()));
  }

  // add them
  Node *sum = input[0];;
  sum = reduce(sum);
  for (int i = 1; i < input.size(); i++) {
    sum = add(sum, input[i]);
    sum = reduce(sum);
  }


  print(sum);
  cout << endl;

  cout << mag(sum) << endl;
  

  
  
  return 0;
}

