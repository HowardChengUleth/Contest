#include <bits/stdc++.h>

using namespace std;

struct Die
{
  int curr;
  int num_roll;
  
  Die() : curr(1), num_roll(0) { };

  int roll() {
    int ans = curr;
    curr++;
    if (curr == 101) curr = 1;
    num_roll++;
    return ans;
  }
};

int main()
{
  Die d;

  int pos[2];
  cin >> pos[0] >> pos[1];
  pos[0]--; pos[1]--;

  int score[2] = {0};

  int curr = 0;
  while (score[0] < 1000 && score[1] < 1000) {
    int steps = 0;
    for (int i = 0; i < 3; i++) {
      steps += d.roll();
    }
    pos[curr] = (pos[curr] + steps) % 10;
    score[curr] += pos[curr]+1;
    curr = 1-curr;
  }

  cout << score[0] << ' ' << score[1] << ' ' << d.num_roll << endl;
  cout << score[curr] * d.num_roll << endl;
  
  return 0;
}
