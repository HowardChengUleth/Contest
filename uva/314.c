#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

FILE *fin, *fout;

/* 0 = N, 1 = E, 2 = S, 3 = W*/

int off_c[4] = {0, 1, 0, -1};
int off_r[4] = {-1, 0, 1, 0};

int m, n;   /* size of grid*/

int e[10000][5];  /* edge list*/

char grid[50][50];  /* row, column*/


int min(int a, int b)
{
   return (a < b) ? a : b;
}

void ReadGrid(void)
{
   int r, c;
   int t;

   for( r=0; r<m; r++ ) {
      for( c =0; c<n; c++ ) {
         fscanf(fin,"%d",&t);
         grid[r][c] = (char)t;
      }
   }
}


void ClearGraph(void)
{
   int i, j;
   for( i=0; i<10000; i++ ) {
      for( j=0; j<5; j++ ) {
         e[i][j] = -1;
      }
   }
}


int Index(int r, int c, int dir)
{
   return (r*n + c)*4 + dir;
}

void AddEdge(int r1, int c1, int d1, int r2, int c2, int d2)
{
   int i1 =Index(r1,c1,d1);
   int i2 = Index(r2,c2,d2);
   int i;


   for( i=0; i<5 && e[i1][i] >= 0; i++ )
      ;  /*loop does it all*/
   assert(i<5);

   e[i1][i] = i2;
}

void CreateDiamonds(void)
{
   int r,c;

   for( r=0; r<m; r++ ) {
      for( c=0; c<n; c++ ) {
         AddEdge(r,c,0,r,c,1);
         AddEdge(r,c,1,r,c,0);
         AddEdge(r,c,1,r,c,2);
         AddEdge(r,c,2,r,c,1);
         AddEdge(r,c,2,r,c,3);
         AddEdge(r,c,3,r,c,2);
         AddEdge(r,c,3,r,c,0);
         AddEdge(r,c,0,r,c,3);
      }
   }
}

int PtOk(int r, int c)
{
   if( !(r>=0 && r<m-1 && c>=0 &&c < n-1) )
      return 0;
   return !(grid[r][c] || grid[r+1][c] || grid[r][c+1] || grid[r+1][c+1]);
}

void BuildNode(int r, int c, int d)
{
   int nr=r, nc=c;
   int i;
   if( !PtOk(r,c) )
      return;

   for( i=0; i<3; i++ ) {
      nr += off_r[d];
      nc += off_c[d];
      if( PtOk(nr,nc) ) {
         AddEdge(r,c,d,nr,nc,d);
      } else {
         break;
      }
   }
}

void BuildGraph(void)
{
   int r,c,d;
   ClearGraph();
   CreateDiamonds();
   for( r=0; r<m-1; r++ ) {
      for( c=0; c<n-1; c++ ) {
         for( d=0; d<4; d++ ) {
            BuildNode(r,c,d);
         }
      }
   }
}

int IsEdge(int v1, int v2)
{
   int i;
   for( i=0; i<5; i++ ) {
      if( e[v1][i] == v2 )
         return 1;
   }
   return 0;
}

void ShortPath(int src, int *D)
{
   int fringe[10000], used[10000];
   int f_size;
   int v, w, i, j, wj;
   int best, best_init;

   f_size = 0;
   for (v = 0; v < 10000; v++) {
      if (IsEdge(src, v)) {
         D[v] = 1;
         fringe[f_size++] = v;
         used[v] = 1;
      } else {
         D[v] = -1;
         used[v] = 0;
      }
   }
   used[src] = 1;

   best_init = 1;
   while (best_init) {
      best_init = 0;
      for (j = 0; j < f_size; j++) {
         v = fringe[j];
         assert(D[v] != -1);
         if (!best_init || D[v] < best) {
            best = D[v];
            w = v;
            wj = j;
            best_init = 1;
         }
      }
      if (best_init) {
         assert(D[w] != -1);
         assert(fringe[wj] == w);

         /* get rid of w from fringe */
         f_size--;
         for (j = wj; j < f_size; j++) {
            fringe[j] = fringe[j+1];
         }

         for (j = 0; j < 5; j++) {
            if ((v = e[w][j]) != src && v != -1) {
               if (D[v] == -1 || D[w] + 1 < D[v]) {
                  D[v] = D[w]+1;
               }
               if (!used[v]) {
                  used[v] = 1;
                  fringe[f_size++] = v;
               }
            }
         }
      }
   }
}

void main(void)
{
   int r1, r2, c1, c2, d;
   int i1, i2;
   int i;
   int best;
   char dir[20];
   int D[10005];

/*   fin = fopen("robot.in","r");*/
/*   fout = fopen("robot.out","w");*/
   fin = stdin;
   fout = stdout;

   /* Read m and n */
   fscanf(fin,"%d %d",&m, &n);
   while( m && n ) {
      ReadGrid();
      BuildGraph();
      fscanf(fin,"%d %d %d %d %s",&r1,&c1,&r2,&c2,dir);
      r1--;
      c1--;
      r2--;
      c2--;
      switch( dir[0] ) {
         case 'n':
            d = 0;
            break;
         case 'e':
            d = 1;
            break;
         case 's':
            d = 2;
            break;
         case 'w':
            d = 3;
            break;
         default:
            assert(0);
      }
      i1 = Index(r1,c1,d);
      i2 = Index(r2,c2,0);
      ShortPath(i1,D);
      for( i=i2; i<i2+4; i++ ) {
         best = (i==i2) ? D[i2] : min(best,D[i]);
      }
      if (r1 == r2 && c1 == c2) {
         best = 0;
      }
      fprintf(fout,"%d\n",best);

      fscanf(fin,"%d %d",&m, &n);
   }
}
