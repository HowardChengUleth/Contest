#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> d;

bool check(int workers)
{
  vector<int> jobs(workers, 0), last(workers, 0);
  /*
  for (auto x : d) {
    for (int i = 0; i < workers; i++) {
      if (jobs[i] < K && last[i] < x) {
	jobs[i]++;
	last[i]++;
	break;
      }
    }
  }
  return count(begin(jobs), end(jobs), K) == workers;

  */

  int index = 0;
  for (int k = 0; k < K; k++) {
    for (int i = 0; i < workers; i++) {
      while (index < N && last[i] >= d[index]) {
	index++;
      }
      if (index < N) {
	jobs[i]++;
	last[i]++;
	index++;
      } else {
	return false;
      }
    }
  }
  return true;
}

int main()
{
  cin >> N >> K;
  d.resize(N);
  for (auto &x : d) {
    cin >> x;
  }
  sort(begin(d), end(d));

  int curr = 1;
  int lo = 0, hi = N/K;
  if (check(hi)) {
    cout << hi << endl;
    return 0;
  }
  while (hi - lo > 1) {
    int mid = (lo + hi)/2;
    if (check(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  cout << lo << endl;
  
  return 0;
}
