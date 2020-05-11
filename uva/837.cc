#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <iomanip>

using namespace std;

void do_case()
{
  int n;
  cin >> n;

  vector<pair<double, int> >info(2*n);
  vector<bool> inside(n);
  vector<double> factor(n);

  for (int i = 0; i < n; i++) {
    double left, right, y;
    cin >> left >> y >> right >> y >> factor[i];
    info[2*i] = make_pair(left, i);
    info[2*i+1] = make_pair(right, i);
  }
  sort(info.begin(), info.end());

  fill(inside.begin(), inside.end(), false);

  double portion = 1.0;
  cout << 2*n+1 << endl;
  cout << "-inf" << ' ' << fixed << setprecision(3) << info[0].first << ' '
       << portion << endl;
  for (int i = 0; i < 2*n-1; i++) {
    int line = info[i].second;
    inside[line] = !inside[line];
    portion = 1.0;
    for (int j = 0; j < n; j++) {
      if (inside[j]) {
	portion *= factor[j];
      }
    }
    cout << info[i].first << ' ' << info[i+1].first << ' ' << portion << endl;
  }
  portion = 1.0;
  cout << info[2*n-1].first << ' ' << "+inf" << ' ' << portion << endl;

}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    do_case();
    if (T) {
      cout << endl;
    }
  }
  return 0;
}
