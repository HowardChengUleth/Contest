#include <iostream>

using namespace std;

int main(void)
{
  int N;
  while (cin >> N) {
    int end[25];
    int pos[25];
    for (int i = 0; i < N; i++) {
      int car;
      cin >> car;
      pos[car] = i;
    }
    for (int i = 0; i < N; i++) {
      cin >> end[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
	if (pos[end[i]] > pos[end[j]]) ans++;
      }
    }
    cout << ans << endl;
  }

  return 0;
}
