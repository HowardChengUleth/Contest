#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<string> v(n);
  for (auto &s: v) {
    cin >> s;
  }

  cout << count_if(begin(v), end(v),
		   [](string s) {
		     return s.find("CD") == string::npos;
		   }) << endl;
  
  return 0;
}
