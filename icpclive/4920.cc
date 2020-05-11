#include <iostream>
#include <vector>

using namespace std;

bool solve()
{
  int k;
  cin >> k;
  if (!k) return false;

  vector<int> P(k+1);
  P[0] = 0;
  for (int i = 1; i <= k; i++) {
    cin >> P[i];
  }

  bool printed = false;
  for (int i = 1; i <= k; i++) {
    int t = P[i] - P[i-1];
    if (!t) continue;
    for (int j = 0; j < t; j++) {
      if (printed) cout << ' ';
      cout << i;
      printed = true;
    }
  }
  cout << endl;

  
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
