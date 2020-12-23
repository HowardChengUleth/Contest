#include <bits/stdc++.h>

using namespace std;

//const int input[] = {3,8,9,1,2,5,4,6,7};

const int input[] = {7,1,6,8,9,2,5,4,3};

vector<int> cups(input, input+9);

bool removed[1000001] = { false };

void step(int &head, vector<int> &next, int maxelem)
{
  int skip[5] = {head};
  for (int i = 0; i < 4; i++) {
    skip[i+1] = next[skip[i]];
  }

  next[head] = skip[4];
  for (int i = 1; i <= 3; i++) {
    removed[skip[i]] = true;
  }
  
  int dest = (head == 1) ? maxelem : head - 1;
  while (removed[dest]) {
    if (--dest <= 0) {
      dest = maxelem;
    }
  }

  for (int i = 1; i <= 3; i++) {
    removed[skip[i]] = false;
  }

 
  int link = next[dest];
  next[dest] = skip[1];
  next[skip[3]] = link;

  head = next[head];
}

void solveA()
{
  auto &v = cups;
  vector<int> next(v.size()+1);
  for (int i = 0; i < 9; i++) {
    next[v[i]] = v[(i+1) % v.size()];
  }

  int head = v[0];
  for (int i = 0; i < 100; i++) {
    step(head, next, 9);
  }
  cout << "A = ";
  int x = 1;
  for (int i = 0; i < 8; i++) {
    cout << next[x];
    x = next[x];
  }
  cout << endl;
}

void solveB()
{
  vector<int> v = cups;
  v.reserve(1000000);
  for (int i = 10; i <= 1000000; i++) {
    v.push_back(i);
  }
  
  vector<int> next(v.size()+1);
  for (int i = 0; i < 1000000; i++) {
    next[v[i]] = v[(i+1) % v.size()];
  }

  int head = v[0];
  for (int i = 0; i < 10000000; i++) {
    step(head, next, 1000000);
  }
  
  long long ans = 1;
  int x = 1;
  ans *= (x = next[x]);
  ans *= (x = next[x]);
  
  cout << "B = " << ans << endl;

}

int main()
{
  solveA();
  solveB();

  return 0;
}
