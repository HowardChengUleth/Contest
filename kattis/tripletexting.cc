#include <bits/stdc++.h>

using namespace std;

int main()
{
    string str;
    cin >> str;

    int n = str.length() / 3;

    for (int i = 0; i < n; i++) {
	char c1 = str[i], c2 = str[i + n], c3 = str[i + 2*n];
	if (c1 == c2 || c1 == c3) {
	    cout << c1;
	} else {
	    cout << c2;
	}
    }
    cout << endl;


    return 0;
}
