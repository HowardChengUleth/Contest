#include <bits/stdc++.h>

using namespace std;

int M;
int c[100];

int N, E;
int belt[101];
int bill[101];

int chef_pos = 0;
int menu_index = 0;

int main()
{
  cin >> M;
  for (int i = 0; i < M; i++) {
    cin >> c[i];
  }

  cin >> N >> E;

  int curr_t = 0;
  for (int i = 0; i < E; i++) {
    int t, p;
    cin >> t >> p;

    while (curr_t < t) {
      if (belt[chef_pos] == 0) {
	belt[chef_pos] = c[menu_index];
	menu_index = (menu_index + 1) % M;
      }
      chef_pos = (chef_pos + N) % (N+1);
      curr_t++;
    }

    int pos = (p + (N+1 - curr_t % (N+1))) % (N+1);
    bill[p] += belt[pos];
    belt[pos] = 0;
  }

  for (int p = 1; p <= N; p++) {
    cout << bill[p] << endl;
  }
  
  return 0;
}
