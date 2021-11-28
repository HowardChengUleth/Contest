#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main()
{
  int d, u;
  cin >> d >> u;
  
  priority_queue<int,vector<int>,greater<int>> avail;
  priority_queue<pii,vector<pii>,greater<pii>> retire;

  for (int i = 1; i <= 200000; i++) {
    avail.push(i);
  }

  for (int i = 1; i <= u; i++) {
    while (!retire.empty() && retire.top().first <= i) {
      auto p = retire.top();
      avail.push(p.second);
      retire.pop();
    }
	
    char ch;
    cin >> ch;
    if (ch == 'a') {
      cout << avail.top() << endl;
      avail.pop();
    } else {
      int item;
      cin >> item;
      retire.emplace(i+d, item);
    }
  }
  
  return 0;
}
