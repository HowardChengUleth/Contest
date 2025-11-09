#include <bits/stdc++.h>

using namespace std;

// slow simulation only
const int MAX_T = 10000;

struct Event
{
  int t, p;
  void read()
  {
    cin >> t >> p;
  }
};

int main()
{ 
  int M;
  cin >> M;
  
  vector<int> c(M);
  for (auto &x : c) {
    cin >> x;
  }

  int N, E;
  cin >> N >> E;
  vector<int> belt(N+1, -1);       // belt[0] = chef, -1 = empty

  vector<Event> event(E);
  for (int i = 0; i < E; i++) {
    event[i].read();
  }

  int curr_item = 0;
  int curr_event = 0;
  vector<int> bill(N, 0);

  /*
  cout << "Belt:";
  for (auto x : belt) {
    cout << ' ' << x;
  }
  cout << endl;
  cout << "=============" << endl;
  */
  
  // don't even bother with exiting early if we run out of events...
  for (int t = 0; t <= MAX_T; t++) {
    // chef places dish
    if (belt[0] == -1) {
      belt[0] = curr_item;
      curr_item = (curr_item + 1) % M;
    }

    // take the dishes
    while (curr_event < E && event[curr_event].t == t) {
      int p = event[curr_event].p;
      assert(belt[p] != -1);
      bill[p-1] += c[belt[p]];
      /*
	cout << "Time " << t << ", person " << p << " got dish " << belt[p] << endl;
      */
      belt[p] = -1;
      curr_event++;
    }

    // move the belt
    rotate(begin(belt), begin(belt)+N, end(belt)); 
    /*
    cout << "Belt:";
    for (auto x : belt) {
      cout << ' ' << x;
    }
    cout << endl;
    cout << "=============" << endl;
    */
 }

  for (auto b : bill) {
    cout << b << endl;
  }
  
  return 0;
}
