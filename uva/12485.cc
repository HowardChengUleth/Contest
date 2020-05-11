#include <iostream>

using namespace std;

int main(void)
{
  int N;
  while (cin >> N) {
    int note[10001];
    int sum = 0;
    for (int i = 0; i < N; i++) {
      cin >> note[i];
      sum += note[i];
    }

    if (sum % N != 0) {
      cout << -1 << endl;
      continue;
    }

    int goal = sum/N;
    int ans = 1;
    for (int i = 0; i < N && note[i] < goal; i++) {
      ans += goal - note[i];
    }
    cout << ans << endl;
  }

  return 0;
}
