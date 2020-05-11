#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector< vector<int> > configs;

void gen_pos(vector<int> &pos, int i = 0)
{
  if (i == 8) {
    configs.push_back(pos);
    return;
  }
  
  for (int j = 1; j <= 8; j++) {
    bool good = true;
    for (int k = 0; k < i && good; k++) {
      good &= pos[k] != j;
      good &= abs(pos[k]-j) != i-k;
    }

    if (good) {
      pos[i] = j;
      gen_pos(pos, i+1);
    }
  }
}

int main(void)
{
  vector<int> pos(8);
  gen_pos(pos);
  int id = 1;
  
  while (cin >> pos[0]) {
    for (int i = 1; i < 8; i++) {
      cin >> pos[i];
    }

    int best = 8;
    for (int i = 0; i < configs.size(); i++) {
      int count = 0;
      for (int j = 0; j < 8; j++) {
	if (configs[i][j] != pos[j]) {
	  count++;
	}
      }
      best = min(best, count);
    }
    cout << "Case " << id++ << ": " << best << endl;
  }
  return 0;
}
