#include <bits/stdc++.h>

using namespace std;

int product(string s)
{
  auto comma = s.find(',');
  if (comma == string::npos)
    return 0;

  size_t i1, i2;
  string xstr = s.substr(0, comma);
  string ystr = s.substr(comma+1);
  int x = stoi(xstr, &i1);
  int y = stoi(ystr, &i2);
  if (i1 == xstr.length() && i2 == ystr.length()) {
    cout << "x, y = " << x << ' ' << y << endl;
    return x*y;
  } else {
    return 0;
  }
  

}

int main()
{
  string s, t;

  while (getline(cin, t)) {
    s += t;
  }

  long long ans = 0;
  size_t pos = 0, mulstart;

  while ((mulstart = s.find("mul(", pos)) != string::npos) {
    auto mulend = s.find(")", mulstart);
    if (mulend == string::npos) {
      break;
    }
    int temp = product(s.substr(mulstart+4, mulend-mulstart-4));
    ans += temp;
    if (temp > 0) {
      pos = mulend+1;
    } else {
      pos = mulstart+1;
    }
  }

  cout << ans << endl;
  
  return 0;
}
