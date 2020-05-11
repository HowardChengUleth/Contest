#include <iostream>
#include <algorithm>

using namespace std;

bool beat(int hand[3], int yours[3])
{
  int count = 0;
  for (int i = 0; i < 3; i++) {
    count += hand[i] > yours[i];
  }
  return count >= 2;
}

bool solve()
{
  int mine[3], yours[3];
  bool used[53] = {false};
  
  for (int i = 0; i < 3; i++) {
    cin >> yours[i];
    used[yours[i]] = true;
  }
  for (int i = 0; i < 2; i++) {
    cin >> mine[i];
    used[mine[i]] = true;
  }
  if (!yours[0]) return false;

  for (int c = 1; c <= 52; c++) {
    if (used[c]) continue;

    int hand[3];
    copy(mine, mine+2, hand);
    hand[2] = c;
    sort(hand, hand+3);

    bool good = true;
    do {
      good &= beat(hand, yours);
    } while (good && next_permutation(hand, hand+3));
    if (good) {
      cout << c << endl;
      return true;
    }
  }
  
  cout << -1 << endl;
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
