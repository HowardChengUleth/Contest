#include <iostream>
#include <string>


using namespace std;

int digval(char c)
{
  return (isdigit(c)) ? c - '0' : c - 'a' + 10;
}

int isdig(char c, int base)
{
  if (!isdigit(c) && !('a' <= c && c <= 'f')) {
    return false;
  }
  return digval(c) < base;
}

bool convert(string s, int &val, bool last = false)
{
  if (s.length() == 0) {
    return false;
  }

  // decimal
  if (s.find('#') == string::npos) {
    val = 0;
    for (int i = 0; i < s.length(); i++) {
      if (!isdig(s[i], 10)) {
	return false;
      }
      val = val * 10 + digval(s[i]);
      if (!last && val > 100) return false;
    }
    return true;
  }

  // let's look for last 2 '#'
  if (s[s.length()-1] != '#') {
    return false;
  }
  s.erase(s.length()-1);
  string::size_type pos = s.rfind('#');
  if (pos == string::npos) {
    return false;
  }

  // convert base recursively
  string base_part = s.substr(0, pos);
  s.erase(0, pos+1);
  if (s.length() == 0) {
    return false;
  }
  
  int base;
  if (!convert(base_part, base) || !(2 <= base && base <= 16)) {
    return false;
  }

  val = 0;
  for (int i = 0; i < s.length(); i++) {
    if (!isdig(s[i], base)) {
      return false;
    }
    val = val * base + digval(s[i]);
    if (!last && val > 100) return false;
  }
  
  return true;
}

void solve()
{
  string num;
  cin >> num;

  int val;
  if (convert(num, val, true)) {
    cout << "yes" << endl;
  } else {
    cout << "no" << endl;
  }
}

int main()
{
  int n;
  cin >> n;
  while (n--) {
    solve();
  }
  return 0;
}
