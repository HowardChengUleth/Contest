#include <bits/stdc++.h>

using namespace std;

int main()
{
    int pos = 1;
    char cmd;

    while (cin >> cmd) {
	if (cmd == 'A') {
	    if (pos == 1) pos = 2;
	    else if (pos == 2) pos = 1;
	} else if (cmd == 'B') {
	    if (pos == 2) pos = 3;
	    else if (pos == 3) pos = 2;
	} else {
	    if (pos == 1) pos = 3;
	    else if (pos == 3) pos = 1;
	}
    }

    cout << pos << endl;

    return 0;
}
