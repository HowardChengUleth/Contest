#include <iostream>
#include <algorithm>

using namespace std;

pair<int,int> G[2549*2];
int start[2500];
int n;

void compute_height(int v, int height[], int forbidden = -1, int curr_h = 0)
{
  height[v] = curr_h;
  for (int i = start[v]; i < 2*(n-1) && G[i].first == v; i++) {
    int w = G[i].second;
    if (forbidden >= 0 && (G[forbidden] == make_pair(v,w) ||
			   G[forbidden] == make_pair(w,v))) continue;
    if (height[w] < 0) {
      compute_height(w, height, forbidden, curr_h+1);
    }
  }
}

int diameter(int v, int forbidden)
{
  int height[2500];
  fill(height, height+n, -1);
  compute_height(v, height, forbidden);
  int index = max_element(height, height+n) - height;
  fill(height, height+n, -1);
  compute_height(index, height, forbidden);
  int max_height = *max_element(height, height+n);
  return max_height;
}

int find_center(int v, int forbidden, int max_height)
{
  int height[2500];
  fill(height, height+n, -1);
  compute_height(v, height, forbidden);

  for (int i = 0; i < n; i++) {
    if (height[i] < 0) continue;
    fill(height, height+n, -1);
    compute_height(i, height, forbidden);
    if (*max_element(height, height+n) == (max_height+1)/2) {
      return i;
    }
  }

  return -1;
}

#include <cassert>

void solve()
{
  cin >> n;

  for (int i = 0; i < n-1; i++) {
    int u, v;
    cin >> u >> v;
    G[2*i] = make_pair(u-1, v-1);
    G[2*i+1] = make_pair(v-1, u-1);
  }
  sort(G, G+2*(n-1));

  fill(start, start+n, -1);
  for (int i = 0; i < 2*(n-1); i++) {
    if (i == 0 || G[i].first != G[i-1].first) {
      start[G[i].first] = i;
    }
  }

  int best = 100000;
  int best_i = -1;
  int best_d1, best_d2;
  for (int i = 0; i < 2*(n-1); i++) {
    if (G[i].first >= G[i].second) continue;
    int d1 = diameter(G[i].first, i);
    if (d1 >= best) continue;
    int d2 = diameter(G[i].second, i);
    int newd = max(max(d1, d2), (d1+1)/2 + (d2+1)/2 + 1);
    if (newd < best) {
      best_i = i;
      best = newd;
      best_d1 = d1;
      best_d2 = d2;
    }
  }

  pair<int,int> del_edge = G[best_i];

  int best_c1 = find_center(G[best_i].first, best_i, best_d1);
  int best_c2 = find_center(G[best_i].second, best_i, best_d2);
  
  cout << best << endl;
  cout << del_edge.first+1 << ' ' << del_edge.second+1 << endl;
  cout << best_c1+1 << ' ' << best_c2+1 << endl;
  return;

  for (int i = 0; i < 2*(n-1); i++) {
    if (G[i] == del_edge) {
      G[i] = make_pair(best_c1, best_c2);
      //      cout << "here1" << endl;
      //      cout << G[i].first << '-' << G[i].second << endl;
    } else if (G[i] == make_pair(del_edge.second, del_edge.first)) {
      G[i] = make_pair(best_c2, best_c1);
      //      cout << "here2" << endl;
      //      cout << G[i].first << '-' << G[i].second << endl;
    }
  }
  sort(G, G+2*(n-1));

  fill(start, start+n, -1);
  for (int i = 0; i < 2*(n-1); i++) {
    if (i == 0 || G[i].first != G[i-1].first) {
      start[G[i].first] = i;
    }
  }

  cout << diameter(0, -1) << endl;
  assert(diameter(0, -1) == best);
}

int main(void)
{
  int N;
  cin >> N;
  while (N--)
    solve();

  return 0;
}
