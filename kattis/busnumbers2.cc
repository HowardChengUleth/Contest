#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<int> cubes;
  for (int i = 1; i*i*i <= 400000; i++) {
    cubes.push_back(i*i*i);
  }

  int m;
  cin >> m;
  
  map<int, int> ways;
  for (int i = 0; i < cubes.size(); i++) {
    for (int j = i; j < cubes.size(); j++) {
      int sum = cubes[i] + cubes[j];
      if (sum <= m) {
	ways[sum]++;
      }
    }
  }

  int ans = -1;
  for (auto p : ways) {
    if (p.second > 1) {
      ans = p.first;
    }
  }

  if (ans < 0) {
    cout << "none" << endl;
  } else {
    cout << ans << endl;
  }

  return 0;
}
