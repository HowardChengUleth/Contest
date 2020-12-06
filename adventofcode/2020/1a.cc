#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<long long> v;
  int x;
  
  while (cin >> x) {
    v.push_back(x);
  }

  int n = v.size();
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      for (int k = j+1; k < n; k++) {
	if (v[i] + v[j] + v[k] == 2020) {
	  cout << v[i]*v[j]*v[k] << endl;
	}
      }
    }
  }

  
  return 0;
}
