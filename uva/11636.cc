#include <iostream>
#include <algorithm>

using namespace std;

int solve(int N)
{
  int ans = 0;
  int mult = 1;

  while (mult < N) {
    ans++;
    mult *= 2;
  }
  return ans;
}

int main(void)
{
  int N;
  int cases = 0;

  while (cin >> N && N >= 0) {
    cout << "Case " << ++cases << ": ";
    cout << solve(N) << endl;
  }
  return 0;
}
