#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;
  bool diff = (N % 2 != 0);
  
  string s1, s2;
  cin >> s1 >> s2;
  for (int i = 0; i < s1.length(); i++) {
    if ((diff && s1[i] == s2[i]) ||
	(!diff && s1[i] != s2[i])) {
      cout << "Deletion failed" << endl;
      return 0;
    }
  }

  cout << "Deletion succeeded" << endl;
  return 0;
}
