#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;

    cin >> N >> M;
    vector<string> grid(N);
    for (auto &s : grid) {
	cin >> s;
    }

    int r = 0, c = 0;

    string ans;
    while (r < N && c < M) {
	if (grid[r][c] != '.') {
	    ans += grid[r][c];
	}

	// if there is something to the right, move right
	bool moved = false;
	for (int j = c+1; j < M; j++) {
	    if (grid[r][j] != '.') {
		c++;
		moved = true;
		break;
	    }
	}

	// if there is something below, move down
	for (int i = r+1; i < N && !moved; i++) {
	    if (grid[i][c] != '.') {
		r++;
		moved = true;
		break;
	    }
	}

	// can't be both
	if (!moved) {
	    r++;
	}
    }

    cout << ans << endl;

    return 0;
}
