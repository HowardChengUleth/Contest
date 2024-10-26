#include <bits/stdc++.h>

using namespace std;

int N, S, M;
vector<int> d;

bool can_boo(int D)
{
  int start = 0;
  int chants = 0;

  for (int end = 0; end <= N; end++) {
    if (end - start >= S) {
      start = end;
      chants++;
    }
    if (d[end] < D) {
      start = end+1;
    }
  }

  return chants >= M;
}




int main()
{
  cin >> N >> S >> M;
  d.resize(N);
  for (auto &x : d) {
    cin >> x;
  }
  d.push_back(-1);

  int lo = 0;
  int hi = 1'000'000'000+1;
  while (hi - lo > 1) {
    int mid = lo + (hi - lo) / 2;
    if (can_boo(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << lo << endl;

  return 0;
}
