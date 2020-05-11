#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

typedef long long ll;

double dist(const pair<int, int> &p1, const pair<int, int> &p2)
{
  int dx = p1.first - p2.first;
  int dy = p1.second - p2.second;
  return sqrt(dx*dx + dy*dy);
}

double best_sum(pair<int, int> loc[], int n, int start)
{
  if (start >= n) {
    return 0.0;
  }

  // first one is fixed
  double best = -1;
  for (int i = start+1; i < n; i++) {
    swap(loc[i], loc[start+1]);
    double temp = best_sum(loc, n, start+2) + dist(loc[start], loc[start+1]);
    if (best == -1 || temp < best) {
      best = temp;
    }
    swap(loc[i], loc[start+1]);
  }
  
  return best;
}

int main(void)
{
  int n;
  int case_num = 1;
  while (cin >> n && n > 0) {
    string name;
    pair<int, int> loc[16];

    for (int i = 0; i < 2*n; i++) {
      cin >> name >> loc[i].first >> loc[i].second;
    }

    cout << "Case " << case_num++ << ": " << fixed << setprecision(2)
	 << best_sum(loc, 2*n, 0) << endl;
  }

  return 0;
}
