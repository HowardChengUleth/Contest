#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int score(string roll[6], int index[6])
{
  int ans = 0;

  for (int i = 0; i < 6; i++) {
    char c = index[i] + '0';
    for (unsigned int j = 0; j < 9; j += 2) {
      if (roll[i][j] == c) {
	ans += index[i];
      }
    }
  }

  if (ans >= 63) {
    ans += 35;
  }

  return ans;
}

int main(void)
{
  string roll[6];
  int case_num = 1;
  while (cin >> roll[0] && roll[0] != "0-0-0-0-0") {
    for (int i = 1; i < 6; i++) {
      cin >> roll[i];
    }

    int index[6] = {1,2,3,4,5,6};
    int best = 0;
    do {
      best = max(best, score(roll, index));
    } while (next_permutation(index, index+6));
    
    cout << "Case " << case_num++ << ": " << best << endl;
  }
  return 0;
}
