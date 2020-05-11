#include <bits/stdc++.h>

using namespace std;

string s;
int n;

int count(int i, int j)
{
  string p = s.substr(i, j-i+1);

  int c = 0;
  string::size_type index = 0;
  
  while ((index = s.find(p, index)) != string::npos) {
    c++;
    index += j-i+1;
  }
  return c;
}

int main()
{

  cin >> s;
  n = s.length();
  int best = n;
  
  n = s.length();
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      int t = count(i, j);
      int len = n - t*(j-i+1) + t + (j-i+1);
      best = min(best, len);
    }
  }

  cout << best << endl;
  return 0;
}
