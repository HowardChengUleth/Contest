#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

long long solve()
{
  long long a[100000];
  long long K, C;
  int n;
  
  cin >> K >> C >> n >> a[0];
  for (int i = 1; i < n; i++) {
    a[i] = (K*a[i-1] + C) % 1000007;
  }

  sort(a, a+n);

  long long ps[100000];
  partial_sum(a, a+n, ps);

  long long sum = 0;
  for (int i = 1; i < n; i++) {
    sum += i*a[i] - ps[i-1];
  }
  return sum;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    cout << solve() << endl;
  }

  return 0;
}
