#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

ll factorial(int n)
{
  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    ans *= i;
  }
  return ans;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    string S;
    ll N;

    cin >> S >> N;
    sort(S.begin(), S.end());

    while (S != "") {
      int n = S.length();
      ll f = factorial(n-1);
      ll index = N / f;
      cout << S[index];
      S.erase(index, 1);
      N %= f;
    }
    cout << endl;
  }
  return 0;
}
