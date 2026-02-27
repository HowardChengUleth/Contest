#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  map<string,int> M;
  int best = 0;
  for (int i = 0; i < n; i++) {
    string s;
    int a;
    cin >> s >> a;
    M[s] += a;
    best = max(best, M[s]);
  }

  for (auto [s, a] : M) {
    if (a == best) {
      cout << s << endl;
    }
  }

  

  return 0;
}
