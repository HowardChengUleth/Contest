#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main(void)
{
  int n;
  int case_num = 1;

  while (cin >> n && n > 0) {
    map<string,int> currency;
    string curr;
    for (int i = 0; i < n; i++) {
      cin >> curr;
      currency[curr] = i;
    }

    double table[30][30];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	table[i][j] = 0;
      }
      table[i][i] = 1;
    }

    int m;
    cin >> m;
    while (m-- > 0) {
      string c1, c2;
      double rate;
      cin >> c1 >> rate >> c2;
      table[currency[c1]][currency[c2]] = rate;
    }
    
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	  table[i][j] = max(table[i][j], table[i][k]*table[k][j]);
	}
      }
    }

    bool found = false;
    for (int i = 0; i < n && !found; i++) {
      found |= (table[i][i] > 1.0);
    }

    cout << "Case " << case_num++ << ": "
	 << (found ? "Yes" : "No") << endl;


  }

  return 0;
}
