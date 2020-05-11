#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int cardpt[256] = {0};
string suits = "SHDC";

int main(void)
{
  cardpt['A'] = 4;
  cardpt['K'] = 3;
  cardpt['Q'] = 2;
  cardpt['J'] = 1;

  string hand[13];
  while (cin >> hand[0]) {
    for (int i = 1; i < 13; i++) {
      cin >> hand[i];
    }

    int dist[256] = {0};
    int pt = 0;
    bool hascard[256][256];
    for (int i = 0; i < 4; i++) {
      fill(hascard[suits[i]], hascard[suits[i]]+256, false);
    }
    for (int i = 0; i < 13; i++) {
      char suit = hand[i][1];
      char rank = hand[i][0];
      dist[suit]++;
      pt += cardpt[rank];
      hascard[suit][rank] = true;
    }

    int stopped = 0;
    for (int i = 0; i < 4; i++) {
      char suit = suits[i];
      if (hascard[suit]['A'] ||
	  (hascard[suit]['K'] && dist[suit] >= 2) ||
	  (hascard[suit]['Q'] && dist[suit] >= 3)) {
	stopped++;
      }

      if (hascard[suit]['K'] && dist[suit] <= 1)
	pt--;
      if (hascard[suit]['Q'] && dist[suit] <= 2)
	pt--;
      if (hascard[suit]['J'] && dist[suit] <= 3)
	pt--;
    }

    if (stopped == 4 && pt >= 16) {
      cout << "BID NO-TRUMP" << endl;
      continue;
    }

    for (int i = 0; i < 4; i++) {
      char suit = suits[i];
      if (dist[suit] == 2) pt++;
      else if (dist[suit] < 2) pt += 2;
    }

    if (pt < 14) {
      cout << "PASS" << endl;
    } else {
      int best = 0;
      for (int i = 0; i < 4; i++) {
	if (best == 0 || dist[best] < dist[suits[i]] ||
	    (dist[best] == dist[suits[i]] && best < suits[i])) {
	  best = suits[i];
	}
      }
      cout << "BID " << (char)(best) << endl;
    }
  }
  
  return 0;
}
