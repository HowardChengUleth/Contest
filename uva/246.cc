#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

typedef vector<vector<int> > vvi;

bool check(vvi &pile, int pile_index, int a, int b, int c)
{
  vector<int> &p = pile[pile_index], &card = pile[7];
  int sum = p[a] + p[b] + p[c];
  if (sum == 10 || sum == 20 || sum == 30) {
    int A = p[a], B = p[b], C = p[c];

    // erase backwards
    p.erase(p.begin() + c);
    p.erase(p.begin() + b);
    p.erase(p.begin() + a);

    card.push_back(A);
    card.push_back(B);
    card.push_back(C);

    return true;
  }

  return false;
}

void check_pile(vvi &pile, int pile_index)
{
  int size = pile[pile_index].size();
  if (size < 3) return;

  // short circuit
  if (check(pile, pile_index, 0, 1, size-1) ||
      check(pile, pile_index, 0, size-2, size-1) ||
      check(pile, pile_index, size-3, size-2, size-1)) {
    check_pile(pile, pile_index);
  }
}

void print(const vvi &pile)
{
  for (int i = 0; i < 8; i++) {
    cout << i << ":";
    for (int j = 0; j < pile[i].size(); j++) {
      cout << ' ' << pile[i][j];
    }
    cout << endl;
  }
  cout << "====================================" << endl;
}

bool solve()
{
  vvi pile(8);

  // fake card deck as the 8th pile (for the set)
  vector<int> &card = pile[7];

  int c;
  cin >> c;
  if (c == 0) return false;

  card.push_back(c);
  for (int i = 1; i < 52; i++) {
    cin >> c;
    card.push_back(c);
  }

  int dealt = 0;
  set<vvi> seen;

  // let's deal out 1 card to each pile initially
  for (int i = 0; i < 7; i++) {
    pile[i].push_back(card[0]);
    card.erase(card.begin());
    dealt++;
  }

  int pile_index = -1;
  while (true) {
    do {
      pile_index = (pile_index + 1) % 7;
    } while (pile[pile_index].size() == 0);
    
    if (card.size() == 0) {
      cout << "Loss";
      break;
    }
    pile[pile_index].push_back(card[0]);
    card.erase(card.begin());
    dealt++;

    /*
    cout << "Dealt = " << dealt << endl;
    print(pile);
    */
    check_pile(pile, pile_index);

    bool win = true;
    for (int i = 0; i < 7; i++) {
      win &= pile[i].size() == 0;
    }
    if (win) {
      cout << "Win ";
      break;
    }

    if (seen.count(pile) > 0) {
      cout << "Draw";
      break;
    }
    seen.insert(pile);
  }

  cout << ": " << dealt << endl;
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
