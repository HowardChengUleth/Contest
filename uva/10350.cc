#include <iostream>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

bool solve()
{
  string name;
  if (!(cin >> name)) {
    return false;
  }
  cout << name << endl;

  int n, m;
  cin >> n >> m;

  int times[2][15];

  fill(times[0], times[0]+m, 0);
  int curr = 0;
  
  for (int i = 0; i < n-1; i++) {
    int next = 1-curr;
    fill(times[next], times[next]+m, INT_MAX);
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
	int t;
	cin >> t;
	
	times[next][k] = min(times[next][k], times[curr][j] + t);
      }
    }
    curr = next;
  }

  cout << *min_element(times[curr], times[curr]+m) + (n-1)*2 << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
