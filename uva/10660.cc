#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

int n;
int r[25], c[25], num[25];

int best;
int best_subset[5];

void search(bool subset[], int office, int index)
{
  if (office == 0) {
    int chosen[5];
    int t = 0;
    for (int i = 0; i < 25; i++) {
      if (subset[i]) {
	chosen[t++] = i;
      }
    }
    
    int total = 0;
    for (int i = 0; i < n; i++) {
      int dist = 1000;
      for (int j = 0; j < 5; j++) {
	dist = min(dist, abs(chosen[j]/5-r[i]) + abs(chosen[j] % 5 - c[i]));
      }
      total += dist * num[i];
    }
    if (total < best) {
      copy(chosen, chosen+5, best_subset);
      best = total;
    }
    return;
  }
  
  if (index >= 25) {
    return;
  }

  subset[index] = true;
  search(subset, office-1, index+1);
  subset[index] = false;
  search(subset, office, index+1);
}

void solve()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> r[i] >> c[i] >> num[i];
  }

  best = 10000000;
  bool subset[25] = { false };

  search(subset, 5, 0);
  cout << best_subset[0];
  for (int i = 1; i < 5; i++) {
    cout << ' ' << best_subset[i];
  }
  cout << endl;
}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
