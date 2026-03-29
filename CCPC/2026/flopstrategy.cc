//
// just do it...carefully
//

#include <bits/stdc++.h>

using namespace std;

string order[4];
queue<int> deck;

set<int> hand[4];
int score[4];
bool done[4];
int curr = 0;

int hand_size()
{
  return hand[curr].size();
}

void hit()
{
  int card = deck.front();
  deck.pop();

  if (hand[curr].count(card) > 0) {
    // already has it
    if (hand[curr].count(-1) > 0) {
      hand[curr].erase(-1);
    } else {
      // busted
      done[curr] = true;
    }
  } else {
    hand[curr].insert(card);
  }
}

int value()
{
  int ans = 0;
  for (auto p : hand[curr]) {
    if (p >= 0) {
      ans += p;
    }
  }
  return ans;
}

void bank()
{
  score[curr] = value();
  done[curr] = true;
}

void alice()
{
  int total = hand_size();
  if (total < 3 || hand[curr].count(-1)) {
    hit();
  } else {
    bank();
  }
}

void bob()
{
  int total = hand_size();
  if (total < 5 || hand[curr].count(-1)) {
    hit();
  } else {
    bank();
  }
}

void charlie()
{
  if (value() < 20 || hand[curr].count(-1)) {
    hit();
  } else {
    bank();
  }
}

void david()
{
  if (value() < 30 || hand[curr].count(-1)) {
    hit();
  } else {
    bank();
  }
}

int main()
{
  for (int i = 0; i < 4; i++) {
    cin >> order[i];
  }

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int card;
    cin >> card;
    deck.push(card);
  }

  while (!deck.empty()) {
    switch (order[curr][0]) {
    case 'A':
      alice();
      break;
    case 'B':
      bob();
      break;
    case 'C':
      charlie();
      break;
    case 'D':
      david();
      break;
    }

    // move to next player
    int counter = 0;
    curr = (curr + 1) % 4;
    while (done[curr]) {
      if (counter > 4) break;
      curr = (curr + 1) % 4;
      counter++;
    }

    if (counter > 4) 
      break;
  }
  for (curr = 0; curr < 4; curr++) {
    if (!done[curr]) {
      bank();
    }
  }
  
  int winner = max_element(score, score+4) - score;
  cout << order[winner] << endl;
  
  return 0;
}
