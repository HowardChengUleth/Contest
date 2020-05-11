#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> Edge;

struct Node {
  int finish_num;
  bool seen;
  int num;

  Node() 
    : finish_num(-1), seen(false) { };

  void clear(int i)
  {
    num = i;
    finish_num = -1;
    seen = false;
  }

  bool operator<(const Node &n) const {
    return finish_num > n.finish_num;
  }
};
  
void dfs(Edge edge[], int e_index[], int v, int &step, Node node[])
{
  if (node[v].seen) {
    return;
  }

  node[v].seen = true;
  for (int i = e_index[v]; edge[i].first == v; i++) {
    dfs(edge, e_index, edge[i].second, step, node);
  }
  node[v].finish_num = ++step;
}

// use a sparse representation for edge list
Edge edge[100001];
Node node[100000];
int e_index[100000];
int order[100000];

void do_case(void)
{
  int n, m;
  cin >> n >> m;


  for (int i = 0; i < m; i++) {
    cin >> edge[i].first >> edge[i].second;
    edge[i].first--;   edge[i].second--;
  }
  sort(edge, edge+m);

  fill(e_index, e_index+n, 0);
  for (int i = m-1; i >= 0; i--) {
    e_index[edge[i].first] = i;
  }
  edge[m].first = n;

  // do DFS one way, and order them based on when each node is visited
  // while backing up in the recursion
  int step = 0;

  for (int i = 0; i < n; i++) {
    node[i].clear(i);
  }
  for (int i = 0; i < n; i++) {
    dfs(edge, e_index, i, step, node);
  }

  // now do DFS the other way, backward based on which DFS finished first
  sort(node, node+n);

  for (int i = 0; i < n; i++) {
    order[i] = node[i].num;
  }

  for (int i = 0; i < n; i++) {
    node[i].clear(i);
  }

  int count = 0;
  for (int i = 0; i < n; i++) {
    if (node[order[i]].seen) continue;
    count++;
    dfs(edge, e_index, order[i], step, node);
  }
  
  cout << count << endl;
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
