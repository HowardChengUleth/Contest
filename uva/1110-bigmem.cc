#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

pair<int, string> size[350];
int N = 0;

struct Data {
  bool possible;
  unsigned char num;
  short last_used;
  
  Data() : possible(false), num(0), last_used(-1) { }
};

Data table[350][1000001];

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

  int curr = 0;
  table[curr][0].possible = true;
  s = 0;
  for (int i = 1; i <= N; i++) {
    int next = curr+1;
    for (int j = 0; j <= s; j++) {
      if (!table[curr][j].possible) continue;

      int j2 = j;
      int nextnum = table[curr][j].num;
      if (!table[next][j2].possible ||
	  nextnum < table[next][j2].num ||
	  (nextnum == table[next][j2].num &&
	   size[i-1].first > size[table[next][j2].last_used].first)) {
	table[next][j2] = table[curr][j];
      }
      
      j2 = j + size[i-1].first;
      if (j2 > 1000000) continue;
      nextnum = table[curr][j].num+1;
      if (!table[next][j2].possible ||
	  nextnum < table[next][j2].num ||
	  (nextnum == table[next][j2].num &&
	   size[i-1].first > size[table[next][j2].last_used].first)) {
	table[next][j2].possible = true;
	table[next][j2].num = nextnum;
	table[next][j2].last_used = i-1;
      }
    }
    
    s = min(1000000, s+size[i-1].first);
    curr = next;
  }
}

bool cmp(const pair<int, string> &p1, const pair<int, string> &p2)
{
  if (p1.first != p2.first) return p1.first > p2.first;
  return p1.second < p2.second;
}

void trace(int c, int N, vector<pair<int, string> > &result)
{
  int besti = -1, bestnum = -1, bestsize = -1;
  if (c == 0) return;
  
  for (int i = 0; i <= N; i++) {
    if (!table[i][c].possible) continue;
    if (besti == -1 || table[i][c].num < bestnum ||
	(table[i][c].num == bestnum &&
	 size[table[i][c].last_used].first > bestsize)) {
      besti = i;
      bestnum = table[i][c].num;
      bestsize = size[table[i][c].last_used].first;
    }
  }
  result.push_back(size[table[besti][c].last_used]);
  trace(c - bestsize, besti-1, result);
}

bool solve(int id)
{
  int c;
  cin >> c;
  if (!c) return false;
  
  cout << "Case " << id << ":";
  if (!table[N][c].possible) {
    cout << " impossible" << endl;
  } else {
    vector<pair<int, string> > result;

    trace(c, N, result);
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
