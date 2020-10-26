// canonical coin systems
// https://open.kattis.com/problems/canonical
#include <bits/stdc++.h>
using namespace std;

const int NN = 2000000;
int n[NN];
int g[NN];
vector<int> coins;

int min_coins(int v) {

   int best = -1;
   for (int i = 0; i < coins.size(); i++) {
      int index = v - coins[i];
      if (index < 0) {
	 continue;
      }
      if (best == -1) {
	 best = n[index]+1;
      } else {
	 best = min(best, n[index]+1);
      }
   }

   if (best == -1) {
      exit(0);
   }
   
   return best;   
}

int greedy(int v) {
   int val = v;
   int c = 0;
   for (int i = coins.size() - 1; i >= 0; i--) {
      if (val < v) {
	 c += g[val];
	 break;
      }      
      if (val >= coins[i]) {
	 c += val / coins[i];
	 val = val % coins[i];
      }
   }
   return c;
}

int main() {

   n[0] = 0;
   n[1] = 1;
   g[0] = 0;
   g[1] = 1;

   int num;
   cin >> num;
   for (int i = 0; i < num; i++) {
      int temp; cin >> temp;
      coins.push_back(temp);
   }
   sort(coins.begin(), coins.end());

   string ans = "canonical";
   for (int i = 2; i < (coins[num-1] + coins[num-2]); i++) {
      int mc = min_coins(i);
      int mc_greedy = greedy(i);
      n[i] = mc;
      g[i] = mc_greedy;
      if (mc != mc_greedy) {
	 ans = "non-canonical";
	 break;
      }
   }   
   cout << ans << endl;

   return 0;
}
