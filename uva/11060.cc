#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(void)
{
  int n, m;
  int id = 1;
  while (cin >> n) {
    string names[100];
    bool after[100][100];
    
    for (int i = 0; i < n; i++) {
      cin >> names[i];
      fill(after[i], after[i]+n, false);
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
      string name1, name2;
      cin >> name1 >> name2;
      after[find(names, names+n, name2) - names]
	[find(names, names+n, name1) - names] = true;
    }

    cout << "Case #" << id++
	 << ": Dilbert should drink beverages in this order:";
    bool used[100] = {false};
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
	if (used[i]) continue;
	if (find(after[i], after[i]+n, true) == after[i]+n) {
	  cout << ' ' << names[i];
	  used[i] = true;
	  for (int r = 0; r < n; r++) {
	    after[r][i] = false;
	  }
	  break;
	}
      }
    }
    cout << '.' << endl;
    cout << endl;
  }
  return 0;
}

