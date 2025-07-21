#include <bits/stdc++.h>

using namespace std;

int main()
{
    int rem = 0;

    char ch;
    while (cin >> ch) {
	rem = (rem + ch - '0') % 3;
    }

    if (rem == 0) {
	cout << "Jebb" << endl;
    } else {
	cout << "Neibb" << endl;
    }

    return 0;
}
