#include<iostream>
#include<map>
#include<queue>
#include<set>

using namespace std;

#define SOLVE true
#define CREATE false

int target[]={
  0,
  1,
  12,
  123,
  1234,
  12345,
  123456,
  1234567,
  12345678,
  123456789
};

int p[]={
  1,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000
};

class state{
public:
  int now, cnt;

  state() {};
  state(int tn, int tc)
  {
    now=tn;
    cnt=tc;
  }
  
  void create(int n, queue<state> &Q, set<int> &S)
  {
    cnt++;

    int tmp = now;

    for (int i=0; i<n; i++) {
      for (int j=i; j<n; j++) {
	int vs = (tmp%p[j+1])/p[i];
	int rem1 = tmp/p[j+1];
	int rem2 = tmp%p[i];

	// cut chunk i to j
	for (int k = 0; k < i; k++) {
	  // paste it at position k.  we only consider moving in one
	  // direction because every move in the other direction is
	  // equivalent to one of these moves
	  int val = rem1*p[j+1] + (rem2/p[k])*p[k+j-i+1] + vs*p[k]+rem2%p[k];
	  if (S.find(val) == S.end()){
	    Q.push(state(val, cnt));
	    S.insert(val);
	  }
	}
      }
    }
  }
};

int bfs(bool flag, int ini, int n, map<int,int> &M)
{
  state now(ini, 0);
  queue<state> Q;
  set<int> S;
  S.insert(ini);
  Q.push(now);
  while (!Q.empty()) {
    now = Q.front();
    Q.pop();
        
    if (flag == CREATE) {
      M[now.now] = now.cnt;
      if (n < now.cnt*4) continue; //change 2 to 4.depend on answer 
    } else if (flag == SOLVE) {
      if (M.find(now.now) != M.end()) {
	return now.cnt + M[now.now];
      }
    }

    now.create(n, Q, S);
  }
  return -1;
}

int main()
{
  map<int,int> M[10];
  int n, tc = 1;
  while (cin >> n && n) {
    if (M[n].size() == 0) {
      bfs(CREATE, target[n], n, M[n]);
    }

    int ini = 0;
    for (int i = 0; i < n; i++) {
      int t;
      cin >> t;
      ini = ini*10 + t;
    }
    cout << "Case "<< tc++ << ": " << bfs(SOLVE, ini, n, M[n]) << endl;
  }
  return 0;
}
