// do binary search on the answer
//
// If we know how many workers there are, we can check whether we can do it
// by assigning the jobs with increasing deadlines.  We can greedily assign
// the jobs to each worker one round at a time until all workers have K jobs.

#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> d;

bool check(int workers)
{
  vector<int> jobs(workers, 0), last(workers, 0);

  int index = 0;

  // try to assign 1 job to each worker each round
  for (int k = 0; k < K; k++) {
    for (int i = 0; i < workers; i++) {
      // find the first job that worker i can do
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
