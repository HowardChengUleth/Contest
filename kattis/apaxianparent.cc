#include <bits/stdc++.h>

using namespace std;

int main()
{
  string Y, P;
  cin >> Y >> P;

  const string vowel = "aeiou";
  
  string ans;
  if (Y.back() == 'e') {
    ans = Y + "x" + P;
  } else if (vowel.find(Y.back()) != string::npos) {
    Y.pop_back();
    ans = Y + "ex" + P;
  } else if (Y[Y.length()-2] == 'e' && Y.back() == 'x') {
    ans = Y + P;
  } else {
    ans = Y + "ex" + P;
  }

  cout << ans << endl;
  

  return 0;
}
