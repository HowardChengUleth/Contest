#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;

  bool found = false;
  for (int i = 0; i < 5; i++) {
    cin >> s;
    if (s.find("FBI") != string::npos) {
      cout << i+1 << ' ';
      found = true;
    }
  }
  if (!found) {
    cout << "HE GOT AWAY!";
  }
  cout << endl;

  return 0;
}
