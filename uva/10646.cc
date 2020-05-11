#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int val(const string &card)
{
  if (isdigit(card[0])) {
    return card[0] - '0';
  } else {
    return 10;
  }
}

void solve()
{
  string deck[52];
  for (int i = 0; i < 52; i++) {
    cin >> deck[51-i];
  }

  int Y = 0;
  int pile_i = 25;

  for (int i = 0; i < 3; i++) {
    int X = val(deck[pile_i]);
    Y += X;
    pile_i += 10-X+1;
  }

  if (pile_i <= 52-Y) {
    cout << deck[52-Y] << endl;
  } else {
    Y -= 52-pile_i;
    cout << deck[25-Y] << endl;
  }
  
}

int main(void)
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
