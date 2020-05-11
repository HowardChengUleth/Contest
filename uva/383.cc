/* @JUDGE_ID: 1102NT 383 C++ "" */

#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

int graph[30][30];

int main(void)
{
  int cases;

  cin >> cases;
  cout << "SHIPPING ROUTES OUTPUT" << endl << endl;
  
  for (int i = 1; i <= cases; i++) {
    int M, N, P;
    map<string,int> warehouse;
    string s, t;

    cout << "DATA SET " << setw(2) << i << endl << endl;
    cin >> M >> N >> P;

    for (int j = 0; j < M; j++) {
      for (int k = 0; k < M; k++) {
	graph[j][k] = 200;   // no route can be this long
      }
    }

    for (int j = 0; j < M; j++) {
      cin >> s;
      warehouse[s] = j;
    }
    for (int j = 0; j < N; j++) {
      cin >> s >> t;
      graph[warehouse[s]][warehouse[t]] = 1;
      graph[warehouse[t]][warehouse[s]] = 1;
    }

    for (int k = 0; k < M; k++) {
      for (int i = 0; i < M; i++) {
	for (int j = 0; j < M; j++) {
	  if (graph[i][k] + graph[k][j] < graph[i][j]) {
	    graph[i][j] = graph[i][k] + graph[k][j];
	  }
	}
      }
    }

    for (int j = 0; j < P; j++) {
      int size;
      cin >> size >> s >> t;
      if (graph[warehouse[s]][warehouse[t]] > M) {
	cout << "NO SHIPMENT POSSIBLE" << endl;
      } else {
	cout << "$" << size*100*graph[warehouse[s]][warehouse[t]] << endl;
      }
    }

    cout << endl;
  }

  cout << "END OF OUTPUT" << endl;
  return 0;
}

