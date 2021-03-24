#include <bits/stdc++.h>

using namespace std;

int N, fee[1000];

long long ans[1000][1000];

long long f(int start, int step)
{
  if (ans[start][step]) {
    return ans[start][step];
  }

  int t = fee[start];
  if (start == N-1) {
    return ans[start][step] = t;
  }

  int back = start - step;
  int forward = start + step + 1;
  long long t1 = (back >= 0) ? f(back, step) + t : INT_MAX;
  long long t2 = (forward < N) ? f(forward, step+1) + t : INT_MAX;
  return ans[start][step] = min((long long)INT_MAX, min(t1, t2));
}

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> fee[i];
  }

  cout << f(1, 1) << endl;

  return 0;
}
