/* @JUDGE_ID: 1102NT 132 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define EPS 1E-8

int px[50000], py[50000];
int n;
int cx, cy;

int check(int i, int j)
{
    int u1, u2, v1, v2;
    double x1, y1;
    int k, side;
    int best = j;

    u1 = px[j] - px[i];
    u2 = py[j] - py[i];
    v1 = cx - px[i];
    v2 = cy - py[i];
    
    x1 = (double)(u1*v1+u2*v2) / (u1*u1+u2*u2);
    y1 = (double)(u1*v2-u2*v1) / (u1*u1+u2*u2);
    if (x1 <= 0.0 || x1 >= 1.0) {
	return -1;
    }
    if (y1 >= EPS) {
        side = 1;
    } else if (y1 <= -EPS) {
        side = -1;
    } else {
        side = 0;
    }

    for (k = 0; k < n; k++) {
	v1 = px[k] - px[i];
	v2 = py[k] - py[i];
	y1 = (double)(u1*v2-u2*v1) / (u1*u1+u2*u2);
	if ((side == 1 && y1 < 0) ||
            (side == -1 && y1 > 0)) {
	    return -1;
	}
        if (side == 0 && y1 != 0) {
            side = (y1 > 0) ? 1 : -1;
        }
        if (fabs(y1) < EPS && k > best) {
            best = k;
        }
    }
    return best;

}

int main(void)
{
    char name[30];
    int i, j, smallest, t;

    while (scanf("%s", name) == 1 && strcmp(name, "#")) {
	scanf("%d %d", &cx, &cy);
	n = 0;
	while (scanf("%d %d", &px[n], &py[n]) == 2 && (px[n] || py[n])) {
	    n++;
	    assert(n <= 50000);
	}
	smallest = n;
	for (i = 0; i < n; i++) {
	    for (j = i+1; j < n; j++) {
		if (j < smallest && (t = check(i, j)) != -1) {
		    smallest = t+1;
		}
	    }
	}
	printf("%-20s%d\n", name, smallest);
    }
    return 0;
}
