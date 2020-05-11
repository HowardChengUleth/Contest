/*
	Problem: 	Tin Cutter
	Author:		Jan Kotas
	Algorithm:	interval compression & floodfill
	Complexity:	n^2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x[256];
int y[256];
int s[256];

char bitmap[32768];

#define TEST(x,y) (!!(bitmap[64*(x)+(y)/8]&(1<<(y)%8)))
#define SET(x,y)  (void)(bitmap[64*(x)+(y)/8]|=1<<((y)%8)) 

#define QS 8192 /* ??? queue length for floodfill 512 x 512 */

struct { int x,y; } q[QS];

int cmp(const int *a, const int *b)
{
	return *a - *b;
}

int compress(int *a, int n)
{
	int i, j;
	
	memcpy(s, a, n*sizeof(int));
	qsort(s, n, sizeof(int), cmp);
	
	for(j = 0, i = 1; i < n; i++)
		if(s[j] != s[i]) s[++j] = s[i];
		
	j++; 	
	
	for(i = 0; i < n; i++)
		a[i] = 2 * ((int*)bsearch(&a[i], s, j, sizeof(int), cmp) - s + 1);

	return 2*(j+1);
}

int dirx[4] = { -1, 1, 0, 0 };
int diry[4] = { 0, 0, -1, 1 };

void main()
{
	int i, j, ii, jj, iii, jjj, k, n, a, b, c, xn, yn, qh, qt, aserholes;
	
	for(;;)
	{
		scanf("%d", &n);
		
		if(!n) break;
		
		for(i = 0; i < 2*n; i++)
			scanf("%d%d", &x[i], &y[i]);
			
		xn = compress(x, 2*n);
		yn = compress(y, 2*n);
		
		memset(bitmap, 0, sizeof(bitmap));
		
		for(i = 0; i < 2*n; i+=2)
		{
			if(x[i] == x[i+1])
			{
				c = x[i];
				
				if(y[i] < y[i+1]) { a = y[i]; b = y[i+1]; }
				else { a = y[i+1]; b = y[i]; }
				
				for(; a <= b; a++) SET(c,a);	
			}
			else
			{
				if(x[i] < x[i+1]) { a = x[i]; b = x[i+1]; }
				else { a = x[i+1]; b = x[i]; }
				
				c = y[i];
				
				for(; a <= b; a++) SET(a,c);	
			}	
		}
		
		aserholes = 0;
		
		for(i = 0; i <= xn; i++) { SET(i,0); SET(i,yn); }
		for(j = 1; j <= yn; j++) { SET(0,j); SET(xn,j); } 
		
		for(i = 1; i < xn; i++)
		{
			for(j = 1; j < yn; j++)
			{
				if(TEST(i,j)) continue;
				SET(i,j);
				
				q[0].x = i;
				q[0].y = j;
				qh = 1;
				qt = 0;
				
				while(qh != qt)
				{
					ii = q[qt].x;
					jj = q[qt].y;
					qt = (qt+1)%QS;
				
					for(k = 0; k < 4; k++)
					{
						iii = ii + dirx[k];
						jjj = jj + diry[k];
						
						if(TEST(iii,jjj))
						{
							if(!aserholes) continue;
							iii += dirx[k];
							jjj += diry[k];
							if(TEST(iii,jjj)) continue;
						}
						SET(iii,jjj);
						
						q[qh].x = iii;
						q[qh].y = jjj;		
						qh = (qh+1)%QS;	
					}
				}
				
				aserholes++;
			}
		}
		
		printf("%d\n", aserholes-1);
	}
}
