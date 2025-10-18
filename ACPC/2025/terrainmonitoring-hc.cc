#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int n;

vector<pii> tmax, tmin;
vector<int> h;

void build_tree(int rstart, int rend, int index = 0)
{
  if (rstart >= rend) return;

  if (rend - rstart == 1) {
    tmax[index] = tmin[index] = pii(h[rstart], rstart);
    return;
  }

  int rmid = rstart + (rend-rstart)/2;

  build_tree(rstart, rmid, 2*index+1);
  build_tree(rmid, rend, 2*index+2);
  tmax[index] = max(tmax[2*index+1], tmax[2*index+2]);
  tmin[index] = min(tmin[2*index+1], tmin[2*index+2]);
}

pii find_max(int start, int end, int rstart, int rend, int index = 0)
{
  if (rend - rstart == 1) {
    return pii(h[rstart], rstart);
  }
  if (start == rstart && end == rend) {
    return tmax[index];
  }
  
  int rmid = rstart + (rend-rstart)/2;

  if (end <= rmid) {
    return find_max(start, end, rstart, rmid, 2*index+1);
  } else if (start >= rmid) {
    return find_max(start, end, rmid, rend, 2*index+2);
  }

  pii left = find_max(start, rmid, rstart, rmid, 2*index+1);
  pii right = find_max(rmid, end, rmid, rend, 2*index+2);

  return max(left, right);
}

pii find_min(int start, int end, int rstart, int rend, int index = 0)
{
  if (rend - rstart == 1) {
    return pii(h[rstart], rstart);
  }
  if (start == rstart && end == rend) {
    return tmin[index];
  }
  
  int rmid = rstart + (rend-rstart)/2;

  if (end <= rmid) {
    return find_min(start, end, rstart, rmid, 2*index+1);
  } else if (start >= rmid) {
    return find_min(start, end, rmid, rend, 2*index+2);
  }

  pii left = find_min(start, rmid, rstart, rmid, 2*index+1);
  pii right = find_min(rmid, end, rmid, rend, 2*index+2);

  return min(left, right);
}

void update_val(int pos, int val, int start, int end, int index = 0)
{
  if (end - start == 1) {
    assert(pos == start);
    tmax[index] = tmin[index] = pii(h[start] = val, start);
    return;
  }

  int mid = start + (end-start)/2;

  if (pos < mid) {
    update_val(pos, val, start, mid, 2*index+1);
  } else {
    update_val(pos, val, mid, end, 2*index+2);
  }
  tmax[index] = max(tmax[2*index+1], tmax[2*index+2]);
  tmin[index] = min(tmin[2*index+1], tmin[2*index+2]);
}
		
void update(int start, int end)
{
  auto [min_val, min_i] = find_min(start, end, 0, n);
  auto [max_val, max_i] = find_max(start, end, 0, n);

  int sum = min_val + max_val;

  update_val(min_i, sum/2, 0, n);
  update_val(max_i, (sum+1)/2, 0, n);
}

int main()
{
  cin >> n;

  h.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }

  tmin.resize(4*n);
  tmax.resize(4*n);

  build_tree(0, n);

  int q, t;
  cin >> q >> t;

  for (int i = 0; i < q; i++) {
    char c;
    int a, b;
    cin >> c >> a >> b;

    if (c == 'L') {
      update(a-1, b);
    } else {
      int maxval = find_max(a-1, b, 0, n).first;
      int minval = find_min(a-1, b, 0, n).first;
      int diff = maxval - minval;

      if (diff < t) {
	cout << "SAFE" << endl;
      } else {
	cout << "DANGER" << endl;
      }
    }

  }

  
  return 0;
}
