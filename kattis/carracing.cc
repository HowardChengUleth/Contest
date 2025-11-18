#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;

  int pos[6] = {0};
  int num[6] = {0};
  
  cin >> n;
  for (int i = 0; i < n; i++) {
    int car, p;
    cin >> car >> p;
    pos[car] += p;
    num[car]++;
  }

  int best_pos = INT_MAX, best_car = -1;
  for (int i = 1; i <= 5; i++) {
    int p = pos[i] / num[i];
    if (p < best_pos) {
      best_car = i;
      best_pos = p;
    }
  }
  cout << best_car << endl;
  cout << best_pos << endl;
  
  return 0;
}
