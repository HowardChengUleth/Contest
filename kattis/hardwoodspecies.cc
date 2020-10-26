#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

int main(void)
{
  string tree;
  map<string, int> count;
  int total = 0;
  while (getline(cin, tree)) {
    count[tree]++;
    total++;
  }

  for (auto p : count) {
    cout << p.first << ' ' << fixed << setprecision(4)
         << (p.second*100.0/total) << endl;
  }
  
  return 0;
}
