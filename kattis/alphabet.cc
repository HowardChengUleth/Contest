#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;

  int lislen[50];
  for (int i = 0; i < s.length(); i++) {
    lislen[i] = 1;
    for (int j = 0; j < i; j++) {
      if (s[j] < s[i]) {
	lislen[i] = max(lislen[i], lislen[j]+1);
      }
    }
  }

  cout << 26 - *max_element(lislen, lislen+s.length()) << endl;

  return 0;
}
