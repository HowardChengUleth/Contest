#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<vector<int>> G;
vector<int> color;

bool odd_cycle(int v, int curr)
{
    color[v] = curr;
    for (auto w : G[v]) {
	if ((color[w] < 0 && odd_cycle(w, 1-curr)) || color[w] == curr) {
	    return true;
	}
    }
    return false;
}

int main()
{
    cin >> N >> M;
    G.resize(N);
    color.resize(N, -1);
    
    for (int i = 0; i < M; i++) {
	int u, v;
	cin >> u >> v;
	G[u].push_back(v);
	G[v].push_back(u);
    }

    for (int i = 0; i < N; i++) {
	if (color[i] < 0) {
	    if (odd_cycle(i, 0)) {
		cout << "no way" << endl;
		return 0;
	    }
	}
    }

    cout << "attend here" << endl;
    
    return 0;
}
