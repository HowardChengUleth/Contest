#include <bits/stdc++.h>
#include <cassert>
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
    return x*y;
  } else {
    return 0;
  }
}

string clean_string(string s)
{
  bool enabled = true;
  string t;
  size_t pos = 0, pos2;
  
  while (true) {
    if (enabled) {
      pos2 = s.find("don't()", pos);
      if (pos2 == string::npos) {
	t += s.substr(pos);
	return t;
      }
      t += s.substr(pos, pos2-pos);
      pos = pos2 + 7;
      enabled = false;
    } else {
      pos2 = s.find("do()", pos);
      if (pos2 == string::npos) {
	return t;
      }
      pos = pos2 + 4;
      enabled = true;
    }
  }
  assert(false);
}

int main()
{
  string s, t;

  while (getline(cin, t)) {
    s += t;
  }

  s = clean_string(s);

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
