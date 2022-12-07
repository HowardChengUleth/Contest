#include <bits/stdc++.h>

using namespace std;

struct Node
{
  string name;
  bool is_dir;
  int size;
  vector<Node *> child;

  Node(string N)
    : name(N), is_dir(true) { }
  Node(string N, int S)
    : name(N), is_dir(false), size(S) { }

  ~Node()
  {
    for (auto p : child) {
      delete p;
    }
  }

  void print() const
  {
    cout << name << ' ';
    if (is_dir) {
      cout << "dir";
    } else {
      cout << size;
    }
  }
};

Node *parse(string curr = "/")
{
  Node *root = new Node(curr);
		    
  string line;
  getline(cin, line);
  assert(line == "$ ls");

  while (getline(cin, line) && line != "$ cd ..") {
    istringstream iss(line);
    string first, second;
    iss >> first >> second;

    if (first == "dir") {
    } else if (first == "$") {
      assert(second == "cd");
      string dirname;
      iss >> dirname;
      root->child.push_back(parse(dirname));
    } else {
      int size = stoi(first);
      root->child.push_back(new Node(second, size));
    }
  }
  return root;
}

void print(Node *root, int indent = 0)
{
  for (int i = 0; i < indent; i++) {
    cout << ' ';
  }
  root->print();
  cout << endl;
  for (auto c : root->child) {
    print(c, indent+2);
  }
}

int final_ans = 0;

int total_size(Node *root)
{
  if (!root->is_dir) {
    return root->size;
  }

  long long ans = 0;
  for (auto c : root->child) {
    ans += total_size(c);
  }

  if (ans <= 100000) {
    final_ans += ans;
  }
  return ans;
}

int main()
{
  string line;
  getline(cin, line);
  Node *root = parse();
  total_size(root);
  cout << final_ans << endl;
  delete root;
  return 0;
}
