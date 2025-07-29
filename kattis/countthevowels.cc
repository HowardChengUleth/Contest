#include <bits/stdc++.h>

using namespace std;

const string vowels = "aeiouAEIOU";

int main()
{
    int ans = 0;
    char ch;
    while (cin >> ch) {
	if (vowels.find(ch) != string::npos) {
	    ans++;
	}
    }
    cout << ans << endl;
    return 0;
}
