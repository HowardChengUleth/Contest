#include <bits/stdc++.h>

using namespace std;

int total[1000] = {0};

void points(string card)
{
  istringstream cards(card);
  string dummy;
  int id;
  cards >> dummy >> id;
  total[id]++;
  
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

  for (int i = 0; i < win_count; i++) {
    total[id+1+i] += total[id];
  }
}

int main()
{
  string card;
  while (getline(cin, card)) {
    points(card);
  }

  int ans = accumulate(total, total+1000, 0);
  cout << ans << endl;
  return 0;
}
