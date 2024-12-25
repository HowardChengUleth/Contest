#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;


typedef vector<int> Grid;

vector<Grid> lock, key;

bool read_grid()
{
  string line[7];
  Grid grid;
  
  for (int i = 0; i < 7; i++) {
    cin >> line[i];
  }
  if (!cin.good()) {
    return false;
  }

  if (line[0][0] == '#') {
    // lock
    assert(line[6][0] == '.');
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 7; k++) {
	if (line[k][j] == '.') {
	  grid.push_back(k-1);
	  break;
	}
      }
    }
    lock.push_back(grid);
  } else {
    // key
    assert(line[6][0] == '#' && line[0][0] == '.');
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 7; k++) {
	if (line[6-k][j] == '.') {
	  grid.push_back(k-1);
	  break;
	}
      }
    }
    key.push_back(grid);
  }
  return true;
}

bool fit(Grid L, Grid K)
{
  for (int i = 0; i < 5; i++) {
    if (L[i] + 1 + K[i] + 1 > 7) {
      return false;
    }
  }
  return true;
}

int main()
{
  while (read_grid())
    ;

  cout << "locks = " << lock.size() << endl;
  cout << "keys = " << key.size() << endl;

  ll ans = 0;
  for (auto L : lock) {
    for (auto K : key) {
      if (fit(L, K)) {
	ans++;
      }
    }
  }

  cout << ans << endl;
  return 0;
}
