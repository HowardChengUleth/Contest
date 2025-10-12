#include <bits/stdc++.h>
#include <cassert>

using namespace std;

int main()
{
  int n, k;
  cin >> n >> k;

  vector<long double> eval(n+1), eval2(n+1);
  
  for (auto &x : eval) {
    cin >> x;
  }
  eval[n] = 0.0;    // fake first element to make partial sums easier
  
  sort(begin(eval), end(eval));
  for (int i = 0; i < n+1; i++) {
    eval2[i] = eval[i] * eval[i];
    assert(eval[i] >= 0.0);
    assert(eval2[i] >= 0.0);
  }

  partial_sum(begin(eval), end(eval), begin(eval));
  partial_sum(begin(eval2), end(eval2), begin(eval2));

  long double badness = DBL_MAX;
  for (int i = k; i < n+1; i++) {
    long double sum = eval[i] - eval[i-k];
    long double sum2 = eval2[i] - eval2[i-k];
    long double sse = sum2 - sum*sum/k;
    
    badness = min(badness, sse);
  }

  cout << fixed << setprecision(10) << badness << endl;

  return 0;
}
