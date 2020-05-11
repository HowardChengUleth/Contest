#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

//
// there aren't any tricks here.  Just read one line at a time, accumulat
// the counts and look for the max.  Then look for all characters with the
// max count.  I'm using STL algorithms for fun here...
//

using namespace std;

void solve(const string &s)
{
  int count[256];

  fill(count, count+256, 0);
  for (unsigned int i = 0; i < s.length(); i++) {
    count[tolower(s[i])]++;
  }
  int *m = max_element(count+'a', count+'z'+1);
  for (int i = 'a'; i <= 'z'; i++) {
    if (count[i] == *m) {
      cout << (char)(i);
    }
  }
  cout << endl;
}

int main(void)
{
  int C;
  cin >> C;
  cin.ignore(1);
  while (C-- > 0) {
    string s;
    getline(cin, s);
    solve(s);
  }
  return 0;
}
