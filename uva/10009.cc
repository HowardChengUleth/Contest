/* @JUDGE_ID: 1102NT 10009 C++ "" */

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

string find_path(map<string,string> &parent, string src)
{
  string s;
  
  s = src[0];
  while (src != "Rome") {
    src = parent[src];
    s += src[0];
  }
  return s;
}

int main(void)
{
  int cases;
  int m, n;

  cin >> cases;
  while (cases-- > 0) {
    cin >> m >> n;
    map<string,string> parent;
    string s1, s2;
    while (m-- > 0) {
      cin >> s1 >> s2;
      parent[s2] = s1;
    }
    while (n-- > 0) {
      cin >> s1 >> s2;
      string p1 = find_path(parent, s1);
      string p2 = find_path(parent, s2);
      char c;

      reverse(p2.begin(), p2.end());
      while (p1.length() > 0 && p2.length() > 0 && 
	     p1[p1.length()-1] == p2[0]) {
	c = p2[0];
	p1.erase(p1.length()-1,1);
	p2.erase(0, 1);
      }
      cout << p1 << c << p2 << endl;
    }    

    if (cases) {
      cout << endl;
    }
  }

  return 0;
}

