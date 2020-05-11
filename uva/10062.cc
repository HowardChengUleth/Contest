#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Stat {
  char val;
  int count;

  bool operator<(const Stat &s) const {
    return (count < s.count ||
	    (count == s.count && val > s.val));
  }
};

int main(void)
{
  string s;
  int freq[256];
  Stat stat[256];
  int num_stat;
  bool first = true;

  while (getline(cin, s)) {
    if (!first) {
      cout << endl;
    }
    first = false;

    fill(freq, freq+256, 0);
    for (unsigned int i = 0; i < s.length(); i++) {
      freq[s[i]]++;
    }
    num_stat = 0;
    for (int i = 0; i < 256; i++) {
      if (freq[i]) {
	stat[num_stat].val = i;
	stat[num_stat++].count = freq[i];
      }
    }
    sort(stat, stat+num_stat);

    for (int i = 0; i < num_stat; i++) {
      cout << (int)stat[i].val << " " << stat[i].count << endl;
    }
  }
  return 0;
}
