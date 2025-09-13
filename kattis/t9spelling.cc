#include <bits/stdc++.h>
#include <cassert>

using namespace std;

const string key[10] = {
    " ",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

string convert(char ch)
{
    for (int i = 0; i < 10; i++) {
	auto pos = key[i].find(ch);
	if (pos != string::npos) {
	    return string(pos+1, '0' + i);
	}
    }

    assert(false);
    return "";
}

void solve(int case_num)
{
    cout << "Case #" << case_num << ": ";

    string msg;
    getline(cin, msg);
    
    string last = "";
    for (auto ch : msg) {
	string str = convert(ch);
	if (last != "" && last.back() == str[0]) {
	    cout << ' ';
	}
	cout << str;
	last = str;
    }
    cout << endl;
}

int main()
{
    int N;
    cin >> N;
    cin.ignore(1);
    
    for (int i = 1; i <= N; i++) {
	solve(i);
    }

    return 0;
}
       
