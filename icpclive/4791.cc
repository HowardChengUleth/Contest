//
// Idea: Use Dynamic Programming and sweep from left to right.  Instead of
// thinking of it as a tour, we can think of two island-disjoint paths
// from left to right (except for 0 and n-1).  We can also fix b1 to be
// on path 1 and b2 to be on path 2 since they are interchangeable.
//
// The state in the DP is dist[i][j] = min distance to start from vertex i
// in path 1, and vertex j in path 2, after consider vertices max(i,j)+1 to
// n-1.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

int n, b1, b2;

double dist[100][100];
int choice[100][100];
int x[100], y[100];
int path1[100], path2[100];
int n1, n2;

double d(int i, int j)
{
  int dx = x[i]-x[j], dy = y[i]-y[j];
  return sqrt(dx*dx + dy*dy);
}

double compute(int i, int j)
{
  if (choice[i][j] > 0) {
    return dist[i][j];
  }

  int k = max(i, j) + 1;
  
  // at the end
  if (k == n) {
    choice[i][j] = 1;
    return dist[i][j] = d(i, n-1) + d(j, n-1);
  }

  // we connect k to either path 1 or path 2
  double dist1 = d(i, k) + compute(k, j);
  double dist2 = d(j, k) + compute(i, k);

  if (k == b1) {
    // must choose the first path
    choice[i][j] = 1;
    return dist[i][j] = dist1;
  } else if (k == b2) {
    // must choose the second path
    choice[i][j] = 2;
    return dist[i][j] = dist2;
  } else if (dist1 < dist2) {
    choice[i][j] = 1;
    return dist[i][j] = dist1;
  } else {
    choice[i][j] = 2;
    return dist[i][j] = dist2;
  }
}

void construct_path(void)
{
  n1 = n2 = 0;
  
  path1[n1++] = path2[n2++] = 0;
  
  int i, j;
  i = 0; j = 0;
  for (int k = 1; k < n; k++) {
    assert(k == max(i, j) + 1);
    if (choice[i][j] == 1) {
      path1[n1++] = k;
      i = k;
    } else {
      path2[n2++] = k;
      j = k;
    }
  }

  if (path2[1] == 1) {
    for (int i = 0; i < max(n1, n2); i++) {
      swap(path1[i], path2[i]);
    }
    swap(n1, n2);
  }
}

bool do_case(int case_num)
{
  cin >> n >> b1 >> b2;
  if (!n && !b1 && !b2) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  
  cout << "Case " << case_num << ": ";
  
  for (int i = 0; i < n; i++) {
    fill(choice[i], choice[i]+n, 0);
  }

  cout.setf(ios::fixed);
  cout << setprecision(2) << compute(0, 0) << endl;
  
  // now construct the path
  construct_path();
  
  for (int i = 0; i < n1; i++) {
    cout << path1[i] << ' ';
  }
  for (int i = n2-1; i >= 0; i--) {
    cout << path2[i];
    if (i) {
      cout << ' ';
    } else {
      cout << endl;
    }
  }
  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  
  return 0;
}
