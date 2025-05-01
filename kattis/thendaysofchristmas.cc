#include <bits/stdc++.h>

using namespace std;

int sum(int N)
{
  return N*(N+1)/2;
}

int f(int N)
{
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    ans += sum(i);
  }
  return ans;
}

int main()
{
  int N;
  cin >> N;

  cout << sum(N) << endl;
  cout << f(N) << endl;

  return 0;
}
