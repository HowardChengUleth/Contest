#include <bits/stdc++.h>

using namespace std;

int P, N;
string pattern[5];
int p[5], q[5];
set<int> times[5];

int main()
{
  p[0] = q[0] = -1;
  
  cin >> P >> N;
  for (int i = 0; i < P; i++) {
    cin >> pattern[i];
    if (i+1 < P) {
      cin >> p[i+1] >> q[i+1];
    }
  }

  for (int i = 0; i < N; i++) {
    string code;
    int t;
    cin >> code >> t;
    int index = find(pattern, pattern+P, code) - pattern;
    if (index == P) continue;

    if (index == 0) {
      times[0].insert(t);
    } else {
      auto lb = times[index-1].lower_bound(t - q[index]);
      auto ub = times[index-1].upper_bound(t - p[index]);
      if (lb != ub) {
	times[index].insert(t);
      }
    }
  }

  if (times[P-1].size() > 0) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}
