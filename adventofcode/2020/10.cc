#include <bits/stdc++.h>

using namespace std;

vector<int> v;

int main()
{
  v.push_back(0);
  
  int x;
  while (cin >> x) {
    v.push_back(x);
  }

  sort(begin(v), end(v));
  v.push_back(v.back()+3);

  int gap[4] = {0};
  for (int i = 1; i < v.size(); i++) {
    gap[v[i] - v[i-1]]++;
  }

  cout << "A = " << gap[1] * gap[3] << endl;

  vector<long long> ways(v.size(), 0);
  ways[0] = 1;
  for (int i = 1; i < v.size(); i++) {
    for (int j = 1; i-j >= 0 && v[i] - v[i-j] <= 3; j++) {
      ways[i] += ways[i-j];
    }
  }

  cout << "B = " << ways[v.size()-1] << endl;
  
  
  return 0;
}
