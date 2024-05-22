#include <bits/stdc++.h>

using namespace std;

int main()
{
  int num[101] = {0};
  int price[4] = {0};

  for (int i = 1; i <= 3; i++) {
    cin >> price[i];
  }
  
  for (int i = 0; i < 3; i++) {
    int s, e;
    cin >> s >> e;
    for (int j = s; j < e; j++) {
      num[j]++;
    }
  }

  int ans = 0;
  for (int i = 0; i <= 100; i++) {
    ans += price[num[i]] * num[i];
  }

  cout << ans << endl;

  return 0;
}
