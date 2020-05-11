#include <iostream>
#include <algorithm>

using namespace std;

int n;
int a[100], m[100], g[100];

bool G[100][100];

bool mycmp(pair<int,int> a, pair<int,int> b)
{
  return (a.first-a.second) > (b.first - b.second);
}

// returns the minimum number of attackers needed and how many are used up
// during the attack
pair<int,int> DFS(int r, bool visited[])
{
  visited[r] = true;

  // we need to do this recursively for each subtree
  int children = 0;
  pair<int, int> result[100];
  for (int i = 0; i < n; i++) {
    if (G[r][i] && !visited[i]) {
      result[children++] = DFS(i, visited);
    }
  }

  int used = m[r] + g[r];
  int need = max(a[r], used); 
  
  // leaf node: the answer is simple
  if (children == 0) {
    return make_pair(need, used);
  }

  // not leaf: it is always best to attack the subtree that has the largest
  // attackers needed - used up first.
  sort(result, result+children, mycmp);

  int left = need - used;
  for (int i = 0; i < children; i++) {
    int diff = result[i].first - left;
    if (diff > 0) {
      need += diff;
      left += diff;
    }
    left -= result[i].second;
  }

  used = need - left;
  return make_pair(need, used);
}

bool do_case(int case_num)
{
  cin >> n;
  if (n == 0) {
    return false;
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> m[i] >> g[i];
  }
  
  for (int i = 0; i < n; i++) {
    fill(G[i], G[i]+n, false);
  }
  for (int i = 0; i < n-1; i++) {
    int a, b;
    cin >> a >> b;
    G[a-1][b-1] = G[b-1][a-1] = true;
  }

  // try starting at every node
  pair<int, int> result[100];
  for (int root = 0; root < n; root++) {
    bool visited[100];
    fill(visited, visited+n, false);
    result[root] = DFS(root, visited);
  }

  cout << "Case " << case_num << ": "
       << min_element(result, result+n)->first << endl;
  return true;
}

int main(void)
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
