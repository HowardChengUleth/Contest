#include <bits/stdc++.h>

using namespace std;

typedef pair<string,int> psi;
vector<psi> hand;

const string card = "23456789TJQKA";

int card_rank(char c)
{
  return card.find(c);
}

int get_type(const string &hand)
{
  int freq[13] = {0};
  for (auto c : hand) {
    freq[card_rank(c)]++;
  }

  int hi = *max_element(freq, freq+13);
  if (hi == 1) {
    return 0;      // high card
  } else if (hi == 2) {
    if (count(freq, freq+13, hi) == 1) {
      return 1;    // one pair
    } else {
      return 2;    // two pair
    }
  }

  if (hi == 3) {
    if (count(freq, freq+13, 2) == 0) {
      return 3;     // three of a kind
    } else {
      return 4;     // full house
    }
  }

  if (hi == 4) {
    return 5;     // four of a kind
  }

  assert(hi == 5);
  return 6;       // five of a kind
}

bool cmp(psi hand1, psi hand2)
{
  auto s1 = hand1.first, s2 = hand2.first;
  if (get_type(s1) != get_type(s2)) {
    return get_type(s1) < get_type(s2);
  }

  for (int i = 0; i < 5; i++) {
    int r1 = card_rank(s1[i]);
    int r2 = card_rank(s2[i]);
    if (r1 != r2) {
      return r1 < r2;
    }
  }
  assert(false);
}

int main()
{
  string str;
  int bet;

  while (cin >> str >> bet) {
    hand.emplace_back(str, bet);
  }

  sort(begin(hand), end(hand), cmp);

  int ans = 0;
  int rank = 1;
  for (auto [h, b] : hand) {
    ans += rank * b;
    rank++;
  }

  cout << ans << endl;
  return 0;
}
