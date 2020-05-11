#include <bits/stdc++.h>

using namespace std;

set<string> S;

string core(const string &s)
{
  string ans;
  for (auto c : s) {
    if (!isalpha(c)) continue;
    ans += tolower(c);
  }
  return ans;
}

bool insert(const string &s1, const string &s2)
{
  if (s1.length()+1 != s2.length()) return false;
  for (int i = 0; i < s2.length(); i++) {
    string s = s2;
    s.erase(i, 1);
    if (s1 == s) return true;
  }
  return false;
}

bool replace(const string &s1, const string &s2)
{
  if (s1.length() != s2.length()) return false;
  int c = 0;
  for (int i = 0; i < s1.length(); i++) {
    c += s1[i] != s2[i];
  }
  return c == 1;
}

bool transpose(const string &s1, const string &s2)
{
  if (s1.length() != s2.length()) return false;
  for (int i = 0; i < s1.length()-1; i++) {
    string s = s1;
    swap(s[i], s[i+1]);
    if (s == s2) return true;
  }
  return false;
}

bool printlist(const string &w)
{
  bool res = false;
  for (auto x : S) {
    if (x == w) continue;
    if (insert(w, x) || insert(x, w) || replace(x, w) || transpose(x, w)) {
      if (!res) {
	cout << w << ":";
      }
      cout << " " << x;
      res = true;
    }
  }
  if (res)
    cout << endl;
  return res;
}

int main()
{
  string s;

  while (cin >> s) {
    s = core(s);
    if (s != "") {
      S.insert(s);
    }
  }

  bool printed = false;
  for (auto w : S) {
    printed |= (printlist(w));
  }
  if (!printed) {
    cout << "***" << endl;
  }
  
  return 0;
}
