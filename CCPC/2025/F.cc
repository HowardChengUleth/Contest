#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  priority_queue<double> pq;
  for (int i = 0; i < n; i++) {
    double x;
    cin >> x;
    pq.push(x);
  }

  double truck = 1.0;
  double total = 0.0;
  while (!pq.empty()) {
    double pool = pq.top();
    pq.pop();
    if (truck > pool) {
      double f = (truck + pool) / 2.0;
      truck = f;
      pool = f;
    }
    total += pool;
  }

  cout << fixed << setprecision(10) << total << endl;
  
  
  return 0;
}
