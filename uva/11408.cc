#include <iostream>

using namespace std;

int sum[5000001];
int partial[5000001];

int main(void)
{
  for (int n = 2; n <= 5000000; n++) {
    if (sum[n]) continue;
    for (int i = n; i <= 5000000; i += n) {
      sum[i] += n;
    }
  }

  for (int n = 2; n <= 5000000; n++) {
    partial[n] = partial[n-1];
    if (sum[sum[n]] == sum[n]) {
      partial[n]++;
    }
  }

  int a, b;
  while (cin >> a >> b && a) {
    cout << partial[b] - partial[a-1] << endl;
  }
  return 0;
}
