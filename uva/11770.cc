#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef vector<int> VI;

const int MAX_N = 10000;

void DFS_visit(const VI adj_list[], int N, pair<int,int> finish[], 
	       char color[], int &time, int u)
{
  color[u] = 1;
  time++;
  for (VI::const_iterator it = adj_list[u].begin(); it != adj_list[u].end();
       ++it) {
    int v = *it;
    if (color[v] == 0) {
      DFS_visit(adj_list, N, finish, color, time, v);
    }
  }
  color[u] = 2;
  finish[u].first = -(++time);
}

void DFS(const VI adj_list[], int N, pair<int,int> finish[])
{
  char color[MAX_N];
  fill(color, color+N, 0);
  int time = 0;

  for (int u = 0; u < N; u++) {
    if (color[u] == 0) {
      DFS_visit(adj_list, N, finish, color, time, u);
    }
  }
}

void DFS_visit(const VI adj_list[], int N, char color[], int u, VI &component)
{
  color[u] = 1;
  component.push_back(u);
  for (VI::const_iterator it = adj_list[u].begin(); it != adj_list[u].end();
       ++it) {
    int v = *it;
    if (color[v] == 0) {
      DFS_visit(adj_list, N, color, v, component);
    }
  }
}

void DFS(const VI adj_list[], int N, pair<int,int> finish[], vector<VI> &scc)
{
  char color[MAX_N];
  fill(color, color+N, 0);

  sort(finish, finish+N);

  for (int i = 0; i < N; i++) {
    int u = finish[i].second;
    if (color[u] == 0) {
      VI component;
      DFS_visit(adj_list, N, color, u, component);
      scc.push_back(component);
    }
  }
}

void do_case(void)
{
  int N, M;
  VI adj_list[MAX_N];
  VI adj_listR[MAX_N];      // all edges reversed
  
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    adj_list[a].push_back(b);
    adj_listR[b].push_back(a);
  }

  pair<int,int> finish[MAX_N];
  for (int i = 0; i < N; i++) {
    finish[i].second = i;
  }
  DFS(adj_list, N, finish);

  vector<VI> scc;
  DFS(adj_listR, N, finish, scc);

  bool on[MAX_N];
  fill(on, on+N, false);
  
  int count = 0;
  for (unsigned int i = 0; i < scc.size(); i++) {
    /*
    cout << "Component " << i+1 << endl;
    cout << "  ";
    */
    bool already_on = false;
    for (unsigned int j = 0; j < scc[i].size(); j++) {
      //      cout << " " << scc[i][j]+1 << " (" << on[scc[i][j]] << ')';
      already_on |= on[scc[i][j]];
    }
    //    cout << endl << endl;
    if (!already_on) {
      count++;
    }
    for (unsigned int j = 0; j < scc[i].size(); j++) {
      int u = scc[i][j];
      on[u] = true;
      for (unsigned int k = 0; k < adj_list[u].size(); k++) {
	on[adj_list[u][k]] = true;
      }
    }
  }
  cout << count << endl;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    do_case();
  }
  return 0;
}
