/* @JUDGE_ID: 1102NT 222 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
  double dist;
  double cost;
} Station;

double dist_dest;
double cap, mpg;
int num_station;
Station station[51];

FILE *in, *out;

int read_case(void)
{
  int i;

  fscanf(in, "%lf\n", &dist_dest);
  if (dist_dest < 0) {
    return 0;
  }
  fscanf(in, "%lf %lf %lf %d\n", &cap, &mpg, &station[0].cost, &num_station);
  num_station++;
  station[0].dist = dist_dest;
  station[0].cost *= 100;
  for (i = 1; i < num_station; i++) {
    fscanf(in, "%lf %lf\n", &station[i].dist, &station[i].cost);
    station[i].dist = dist_dest - station[i].dist;
  }

  return 1;
}

double do_case(void)
{
  double cost_from[51], dist, used, cost, dist2;
  int best_init, i, j, must_stop;

  for (i = num_station-1; i >= 0; i--) {
    best_init = 0;
    
    /* first see if we can go without stopping */
    if (cap * mpg >= station[i].dist) {
      cost_from[i] = 0.0;
      best_init = 1;
    } else {
      /* see if we can go to a next stop */ 
      for (j = i; j < num_station; j++) {
	dist = station[i].dist - station[j].dist;
	used = dist/mpg;
	cost = floor(cost_from[j] + used*station[j].cost + 200 + 0.5);
	
	if (j < num_station-1) {
	  dist2 = station[i].dist - station[j+1].dist;
	} else {
	  dist2 = station[i].dist;
	}
	must_stop = (cap/2 <= used && used <= cap) ||
                    (used <= cap && cap * mpg < dist2);
	if (must_stop) {
	  if (!best_init || cost < cost_from[i]) {
	    cost_from[i] = cost;
	    best_init = 1;
	  } 
	}
      }
    }
    assert(best_init == 1);
  }
  return (cost_from[0] + station[0].cost)/100.0;
}


int main(void)
{
  int count;
  double cost;

  in = stdin;
  out = stdout;

  count = 0; 
  while (read_case()) {
    fprintf(out, "Data Set #%d\n", ++count);
    cost = do_case();
    fprintf(out, "minimum cost = $%0.2f\n", cost);
  }

  return 0;
}
