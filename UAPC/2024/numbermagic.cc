#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef unsigned long long ull;

// go forward 25 steps
const int FORWARD_STEPS = 25;
const int BACKWARD_STEPS = 32 -FORWARD_STEPS;

unordered_map<ull, int> forward_dist;

void insert(unordered_map<ull, int> &M, queue<ull> &Q, ull val, int d)
{
  if (M.find(val) == M.end()) {
    M[val] = d;
    Q.push(val);
  }
}

// forward_add[i] = what to add for integers x st 10^(i-1) <= x < 10^i
ull forward_add[18];

ull type1forward(ull K)
{
  ull bound = 10;
  int i = 1;
  while (bound <= K && i < 18) {
    i++;
    bound *= 10;
  }

  if (bound <= K) {
    return 0;
  }
  
  return K + forward_add[i];
}

ull type1backward(ull K)
{
  for (int i = 1; i <= 17; i++) {
    if (K <= forward_add[i]) continue;
    ull cand = K - forward_add[i];
    if (K == type1forward(cand)) {
      return cand;
    }
  }
  return 0;
}

void forward_search(ull N)
{
  queue<ull> Q;
  
  forward_dist[N] = 0;
  Q.push(N);

  while (!Q.empty()) {
    ull curr = Q.front();
    Q.pop();
    int dist = forward_dist[curr];
    if (dist == FORWARD_STEPS) continue;

    // type 1
    insert(forward_dist, Q, type1forward(curr), dist+1);
    
    // type 2
    insert(forward_dist, Q, curr/2, dist+1);
  }
}

void backward_search(ull N)
{
  unordered_map<ull, int> back_dist;
  queue<ull> Q;

  back_dist[N] = 0;
  Q.push(N);

  while (!Q.empty()) {
    ull curr = Q.front();
    Q.pop();
    int dist = back_dist[curr];
    if (forward_dist.find(curr) != forward_dist.end()) {
      int ans = dist + forward_dist[curr];
      if (ans <= 32) {
	cout << "YES" << endl;
      } else {
	cout << "NO" << endl;
      }
      return;
    }
    if (dist == BACKWARD_STEPS) continue;
    
    // type1
    ull val = type1backward(curr);
    if (val > 0) {
      insert(back_dist, Q, val, dist+1);
    }

    // type2
    if (curr <= ULONG_LONG_MAX / 2) {
      insert(back_dist, Q, 2*curr, dist+1);
    }
    if (curr <= (ULONG_LONG_MAX / 2) - 1) {
      insert(back_dist, Q, 2*curr+1, dist+1);
    }
  }

  cout << "NO" << endl;
}

int main()
{
  forward_add[1] = 1;
  for (int i = 2; i <= 17; i++) {
    forward_add[i] = forward_add[i-1] * 10 + 1;
  }

  
  ull N, Q;
  cin >> N >> Q;

  forward_search(N);

  while (Q--) {
    ull M;
    cin >> M;
    backward_search(M);
  }


  return 0;
}
