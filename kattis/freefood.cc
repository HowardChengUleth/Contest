#include <bits/stdc++.h>

using namespace std;

int main()
{
  bool food[366] = {false};

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int s, t;
    cin >> s >> t;
    fill(food+s, food+t+1, true);
  }

  cout << count(food, food+366, true) << endl;
  
  return 0;
}
