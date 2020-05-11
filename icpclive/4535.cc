#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

void add_word(map<string, int> &dict, const string &w)
{
  int t = dict.size();
  dict[w] = t;
}

int codelen(const vector<string> &dict)
{
  int t = dict.size()-1;
  if (t == 0) return 1;
  int c = 0;
  while (t > 0) {
    t /= 10;
    c++;
  }
  return c;
}

int main(void)
{
  int case_num = 1;
  string digits;

  while (cin >> digits && digits != "0") {
    cout << "Case " << case_num++ << ": ";
    
    vector<string> dict;
    //    map<string, int> dict;
    int s;
    cin >> s;
    while (s-- > 0) {
      string w;
      cin >> w;
      //add_word(dict, w);
      dict.push_back(w);
    }

    string orig;
    bool first = true;
    int si = 0;
    while (si < digits.length()) {
      int di = atoi(digits.substr(si, codelen(dict)).c_str());
      si += codelen(dict);
      if (!first) {
	// add newly decoded character to last prefix
	dict[dict.size()-1] += dict[di][0];
      }
      orig += dict[di];

      // new entry is the current prefix + the next decoded character
      dict.push_back(dict[di]);
      first = false;
    }
    cout << orig << endl;
  }

  return 0;
}
