#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> event;
map<string, int> ind;

int get_index(const string &e)
{
  map<string,int>::iterator it = ind.find(e);
  if (it == ind.end()) {
    ind[e] = event.size();
    event.push_back(e);
    return ind[e];
  } else {
    return it->second;
  }
}

bool solve(int id)
{
  int nc;
  cin >> nc;
  if (!nc) return false;

  const int MAX_E = 300;
  bool A[MAX_E][MAX_E];

  for (int i = 0; i < MAX_E; i++) {
    fill(A[i], A[i]+MAX_E, false);
  }

  event.clear();
  ind.clear();
  for (int i = 0; i < nc; i++) {
    int ne;
    cin >> ne;
    int prev = -1;
    for (int j = 0; j < ne; j++) {
      string e;
      cin >> e;
      int t = get_index(e);
      if (j > 0) {
	A[prev][t] = true;
      }
      prev = t;
    }
  }

  int nm;
  cin >> nm;
  while (nm--) {
    string e1, e2;
    cin >> e1 >> e2;
    int t1 = get_index(e1), t2 = get_index(e2);
    A[t1][t2] = true;
  }

  int N = event.size();
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
	A[i][j] |= A[i][k] && A[k][j];
      }
    }
  }

  int count = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (!A[i][j] && !A[j][i]) count++;
    }
  }

  cout << "Case " << id << ", ";
  if (count == 0) {
    cout << "no concurrent events." << endl;
  } else {
    cout << count << " concurrent events:" << endl;
    count = min(2,count);
    for (int i = 0; i < N && count; i++) {
      for (int j = i+1; j < N && count; j++) {
	if (A[i][j] || A[j][i]) continue;
	cout << '(' << event[i] << ',' << event[j] << ')' << ' ';
	count--;
      }
    }
    cout << endl;
  }
  return true;
}

int main(void)
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
