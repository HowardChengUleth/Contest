#include <bits/stdc++.h>

using namespace std;

// (price, number of shares)
typedef pair<int,int> pii;

void solve()
{
  int n;
  cin >> n;

  priority_queue<pii> bid;
  priority_queue<pii, vector<pii>, greater<pii>> ask;
  
  int price = -1;
  for (int i = 0; i < n; i++) {
    string type, shares, at;
    int x, y;

    cin >> type >> x >> shares >> at >> y;

    if (type == "buy") {
      bid.emplace(y, x);
    } else {
      ask.emplace(y, x);
    }

    while (!bid.empty() && !ask.empty() &&
	   bid.top().first >= ask.top().first) {
      pii bidtop = bid.top();
      pii asktop = ask.top();
      bid.pop();
      ask.pop();

      int shares = min(bidtop.second, asktop.second);
      bidtop.second -= shares;
      asktop.second -= shares;
      price = asktop.first;
      if (bidtop.second) {
	bid.push(bidtop);
      }
      if (asktop.second) {
	ask.push(asktop);
      }
    }

    if (ask.empty()) {
      cout << "-";
    } else {
      cout << ask.top().first;
    }
    cout << ' ';

    if (bid.empty()) {
      cout << "-";
    } else {
      cout << bid.top().first;
    }
    cout << ' ';

    if (price < 0) {
      cout << "-";
    } else {
      cout << price;
    }
    cout << endl;
    
  }
}

int main()
{
  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    solve();
  }
  
  return 0;
}
