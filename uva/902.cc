#include <iostream>
#include <tr1/unordered_map>
#include <string>

using namespace std;
using namespace std::tr1;

int main(void)
{
  int N;
  string s;

  while (cin >> N >> s) {
    typedef unordered_map<string, int> map;
    map count;
    for (int i = 0; i+N-1 < s.length(); i++) {
      count[s.substr(i, N)]++;
    }
    int best = -1;
    string passwd = "";
    for (map::const_iterator it = count.begin(); it != count.end(); ++it) {
      if (it->second > best) {
	passwd = it->first;
	best = it->second;
      }
    }
    cout << passwd << endl;
  }
  return 0;
}
