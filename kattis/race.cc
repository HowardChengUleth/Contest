#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 20;

int n, T;
int p[MAX_N], t[MAX_N], d[MAX_N];
int start, dest;
int dist[MAX_N+2][MAX_N+2];

void read()
{
  cin >> n >> T;
  for (int i = 0; i < n; i++) {
    cin >> p[i] >> t[i] >> d[i];
    if (d[i] == -1)
      d[i] = T+1;      // equivalent to no deadline
  }
  start = n;
  dest = n+1;

  for (int i = 0; i < n+2; i++) {
    for (int j = 0; j < n+2; j++) {
      cin >> dist[i][j];
    }
  }
}

// comptime[i][j]: time to go from start, visit the subset i and end
//             at j (task j done).  Only defined if bit j is set in i.
//
//             Note that my masks actually have location 1 in the most
//             significant bit and location n in the least significant bit,
//             so the tie-breaking is easier to handle.
int comptime[1 << MAX_N][MAX_N];
int points[1 << MAX_N];

int DPpoints(int mask)
{
  if (mask == 0) return points[mask] = 0;
  if (points[mask] >= 0) return points[mask];

  for (int i = 0; i < n; i++) {
    int bit = 1 << (n-1-i);
    if (mask & bit) {
      return points[mask] = DPpoints(mask-bit) + p[i];
    }
  }
  assert(false);
}

int DPcomptime(int mask, int j)
{
  if (comptime[mask][j] >= 0) return comptime[mask][j];
  
  int bitj = 1 << (n-1-j);
  assert(mask & bitj);

  if (mask == bitj) {
    // go from start
    int temp = dist[start][j] + t[j];
    return comptime[mask][j] = (temp > d[j]) ? T+1 : temp;
  }
  
  int best = T+1;
  for (int i = 0; i < n; i++) {
    int biti = 1 << (n-1-i);
    if (!(mask & biti) || i == j) continue;
    
    int temp = DPcomptime(mask - bitj, i) + dist[i][j] + t[j];
    if (temp > d[j]) continue;       // too late
    best = min(temp, best);
  }
  
  return comptime[mask][j] = best;
}

void solve()
{
  fill(points, points + (1 << n), -1);
  for (int mask = 0; mask < (1 << n); mask++) {
    fill(comptime[mask], comptime[mask]+n, -1);
    DPpoints(mask);
  }


  int best = 0;
  int best_mask = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int j = 0; j < n; j++) {
      if (!((1 << (n-1-j)) & mask)) continue;
      if (DPcomptime(mask, j) + dist[j][dest] > T) continue;
      if (points[mask] > best ||
	  (points[mask] == best && mask > best_mask)) {
	best = points[mask];
	best_mask = mask;
	/*
	cout << "mask = " << mask << endl;
	cout << "j = " << j << endl;
	cout << "points = " << best << endl;
	cout << "comptime = " << comptime[mask][j] << endl;
	cout << "===" << endl;
	*/
      }
    }
  }

  cout << best << endl;
  bool printed = false;
  for (int i = 0; i < n; i++) {
    if ((1 << (n-1-i)) & best_mask) {
      if (printed) cout << ' ';
      cout << i+1;
      printed = true;
    }
  }
  cout << endl;
}

int main()
{
  read();
  solve();
  
  return 0;
}
	
