#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

// number of ways for (p1,p2) to win, if the current score is (i, j) and
// it is k's turn, and at pos1, pos2
pll memo[22][22][2][10][10];
bool init[22][22][2][10][10];

pll f(int score[2], int turn, int pos[2])
{
  if (score[0] >= 21) {
    return pll(1,0);
  }
  if (score[1] >= 21) {
    return pll(0,1);
  }
  pll &ans = memo[score[0]][score[1]][turn][pos[0]][pos[1]];
  bool &done = init[score[0]][score[1]][turn][pos[0]][pos[1]];
  if (done) {
    return ans;
  }


  ans = pll(0,0);
  for (int s1 = 1; s1 <= 3; s1++) {
    for (int s2 = 1; s2 <= 3; s2++) {
      for (int s3 = 1; s3 <= 3; s3++) {
	int s = s1+s2+s3;
	int npos[2];
	npos[0] = pos[0];
	npos[1] = pos[1];
	npos[turn] = (npos[turn] + s) % 10;

	int nscore[2];
	nscore[0] = score[0];
	nscore[1] = score[1];
	nscore[turn] += npos[turn] + 1;
	
	pll ans2 = f(nscore, 1-turn, npos);
	ans.first += ans2.first;
	ans.second += ans2.second;
      }
    }
  }

  done = true;
  return ans;
}

int main()
{
  int pos[2];
  cin >> pos[0] >> pos[1];
  pos[0]--; pos[1]--;

  int score[2] = {0};
  auto ans = f(score, 0, pos);

  cout << ans.first << ' ' << ans.second << endl;
  cout << max(ans.first, ans.second) << endl;
    
  return 0;
}
