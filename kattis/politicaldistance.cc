#include <bits/stdc++.h>

using namespace std;

int main()
{
    int64_t x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    uint64_t dx = (x1 > x2) ? x1 - x2 : x2 - x1;
    uint64_t dy = (y1 > y2) ? y1 - y2 : y2 - y1;

    cout << dx*dx + dy*dy << endl;
    

    return 0;
}
