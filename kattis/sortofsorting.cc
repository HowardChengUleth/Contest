#include <bits/stdc++.h>

using namespace std;

bool compare(const string &s1, const string &s2)
{
    string prefix1 = s1.substr(0, 2);
    string prefix2 = s2.substr(0, 2);
    return prefix1 < prefix2;
}

bool solve(bool first)
{
    int n;
    if (!(cin >> n) || n == 0) {
	return false;
    }
    
    vector<string> v(n);
    for (auto &s : v) {
	cin >> s;
    }
    
    stable_sort(begin(v), end(v), compare);

    if (!first) {
	cout << endl;
    }
    for (auto s : v) {
	cout << s << endl;
    }

    return true;
}

int main()
{
    bool first = true;
    while (solve(first)) {
	first = false;
    }

    return 0;
}
