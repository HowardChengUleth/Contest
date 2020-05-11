#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

const int MAX = 120*50000 + 1000;

int main(void)
{
  int S, M, N;
  while (cin >> S >> M >> N && S) {
    cin.ignore(1);

    int count[8] = {0};
    int cost = 0;
    for (int i = 0; i < M; i++) {
      string line;
      getline(cin, line);
      istringstream iss(line);
      int t;
      iss >> t;
      cost += t;
      while (iss >> t) {
	count[t-1]++;
      }
    }

    int start = 0;
    int all = 1;
    for (int i = 0; i < S; i++) {
      start = 3 * start + min(2, count[i]);
      all *= 3;
    }
    all--;

    int best[101][6561];
    fill(best[0], best[0]+all+1, MAX);
    best[0][start]= cost;

    for (int i = 1; i <= N; i++) {
      fill(best[i], best[i]+all+1, MAX);
      
      string line;
      getline(cin, line);
      istringstream iss(line);
      int cost;
      iss >> cost;
      bool subj[8] = {false};
      int t;
      while (iss >> t) {
	subj[t-1] = true;
      }

      for (int j = 0; j <= all; j++) {
	if (best[i-1][j] == MAX) continue;

	// don't hire that person
	best[i][j] = min(best[i][j], best[i-1][j]);

	// hire person i
	int newj = 0;
	int newsubj[8] = {0};
	int k = j;
	for (int l = S-1; l >= 0; l--) { 
	  newsubj[l] = min(2, k % 3 + subj[l]);
	  k /= 3;
	}
	for (int l = 0; l < S; l++) {
	  newj = 3 * newj + newsubj[l];
	}
	best[i][newj] = min(best[i][newj], best[i-1][j] + cost);
      }
    }

    cout << best[N][all] << endl;
  }
 
  return 0;
}
