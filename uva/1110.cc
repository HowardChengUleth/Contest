#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

// somehow we know that you only need <= 6 pyramids

pair<int, string> size[350];
int N = 0;

const int MAX = 1000000;
// T[i][j] = smallest pyramid (index) needed to form sum j using i pyramids
int T[7][MAX+1];

void init()
{
  // build high pyramids
  int s = 1;
  for (int n = 2; s + n*n <= 1000000; n++) {
    s += n*n;
    ostringstream oss;
    oss << n << 'H';
    size[N++] = make_pair(s, oss.str());
  }

  // build low pyramids
  s = 4;
  for (int n = 4; s + n*n <= 1000000; n += 2) {
    s += n*n;
    ostringstream oss;
    oss << n << 'L';
    size[N++] = make_pair(s, oss.str());
  }
  s = 1;
  for (int n = 3; s + n*n <= 1000000; n += 2) {
    s += n*n;
    ostringstream oss;
    oss << n << 'L';
    size[N++] = make_pair(s, oss.str());
  }
  sort(size, size+N);

  for (int i = 0; i < 7; i++) {
    fill(T[i], T[i]+MAX+1, -1);
  }
  
  for (int i = 0; i < N; i++) {
    T[1][size[i].first] = i;
  }
  
  for (int i = 2; i <= 6; i++) {
    for (int s = 0; s <= MAX; s++) {
      if (T[i-1][s] < 0) continue;
      for (int k = T[i-1][s]+1; k < N; k++) {
	int newS = s + size[k].first;
	if (newS > MAX) continue;
	if (T[i][newS] < 0 || k < T[i][newS]) {
	  T[i][newS] = k;
	}
      }
    }
  }
}

bool cmp(const pair<int, string> &p1, const pair<int, string> &p2)
{
  if (p1.first != p2.first) return p1.first > p2.first;
  return p1.second < p2.second;
}

void trace(int elems, int c, vector<pair<int, string> > &result,
	   int prev = 1000)
{
  if (elems == 1) {
    result.push_back(size[T[elems][c]]);
    return;
  }
  
  int best_i = T[elems][c];
  for (int i = best_i + 1; i < min(prev,N); i++) {
    int newS = c - size[i].first;
    if (newS < 0) continue;
    if (T[elems-1][newS] >= 0) {
      best_i = i;
    }
  }

  result.push_back(size[best_i]);
  trace(elems-1, c-size[best_i].first, result, best_i);
}

bool solve(int id)
{
  int c;
  cin >> c;
  if (!c) return false;
  
  cout << "Case " << id << ":";
  vector<pair<int, string> > result;
  
  int best = -1;
  for (int i = 1; i <= 6; i++) {
    if (T[i][c] >= 0) {
      best = i;
      break;
    }
  }
  if (best == -1) {
    cout << " impossible" << endl;
  } else {
    trace(best, c, result);
    sort(result.begin(), result.end(), cmp);
    for (unsigned int i = 0; i < result.size(); i++) {
      cout << ' ' << result[i].second;
    }
    cout << endl;
  }
  
  return true;
}

int main()
{
  init();

  int id = 1;
  while (solve(id++))
    ;
  
  return 0;
}
