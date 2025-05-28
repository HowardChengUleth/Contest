#include <bits/stdc++.h>

using namespace std;

int main()
{
    int h, w, n;
    cin >> h >> w >> n;

    vector<int> brick(n);
    for (auto &x : brick) {
	cin >> x;
    }


    int curr_h = 0, curr_w = 0;
    bool good = true;
    for (int i = 0; i < n && curr_h < h; i++) {
	if (curr_w + brick[i] > w) {
	    good = false;
	    break;
	}
	curr_w += brick[i];
	if (curr_w == w) {
	    curr_h++;
	    curr_w = 0;
	}
    }

    good &= (curr_h == h);       // curr_w == 0 at this point if true
    if (good) {
	cout << "YES" << endl;
    } else {
	cout << "NO" << endl;
    }
    return 0;
}
