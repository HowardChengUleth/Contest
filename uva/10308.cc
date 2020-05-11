/* @JUDGE_ID: 1102NT 10308 C++ "" */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <list>

using namespace std;

struct Node {
  list<int> nbrs;
  list<int> dist;

  void add_edge(int v, int d)
  {
    nbrs.push_back(v);
    dist.push_back(d);
  }

  void clear(void)
  {
    nbrs.clear();
    dist.clear();
  }
};

Node nodes[10000];

void dfs(int v, int n, char *visited, int *dist, int d)
{
  int w;
  list <int>::iterator i, j;

  visited[v] = 1;
  dist[v] = d;
  
  i = nodes[v].nbrs.begin();
  j = nodes[v].dist.begin();
  while (i != nodes[v].nbrs.end()) {
    w = *i;
    if (!visited[w]) {
      dfs(w, n, visited, dist, d+(*j));
    }
    i++;
    j++;
  }
}

int main(void)
{
  char buffer[1024];
  char visited[10000];
  int dist[10000];
  int i, j, k, d;
  int n;

  while (fgets(buffer, 1024, stdin)) {
    n = 0;

    while (buffer[0] != '\n') {
      sscanf(buffer, "%d %d %d", &i, &j, &d);
      if (i > n) {
	for (k = n; k < i; k++) {
	  nodes[k].clear();
	}
	n = i;
      }
      if (j > n) {
	for (k = n; k < j; k++) {
	  nodes[k].clear();
	}
	n = j;
      }
      i--;
      j--;
      nodes[i].add_edge(j, d);
      nodes[j].add_edge(i, d);

      if (!fgets(buffer, 1024, stdin)) {
	break;
      }
    }

    memset(visited, 0, 10000);
    dfs(0, n, visited, dist, 0);
    d = dist[0];
    j = 0;
    for (i = 0; i < n; i++) {
      if (d < dist[i]) {
	d = dist[i];
	j = i;
      }
    }

    memset(visited, 0, 10000);
    dfs(j, n, visited, dist, 0);
    d = dist[0];
    for (i = 0; i < n; i++) {
      if (d < dist[i]) {
	d = dist[i];
      }
    }

    printf("%d\n", d);
  }

  return 0;
}
