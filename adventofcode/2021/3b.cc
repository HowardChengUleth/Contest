#include <bits/stdc++.h>

using namespace std;

struct Cmp
{
  Cmp(int p)
    : pos(p)
  {
  }

  bool operator()(const string &s1, const string &s2) const {
    return s1[pos] < s2[pos];
  }
  
  int pos;
};

int main()
{
  vector<string> bits;
  string s;
  while (cin >> s) {
    bits.push_back(s);
  }
  int n = bits[0].length();
  
  // find oxygen
  int lo = 0, hi = bits.size();
  int pos = 0;
  while (hi - lo > 1) {
    sort(begin(bits)+lo, begin(bits)+hi, Cmp(pos));
    int ind1 = upper_bound(begin(bits)+lo, begin(bits)+hi,
			   string(n, '0'), Cmp(pos)) - begin(bits);
    int count0 = ind1 - lo;
    int count1 = hi - ind1;
    if (count0 > count1) {
      hi = ind1;
    } else {
      lo = ind1;
    }
    pos++;
  }
  bitset<12> oxygen(bits[lo]);

  // find CO2
  lo = 0, hi = bits.size();
  pos = 0;
  while (hi - lo > 1) {
    sort(begin(bits)+lo, begin(bits)+hi, Cmp(pos));
    int ind1 = upper_bound(begin(bits)+lo, begin(bits)+hi,
			   string(n, '0'), Cmp(pos)) - begin(bits);
    int count0 = ind1 - lo;
    int count1 = hi - ind1;
    if (count0 <= count1) {
      hi = ind1;
    } else {
      lo = ind1;
    }
    pos++;
  }
  bitset<12> CO2(bits[lo]);
  

  cout << oxygen.to_ullong() * CO2.to_ullong() << endl;

  
  return 0;
}
