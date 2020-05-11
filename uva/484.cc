#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct output {
  int n, freq;
};

int main(void)
{
  map<int, pair<int,int> > freq;
  int n, i = 0;

  while (cin >> n) {
    if (freq.find(n) == freq.end()) {
      freq[n] = make_pair<int,int>(i++, 1);
    } else {
      freq[n].second++;
    }
  }

  vector<output> v(i);
  for (map<int, pair<int,int> >::const_iterator it = freq.begin();
       it != freq.end(); ++it) {
    v[it->second.first].n = it->first;
    v[it->second.first].freq = it->second.second;
  }
  for (int k = 0; k < i; k++) {
    cout << v[k].n << " " << v[k].freq << endl;
  }
  
  
  return 0;
}
