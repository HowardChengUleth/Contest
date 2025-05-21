#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
vector<pii> asc, desc;

double find_time(pii asc1, pii asc2)
{
    // (h1, t1) = asc1, (h2, t2) = asc2
    //
    // h(t) = h1 + (h2-h1)/(t2-t1) * (t - t1) for t in [t1, t2]
    //      = h1 + m * (t-t1) if m = (h2-h1)/(t2-t1)

    auto [h1, t1] = asc1;
    auto [h2, t2] = asc2;
    double m = double(h2-h1) / (t2-t1);
    
    for (int i = 0; i < desc.size()-1; i++) {
	// (dh1, dt1) = desc1, (dh2, dt2) = desc2;
	//
	// h(t) = dh1 + (dh2-dh1)/(dt2-dt1) * (t-dt1) for t in [dt1, dt2]
	//      = dh1 + dm * (t-dt1) if dm = (dh2-dh1)/(dt2-dt1)
	auto [dh1, dt1] = desc[i];
	auto [dh2, dt2] = desc[i+1];
	double dm = double(dh2-dh1) / (dt2-dt1);
	
	if (dt1 > t2 || dt2 < t1) continue;

	double denom = m - dm;
	if ((h2-h1)*(dt2-dt1) != (dh2-dh1)*(t2-t1)) {
	    double t = (dh1 - h1 - dm*dt1 + m*t1) / denom;
	    if (t1 <= t && t <= t2 && dt1 <= t && t <= dt2) {
		return t;
	    }
	} else {
	    assert(h1 == h2 && dh1 == dh2);
	    if (h1 == dh1) {
		double t = max(t1, dt1);
		assert(t1 <= t && t <= t2 && dt1 <= t && t <= dt2);
		return t;
	    }
	}
    }
    
    return -1;
}

void solve1()
{
    for (int i = 0; i < asc.size(); i++) {
	double t = find_time(asc[i], asc[i+1]);
	if (t >= 0) {
	    cout << fixed << setprecision(10) << t << endl;
	    break;
	}
    }
}

double simulate(const vector<pii> &p, double t)
{
    for (int i = 0; i < p.size()-1; i++) {
	double t1 = p[i].second, t2 = p[i+1].second;
	if (!(t1 <= t && t <= t2)) continue;
	double h1 = p[i].first, h2 = p[i+1].first;
	return h1 + double(h2-h1) / (t2-t1) * (t - t1);
    }

    assert(false);
    return -1;
}

void solve2()
{
    double lo = 0.0, hi = min(asc.back().second, desc.back().second);

    while (fabs(hi-lo) > 1e-8) {
	double mid = (lo+hi)/2.0;

	double up = simulate(asc, mid);
	double down = simulate(desc, mid);

	if (up < down) {
	    lo = mid;
	} else {
	    hi = mid;
	}
    }

    cout << fixed << setprecision(10) << lo << endl;
}

int main()
{
    int a, d;
    cin >> a >> d;

    asc.resize(a+1);
    desc.resize(d+1);
    int top = 0;
    asc[0] = make_pair(0, 0);
    for (int i = 1; i < a+1; i++) {
	int h, t;
	cin >> h >> t;
	top = asc[i].first = asc[i-1].first + h;
	asc[i].second = asc[i-1].second + t;
    }

    desc[0] = make_pair(top, 0);
    for (int i = 1; i < d+1; i++) {
	int h, t;
	cin >> h >> t;
	desc[i].first = desc[i-1].first - h;
	desc[i].second = desc[i-1].second + t;
    }
    
    solve2();
    
    return 0;
}
