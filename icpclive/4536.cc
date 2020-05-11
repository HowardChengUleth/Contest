#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>

using namespace std;

bool do_case(int case_num)
{
  int n;
  cin >> n;
  if (n == 0) {
    return false;
  }
		
  cout << "Pile " << case_num << endl;

  string cards, moves;
  cin >> cards >> moves;

  deque< vector<int> > piles(n);
  for (int i = 0; i < n; i++) {
    int card = (cards[i] == 'U') ? i+1 : -(i+1);
    piles[i].push_back(card);
  }

  for (int i = 0; i < moves.length(); i++) {
    if (moves[i] == 'R') {
      int j = piles.size()-1;
      for (int k = piles[j].size()-1; k >= 0; k--) {
	piles[j-1].push_back(-piles[j][k]);
      }
      piles.pop_back();
    } else {
      for (int k = piles[0].size()-1; k >= 0; k--) {
	piles[1].push_back(-piles[0][k]);
      }
      piles.pop_front();
    }
  }

  int m;
  cin >> m;
  while (m-- > 0) {
    int q;
    cin >> q;

    int i = n-q;
    cout << "Card " << q << " is a face "
	 << (piles[0][i] > 0 ? "up " : "down ")
	 << abs(piles[0][i]) << "." << endl;
  }
   
  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
