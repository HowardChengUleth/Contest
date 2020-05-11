#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

bool nondigit(char c)
{
  return !isdigit(c);
}

int main(void)
{
  int n, m;
  string standard[100], team[100];
  int run = 1;

  while (cin >> n && n > 0) {
    cout << "Run #" << run++ << ": ";
    cin.ignore();
    for (int i = 0; i < n; i++) {
      getline(cin, standard[i]);
    }
    cin >> m;
    cin.ignore();
    for (int i = 0; i < m; i++) {
      getline(cin, team[i]);
    }

    if (n == m) {
      int i;
      for (i = 0; i < n && standard[i] == team[i]; i++)
	;
      if (i >= n) { 
	cout << "Accepted" << endl;
	continue;
      }
    }
    
    for (int i = 1; i < n; i++) {
      standard[0] += standard[i];
    }
    for (int i = 1; i < m; i++) {
      team[0] += team[i];
    }
    int s1 = remove_if(standard[0].begin(), standard[0].end(), nondigit) -
      standard[0].begin();
    int s2 = remove_if(team[0].begin(), team[0].end(), nondigit) - 
      team[0].begin();
    standard[0].resize(s1);
    team[0].resize(s2);
    if (standard[0] == team[0]) {
      cout << "Presentation Error" << endl;
    } else {
      cout << "Wrong Answer" << endl;
    }
  }

  return 0;
}
