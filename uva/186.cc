#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*
 * Floyd's Algorithm
 *
 * Author: Howard Cheng
 *
 * The following code takes a graph stored in an adjacency matrix "graph",
 * and returns the shortest distance from node i to node j in dist[i][j].
 * We assume that the weights of the edges is not DISCONNECT, and the
 * DISCONNECT constant is used to indicate the absence of an edge.
 *
 * Call extract_path to return the path, as well as its length (in terms
 * of vertices).  The length is -1 if no such path exists.
 *
 */

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_NODES = 100;
const int DISCONNECT = -1;

int graph[MAX_NODES][MAX_NODES];
int dist[MAX_NODES][MAX_NODES];
int succ[MAX_NODES][MAX_NODES];

void floyd(int n)
{
  int i, j, k;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      dist[i][j] = graph[i][j];
      if (i == j || graph[i][j] == DISCONNECT) {
	succ[i][j] = -1;
      } else {
	succ[i][j] = j;
      }
    }
  }

  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        if (dist[i][k] != DISCONNECT && dist[k][j] != DISCONNECT) {
          int temp = dist[i][k] + dist[k][j];
          if (dist[i][j] == DISCONNECT || dist[i][j] > temp) {
            dist[i][j] = temp;
	    succ[i][j] = succ[i][k];
          } else if (dist[i][j] == temp && succ[i][k] < succ[i][j]) {
            /* put tie-breaking on paths here */

	    /* e.g. the test above chooses lexicographically smallest */
	    /*      paths, but ignores the number of vertices in the  */
	    /*      path.  To really do lexicographically sorting     */
	    /*      properly, you also need to have len[i][j] which   */
	    /*      can be computed easily as well.                   */
	    succ[i][j] = succ[i][k];
	  }
        }
      }
    }
  }

  for (i = 0; i < n; i++) {
    dist[i][i] = 0;
  }
}

int extract_path(int u, int v, int path[])
{
  int len = 0;
  
  if (dist[u][v] == DISCONNECT) {
    return -1;
  }

  path[len++] = u;
  while (u != v) {
    u = succ[u][v];
    path[len++] = u;
  }

  return len;
}


string city[100];
int num_cities;
map<string,int> M;
string route[100][100];

void read_highway(void)
{
  string line;

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      graph[i][j] = DISCONNECT;
    }
  }

  while (getline(cin, line) && line != "") {
    int pos = line.find(",");
    string city1 = line.substr(0, pos);
    line.erase(0, pos+1);
    pos = line.find(",");
    string city2 = line.substr(0, pos);
    line.erase(0, pos+1);
    pos = line.find(",");
    string r = line.substr(0, pos);
    line.erase(0, pos+1);
    int len = atoi(line.c_str());
    
    if (M.find(city1) == M.end()) {
      M[city1] = num_cities;
      city[num_cities++] = city1;
    }
    if (M.find(city2) == M.end()) {
      M[city2] = num_cities;
      city[num_cities++] = city2;
    }
    int u = M[city1], v = M[city2];
    if (graph[u][v] == DISCONNECT || len < graph[u][v]) {
      graph[u][v] = graph[v][u] = len;
      route[u][v] = route[v][u] = r;
    }
  }
}

int main(void)
{
  read_highway();
  floyd(num_cities);
  
  string line;
  while (getline(cin, line)) {
    int pos = line.find(",");
    string city1 = line.substr(0, pos);
    line.erase(0, pos+1);
    string city2 = line;

    cout << endl << endl;
    cout << "From                 To                   Route      Miles" 
	 << endl;
    cout << "-------------------- -------------------- ---------- -----" 
	 << endl;

    int path[MAX_NODES];
    int len = extract_path(M[city1], M[city2], path);

    for (int i = 0; i < len-1; i++) {
      cout << setw(20) << left << city[path[i]] << " "
	   << setw(20) << city[path[i+1]] << " "
	   << setw(10) << route[path[i]][path[i+1]] << " "
	   << setw(5) << right << graph[path[i]][path[i+1]] << endl;
    }

    cout << "                                                     -----"
	 << endl;
    cout << "                                          Total      "
	 << setw(5) << right << dist[M[city1]][M[city2]] << endl;

  }

  return 0;
}

