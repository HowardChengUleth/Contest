#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

int main(void)
{
  int T;
  cin >> T;
  cin.ignore(1);
  cin.ignore(1);

  while (T-- > 0) {
    string tree;
    map<string, int> count;
    int total = 0;
    while (getline(cin, tree) && tree != "") {
      count[tree]++;
      total++;
    }

    for (map<string, int>::const_iterator it = count.begin();
	 it != count.end(); ++it) {
      cout << it->first << ' ' << fixed << setprecision(4)
	   << (it->second*100.0/total) << endl;
    }
    
    if (T) {
      cout << endl;
    }
  }
  
  return 0;
}
