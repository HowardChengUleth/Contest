#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int T;
  cin >> T;
  for (int id = 1; id <= T; id++) {
    cout << "Case " << id << ": ";
    int N;
    cin >> N;

    int best = 0;
    for (int i = 0; i < N; i++) {
      int t;
      cin >> t;
      best = max(t, best);
    }
    cout << best << endl;
  }

  return 0;
}
