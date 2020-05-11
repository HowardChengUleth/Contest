#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

string tolower(string s)
{
  string r = s;
  for (int i = 0; i < s.length(); i++) {
    r[i] = tolower(s[i]);
  }
  return r;
}

bool cmp(pair<long long, string> p1, pair<long long, string> p2)
{
  if (p1.first != p2.first) return p1.first < p2.first;
  return tolower(p1.second) < tolower(p2.second);
}

int main(void)
{
  int n;
  pair<long long, string> info[100];
  
  while (cin >> n) {
    for (int i = 0; i < n; i++) {
      string name;
      cin >> name;
      
      string dummy;
      int x, y, z;
      cin >> dummy >> x >> dummy >> y >> dummy >> z >> dummy;
      info[i] = make_pair(x*60*1000+y*1000+z, name);
    }
    sort(info, info+n, cmp);

    int row = 1;
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
	cout << "Row " << row++ << endl;
      }
      cout << info[i].second << endl;
    }
    cout << endl;
  }
  return 0;
}
