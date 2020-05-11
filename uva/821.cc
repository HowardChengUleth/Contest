/* @JUDGE_ID: 1102NT 821 C++ "" */

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

bool present[100];
int graph[100][100];
const int DISCONNECT = -1;

bool read_graph(void)
{
  fill(present, present+100, false);
  for (int i = 0; i < 100; i++) {
    fill(graph[i], graph[i]+100, DISCONNECT);
    graph[i][i] = 0;
  }
  
  int x, y;
  int count = 0;
  while (cin >> x >> y && (x || y)) {
    count++;
    graph[x-1][y-1] = 1;
    present[x-1] = present[y-1] = true;
  }
  return count > 0;
}

double average(void)
{
  int i, j, k;

  for (k = 0; k < 100; k++) {
    for (i = 0; i < 100; i++) {
      for (j = 0; j < 100; j++) {
	if (graph[i][k] == DISCONNECT || graph[k][j] == DISCONNECT) continue;
	if (graph[i][j] == DISCONNECT || 
	    graph[i][j] > graph[i][k] + graph[k][j]) {
	  graph[i][j] = graph[i][k] + graph[k][j];
	}
      }
    }
  }

  double sum = 0.0;
  int count = 0;
  for (i = 0; i < 100; i++) {
    if (!present[i]) continue;
    for (j = 0; j < 100; j++) {
      if (!present[j] || i == j) continue;
      count++;
      sum += graph[i][j];
    }
  }
  return sum / count;
}

int main(void)
{
  int case_num = 1;
  while (read_graph()) {
    cout.setf(ios::fixed);
    cout.precision(3);
    cout << "Case " << case_num++ << ": average length between pages = "
	 << average() << " clicks" << endl;
  }

  return 0;
}
