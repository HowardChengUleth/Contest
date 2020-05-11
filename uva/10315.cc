#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int rank(const string &card)
{
  const string ranking = "23456789TJQKA";
  return ranking.find(card[0]);
}

bool cmp(const string &c1, const string &c2)
{
  return rank(c1) < rank(c2);
}

enum HandType {
  HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH,
  FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH
};

class Hand
{
private:
  string card[5];
  HandType type;
  int freq[13];

  int highest_rank() const
  {
    int ans = rank(card[0]);
    for (int i = 1; i < 5; i++) {
      ans = max(rank(card[i]), ans);
    }
    return ans;
  }

  void comp_freq()
  {
    fill(freq, freq+13, 0);
    for (int i = 0; i < 5; i++) {
      freq[rank(card[i])]++;
    }
  }

  bool is_pair() const
  {
    return find(freq, freq+13, 2) != freq+13;
  }

  bool is_two_pairs() const
  {
    if (!is_pair()) return false;
    const int *pos1 = find(freq, freq+13, 2);
    return find(pos1+1, freq+13, 2) != freq+13;
  }

  bool is_three_of_a_kind() const
  {
    return find(freq, freq+13, 3) != freq+13;
  }

  bool is_straight() const
  {
    for (int i = 0; i < 13; i++) {
      int found = 0;
      for (int j = 0; j < 5 && i+j < 13; j++) {
	if (freq[i+j]) {
	  found++;
	}
      }
      if (found == 5) {
	return true;
      }
    }
    return false;
  }

  bool is_flush() const
  {
    for (int i = 0; i < 5; i++) {
      if (card[i][1] != card[0][1]) {
	return false;
      }
    }
    return true;
  }

  bool is_full_house() const
  {
    return is_pair() && is_three_of_a_kind();
  }

  bool is_four_of_a_kind() const
  {
    return find(freq, freq+13, 4) != freq+13;
  }

  bool is_straight_flush() const
  {
    return is_straight() && is_flush();
  }

  void get_type()
  {
    if (is_straight_flush()) {
      type = STRAIGHT_FLUSH;
    } else if (is_four_of_a_kind()) {
      type = FOUR_OF_A_KIND;
    } else if (is_full_house()) {
      type = FULL_HOUSE;
    } else if (is_flush()) {
      type = FLUSH;
    } else if (is_straight()) {
      type = STRAIGHT;
    } else if (is_three_of_a_kind()) {
      type = THREE_OF_A_KIND;
    } else if (is_two_pairs()) {
      type = TWO_PAIRS;
    } else if (is_pair()) {
      type = PAIR;
    } else {
      type = HIGH_CARD;
    }
  }

  bool high_card_rule(const Hand &h) const
  {
    for (int i = 4; i >= 0; i--) {
      if (rank(card[i]) != rank(h.card[i])) {
	return rank(card[i]) < rank(h.card[i]);
      }
    }
    return false;
  }

  bool lt_break_ties(const Hand &h) const
  {
    switch (type) {
    case STRAIGHT_FLUSH:
    case STRAIGHT:
      return rank(card[4]) < rank(h.card[4]);
    case FOUR_OF_A_KIND:
      return (find(freq, freq+13, 4)-freq) < 
	(find(h.freq, h.freq+13, 4)-h.freq);
    case FULL_HOUSE:
    case THREE_OF_A_KIND:
      return (find(freq, freq+13, 3)-freq) < 
	(find(h.freq, h.freq+13, 3)-h.freq);
    case TWO_PAIRS:
      {
	const int r11 = find(freq, freq+13, 2) - freq,
	  r12 = find(freq+r11+1, freq+13, 2) - freq,
	  r21 = find(h.freq, h.freq+13, 2) - h.freq,
	  r22 = find(h.freq+r21+1, h.freq+13, 2) - h.freq;
	if (r12 != r22) {
	  return r12 < r22;
	} else if (r11 != r21) {
	  return r11 < r21;
	} else {
	  return high_card_rule(h);
	}
      }
    case PAIR:
      {
	int r1 = find(freq, freq+13, 2) - freq;
	int r2 = find(h.freq, h.freq+13, 2) - h.freq;
	if (r1 != r2) {
	  return r1 < r2;
	} 
      }
      // FALLTHROUGH!!!
    case FLUSH:
    case HIGH_CARD:
      return high_card_rule(h);


    }
    return false;
  }

public:
  Hand(string in[5])
  {
    sort(in, in+5, cmp);
    for (int i = 0; i < 5; i++) {
      card[i] = in[i];
    }
    comp_freq();
    get_type();
  }

  bool operator<(const Hand &h) const
  {
    if (type != h.type) return type < h.type;
    return lt_break_ties(h);
  }
};

bool do_case(void)
{
  string b[5], w[5];

  for (int i = 0; i < 5; i++) {
    if (!(cin >> b[i])) {
      return false;
    }
  }
  for (int i = 0; i < 5; i++) {
    cin >> w[i];
  }

  Hand black(b), white(w);

  if (white < black) {
    cout << "Black wins." << endl;
  } else if (black < white) {
    cout << "White wins." << endl;
  } else {
    cout << "Tie." << endl;
  }

  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
  

