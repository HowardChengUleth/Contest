#include <bits/stdc++.h>

using namespace std;

int main()
{
  int nn;
  cin >> nn;
  string s;
  cin >> s;

  for (int c = 'z'; c >= 'a'; c--) {
    int n = s.length();
    bool done = false;
    while (!done) {
      done = true;
      for (int i = n-1; i >= 0; i--) {
	if (s[i] == c &&
	    ((i < n-1 && s[i+1] == c-1) ||
	     (i > 0 && s[i-1] == c-1))) {
	  s.erase(i, 1);
	  done = false;
	}
      }
    }
    
  }
  cout << nn - s.length() << endl;

  return 0;
}
