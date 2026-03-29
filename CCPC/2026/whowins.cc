// basically just work through the rules
//
// To figure out the value of a hand, just add things up.  Only trick is
// how to deal with the aces.
//
// Count the aces as 1, and if adding 10 does not make you go over 21, convert
// an ace to 11.  You can convert at most 1 ace.
#include <bits/stdc++.h>

using namespace std;

int score(int n, string hand[])
{
  int ans = 0;
  int num_ace = 0;
  for (int i = 0; i < n; i++) {
    if (isdigit(hand[i][0])) {
      int val = hand[i][0] - '0';
      if (hand[i] == "10") {
	val = 10;
      }
      ans += val;
    } else if (hand[i] == "J" || hand[i] == "Q" || hand[i] == "K") {
      ans += 10;
    } else {
      assert(hand[i] == "A");
      ans++;
      num_ace++;
    }
  }

  while (num_ace > 0 && ans + 10 <= 21) {
    ans += 10;
    num_ace--;
  }

  return ans;
}

int main()
{
  string dealer[3], player[3];
  int d, p;

  cin >> d;
  for (int i = 0; i < d; i++) {
    cin >> dealer[i];
  }
  cin >> p;
  for (int i = 0; i < p; i++) {
    cin >> player[i];
  }

  int dscore = score(d, dealer);
  int pscore = score(p, player);

  if (dscore > 21 && pscore > 21) {
    cout << "Push" << endl;
  } else if (pscore > 21) {
    cout << "Dealer" << endl;
  } else if (dscore > 21) {
    cout << "Player" << endl;
  } else if (dscore > pscore) {
    cout << "Dealer" << endl;
  } else if (pscore > dscore) {
    cout << "Player" << endl;
  } else {
    assert(dscore == pscore);
    cout << "Push" << endl;
  }

  return 0;
}
