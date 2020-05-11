//
// Just try all possible n! permutations
//

#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

typedef pair<pair<int, int>, int> Constraint;

int main(void)
{
  int m, n;
  while (cin >> n >> m && (n || m)) {
    Constraint con[20];
    for (int i = 0; i < m; i++) {
      cin >> con[i].first.first >> con[i].first.second >> con[i].second;
    }
    int perm[8];
    for (int i = 0; i < n; i++) {
      perm[i] = i;
    }
    int count = 0;
    do {
      bool good = true;
      for (int i = 0; i < m; i++) {
	int d = abs(perm[con[i].first.first] - perm[con[i].first.second]);
	int c = con[i].second;
	if ((c > 0 && d > c) || (c < 0 && d < -c)) {
	  good = false;
	  break;
	}
      }
      if (good) {
	count++;
      }
    } while (next_permutation(perm, perm+n));
    cout << count << endl;
  }
  return 0;
}
