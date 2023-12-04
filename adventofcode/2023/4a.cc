#include <bits/stdc++.h>

using namespace std;

int points(string card)
{
  auto colon = card.find(':');
  auto bar = card.find('|');
  string win = card.substr(colon+1, bar-colon+1);
  string ticket = card.substr(bar+1);
  istringstream wins(win), tickets(ticket);

  set<int> win_num;
  int x;
  while (wins >> x) {
    win_num.insert(x);
  }

  int win_count = 0;
  while (tickets >> x) {
    if (win_num.count(x)) {
      win_count++;
    }
  }

  if (win_count) {
    return (1 << (win_count-1));
  } else {
    return 0;
  }

}

int main()
{
  string card;
  int ans = 0;
  while (getline(cin, card)) {
    ans += points(card);
  }
  
  cout << ans << endl;
  return 0;
}
