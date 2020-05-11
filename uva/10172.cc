#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void do_case()
{
  int N, S, Q;
  cin >> N >> S >> Q;

  queue<int> platB[100];
  int cargo = 0;
  for (int i = 0; i < N; i++) {
    int num;
    cin >> num;
    cargo += num;
    while (num--) {
      int x;
      cin >> x;
      platB[i].push(x-1);
    }
  }

  //  cout << "cargo = " << cargo << endl;
  
  stack<int> carrier;
  int index = 0;
  int time = 0;
  while (cargo > 0) {
    //    cout << "At station " << index << ":" << endl;
    
    // unload the carrier
    while (!carrier.empty()) {
      int x = carrier.top();
      if (x == index) {
	// put in platform A
	carrier.pop();
	time += 1;
	cargo--;

	//	cout << "  Unloading " << x << " to A" << endl;
      } else if (platB[index].size() < Q) {
	// put in platform B
	platB[index].push(x);
	carrier.pop();
	time += 1;

	//	cout << "  Unloading " << x << " to B" << endl;
      } else {
	// can't continue
	break;
      }
    }

    // all done
    if (cargo == 0) continue;
    
    // load cargo
    while (carrier.size() < S && !platB[index].empty()) {
      carrier.push(platB[index].front());
      //      cout << "  Loading " << carrier.top() << endl;
      platB[index].pop();
      time += 1;
    }

    // move
    if (++index >= N) index = 0;
    time += 2;
  }

  cout << time << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    do_case();
  }
  return 0;
}
