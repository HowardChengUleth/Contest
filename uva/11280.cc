#include <iostream>
#include <map>
#include <string>
#include <climits>

using namespace std;

void solve()
{
  int N;
  cin >> N;

  map<string, int> name;
  for (int i = 0; i < N; i++) {
    string city;
    cin >> city;
    name[city] = i;
  }

  int cost[100][100];
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cost[i][j] = -1;
    }
  }

  int M;
  cin >> M;
  while (M--) {
    string city1, city2;
    int c;
    cin >> city1 >> city2 >> c;
    if (cost[name[city1]][name[city2]] < 0 ||
	c < cost[name[city1]][name[city2]]) {
      cost[name[city1]][name[city2]] = c;
    }
  }

  int src = name["Calgary"];
  
  int Q;
  cin >> Q;
  while (Q--) {
    int stops;
    cin >> stops;

    int D[100][100];
    for (int i = 0; i < N; i++) {
      if (cost[src][i] >= 0) {
	D[0][i] = cost[src][i];
      } else {
	D[0][i] = INT_MAX;
      }
    }
    D[0][src] = 0;
    stops = min(stops, N-1);
    
    for (int i = 1; i <= stops; i++) {
      for (int v = 0; v < N; v++) {
	D[i][v] = INT_MAX;
      }
      for (int v = 0; v < N; v++) {
	for (int w = 0; w < N; w++) {
	  if (cost[v][w] >= 0 && D[i-1][v] != INT_MAX) {
	    D[i][w] = min(D[i][w], D[i-1][v] + cost[v][w]);
	  }
	}
      }
    }

    int dest = name["Fredericton"];
    int best = D[0][dest];
    for (int i = 1; i <= stops; i++) {
      best = min(best, D[i][dest]);
    }
    
    if (best < INT_MAX) {
      cout << "Total cost of flight(s) is $" << best << endl;
    } else {
      cout << "No satisfactory flights" << endl;
    }
  }
}

int main(void)
{
  int S;
  cin >> S;
  for (int i = 1; i <= S; i++) {
    if (i > 1) cout << endl;
    cout << "Scenario #" << i << endl;
    solve();
  }
  return 0;
}
