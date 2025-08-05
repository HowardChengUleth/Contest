#include <bits/stdc++.h>

using namespace std;

int main()
{
    int X;
    cin >> X;

    int N;
    cin >> N;

    int cap = (N+1) * X;
    for (int i = 0; i < N; i++) {
	int P;
	cin >> P;
	cap -= P;
    }

    cout << cap << endl;

    return 0;
}
