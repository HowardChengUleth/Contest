#include <iostream>
#include <algorithm>

using namespace std;

bool graph[100][100];
int N;

void DFS(int v, bool visited[], int skip = -1)
{
  visited[v] = true;
  for (int w = 0; w < N; w++) {
    if (graph[v][w] && !visited[w] && w != skip) {
      DFS(w, visited, skip);
    }
  }
}

void print_line()
{
  cout << '+';
  for (int i = 0; i < 2*N-1; i++) {
    cout << '-';
  }
  cout << '+' << endl;
}

void solve()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> graph[i][j];
    }
  }

  bool reach[100];
  bool reach2[100][100];

  fill(reach, reach+N, false);
  DFS(0, reach);

  for (int i = 0; i < N; i++) {
    fill(reach2[i], reach2[i]+N, false);
    if (i > 0) {
      DFS(0, reach2[i], i);
    }
  }

  for (int i = 0; i < N; i++) {
    print_line();
    for (int j = 0; j < N; j++) {
      cout << '|';
      if (reach[j] && !reach2[i][j]) {
	cout << 'Y';
      } else {
	cout << 'N';
      }
    }
    cout << '|' << endl;
  }
  print_line();
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ":" << endl;
    solve();
  }

  return 0;
}
