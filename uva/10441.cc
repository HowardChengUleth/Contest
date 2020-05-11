#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

int n;
string dict[1000];

struct Graph
{
  int in_deg[26], out_deg[26];
  int adj[26][26];
  int edge[26][26][1000];

  Graph()
  {
    fill(in_deg, in_deg+26, 0);
    fill(out_deg, out_deg+26, 0);
    for (int i = 0; i < 26; i++) {
      fill(adj[i], adj[i]+26, 0);
    }
  }

  void add_edge(int i, int j)
  {
    in_deg[j]++;
    out_deg[i]++;
    adj[i][j]++;
  }
  
  void add_edge(int dict_i)
  {
    string word = dict[dict_i];
    char first = word[0] - 'a', last = word[word.length()-1] - 'a';
    edge[first][last][adj[first][last]++] = dict_i;
    in_deg[last]++;
    out_deg[first]++;
  }

  void del_edge(int i, int j)
  {
    in_deg[j]--;
    out_deg[i]--;
    adj[i][j]--;
  }

  void dfs(int start, bool mark[26])
  {
    if (mark[start]) return;
    mark[start] = true;
    for (int i = 0; i < 26; i++) {
      if (adj[start][i]) {
	dfs(i, mark);
      }
    }
  }
  
  bool connected(int start)
  {
    bool mark[26] = {false};
    dfs(start, mark);
    for (int i = 0; i < 26; i++) {
      if (!mark[i] && (in_deg[i] > 0 || out_deg[i] > 0)) {
	return false;
      }
    }
    return true;
  }

  bool is_eulerian(int &start, int &end, bool fixed = false)
  {
    int start2 = -1, end2 = -1;
    bool found = false;
    for (int i = 0; i < 26; i++) {
      if (!in_deg[i] && !out_deg[i]) continue;
      found = true;
      if (in_deg[i] == out_deg[i]) continue;
      if (in_deg[i]+1 == out_deg[i]) {
	if (start2 != -1) return false;
	start2 = i;
      } else if (in_deg[i] == out_deg[i]+1) {
	if (end2 != -1) return false;
	end2 = i;
      } else {
	return false;
      }
    }

    if (!found) {
      return true;
    }

    if ((start2 == -1 && end2 != -1) || (start2 != -1 && end2 == -1)) {
      return false;
    }
					 
    if (fixed) {
      if ((start2 != -1 && end2 != -1) && !(start == start2 && end == end2)) {
	return false;
      }
      if ((start2 == -1 && end2 == -1) && (start != end || !in_deg[start] )) {
	return false;
      }
    } else {
      start = start2;
      end = end2;
    }
    
    if (start != -1 && end != -1) {
      // eulerian path?
      return connected(start);
    } else if (start == -1 && end == -1) {
      // eulerian cycle
      for (int i = 0; i < 26; i++) {
	if (in_deg[i] || out_deg[i]) {
	  start = end = i;
	  return connected(start);
	}
      }
    } else {
      return false;
    }
    assert(false);
    return false;
  }

};

void solve()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> dict[i];
  }
  sort(dict, dict+n, greater<string>());

  Graph G;
  for (int i = 0; i < n; i++) {
    G.add_edge(i);
  }

  int start, end;
  if (!G.is_eulerian(start, end)) {
    cout << "***" << endl;
    return;
  }

  
  for (int i = 0; i < n; i++) {
    // repeatedly try to move from start

    string best;
    int best_j = -1;
    for (int j = 0; j < 26; j++) {
      if (!G.adj[start][j]) continue;
      G.del_edge(start, j);
      if (G.is_eulerian(j, end, true)) {
	string word = dict[G.edge[start][j][G.adj[start][j]]];
	if (best_j < 0 || word < best) {
	  best = word;
	  best_j = j;
	}
      }
      G.add_edge(start, j);
    }

    G.del_edge(start, best_j);
    cout << best;
    if (i < n-1) cout << '.';
    start = best_j;
  }
  cout << endl;
}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
