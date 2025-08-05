#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    int ans = -1;

    for (int i = 0; i < N; i++) {
	int M, O;
	cin >> M >> O;
	if (!O) {
	    if (ans == -1 || M < ans) {
		ans = M;
	    }
	}
    }

    cout << ans << endl;

    
    return 0;
}
