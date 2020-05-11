/*

  1995-96 ACM International Collegiate Programming Contest
  Southwestern European Regional Contest
  ETH Zurich, Switzerland
  December 9, 1995


  Problem: Synchronous

  Idea and implementation:	Manuel Bleichenbacher, Head Judge

  Source file: synchronous.c / synchronous.p
  Input file: synchronous.in
  Output file: synchronous.out

*/

#include <stdio.h>
#include <stdlib.h>

/*	type definition for the node and connection data structures */


typedef enum { FALSE = 0, TRUE = 1 } bool;


/*  data type for nodes */

typedef struct {
  bool	isSynch;		/* is node synchronous? */
  int	delay;			/* delay between input and output */
  int	incomingConnections;	/* number of incomingConnections connections */
  bool	removed;		/* already removed on search for cycles? */ 
  int	totalDelay;		/* total delay since synchronous node */
} NODE;

/* data structure for connections */

typedef struct {
  int	from;			/* outgoing node */
  int	to;			/* incomingConnections node */
} CONNECTION;


/*	declaration of subroutines */
void read_circuit(FILE* fp);
void delete_circuit();
void analyze_circuit(FILE* fp);
void propagate_delay(int node);


/* static data */

NODE*		sNodes;			/* array of nodes */
int		sNumNodes;		/* number of nodes */
CONNECTION*	sConnections;		/* array of connections */
int		sNumConnections;	/* number of connections */
int		sClockPeriod;		/* clock period */
int		sMaxDelay;		/* maximum delay */


int main()
{
  int numCircuits;
  int i;
  FILE *fin, *fout;
	
  fin = stdin;
  fout = stdout;
	
  /* read number of circuits */
  fscanf(fin, "%d", &numCircuits);
	
  /* for every circuit, read it in, analyze it and clean up */
  for (i=0; i < numCircuits; i++) {
    read_circuit(fin);
    analyze_circuit(fout);
    delete_circuit();
  }
	
  return 0;
}

void read_circuit(FILE* fp)
{
  char type[20];
  int i;

  /* read the clock period */
  fscanf(fp, "%d", &sClockPeriod);
	
  /* read the number of nodes */
  fscanf(fp, "%d", &sNumNodes);
  /* allocate the nodes */
  sNodes = (NODE*) calloc( sNumNodes, sizeof(NODE) );

  for (i=0; i < sNumNodes; i++) {
    /* read the type and delay of the node */
    fscanf(fp, "%s %d", type, &sNodes[i].delay);
    sNodes[i].isSynch = ( type[0] != 'a' );
    sNodes[i].totalDelay = 0;
    sNodes[i].incomingConnections = 0;
    sNodes[i].removed = FALSE;
  }
	
  /* read the number of connections */
  fscanf(fp, "%d", &sNumConnections);
  /* allocate the connections */
  sConnections = (CONNECTION*) calloc( sNumConnections, sizeof(CONNECTION) );
	
  for (i=0; i < sNumConnections; i++) {
    fscanf(fp, "%d %d", &sConnections[i].from, &sConnections[i].to);
  }
}

void delete_circuit()
{
  free( sNodes );
  free( sConnections );
}

void analyze_circuit(FILE* fp)
{
  /*	search for cycles in the circuits */
  
  /*	Strategy: We count the number of incomingConnections
	connections for every node.  Then we remove all nodes without
	incomingConnections connections together with their outgoing
	connections until no nodes are left (no cycles in the circuit)
	or no further nodes can be removed (cycle in the circuit).
	Synchronously working nodes always break a cycle and therefore
	don't count. */
	
  bool nodeRemoved;
  int numRemovedNodes;
  int i,j;
	
  /* count number of incomingConnections connections */
  for (i=0; i < sNumConnections; i++) {
    int to = sConnections[i].to;
    if ( !sNodes[to].isSynch )
      sNodes[to].incomingConnections ++;
  }
		
  nodeRemoved = TRUE;
  numRemovedNodes = 0;
  while ( nodeRemoved ) {
    /* while a further node has been removed do ... */
    nodeRemoved = FALSE;
		
    for (i=0; i < sNumNodes; i++) {	/* loop over all nodes */
      if (!sNodes[i].removed && sNodes[i].incomingConnections == 0) {
	/* node has no incomingConnections connections => remove it */
	nodeRemoved = TRUE;
	numRemovedNodes++;
	/* remove nodes */
	sNodes[i].removed = TRUE;
	/* remove outgoing connections */
	for (j=0; j < sNumConnections; j++) {
	  int to = sConnections[j].to;
	  if (sConnections[j].from == i && !sNodes[to].isSynch)
	    sNodes[to].incomingConnections--;
	}
      }
    }
  }
	
  /* if all nodes have been removed, there are no cycles */
  if (numRemovedNodes != sNumNodes) {
    fprintf(fp, "Circuit contains cycle.\n");
    return;
  }
	
	
  /*	calculate delays */
	
  /*	Strategy: We start at all inputs and propagate recursively the
	delays until we reach an output or a synchronous node. The
	outputs of synchronous nodes are also considered as
	inputs. This algorithm will terminate because we know there
	are no cycles. */

  sMaxDelay = 0;
  for (i=0; i < sNumNodes; i++)	
    if ( sNodes[i].isSynch )		/* start propagating the delays */
      propagate_delay(i);
	
  if (sMaxDelay > sClockPeriod)
    fprintf(fp, "Clock period exceeded.\n");
  else
    fprintf(fp, "Synchronous design. Maximum delay: %d.\n", sMaxDelay);
}


void propagate_delay(int i)
{
  int j;
	
  /* for all connections that lead from the current node to another
     one do ... */
  for (j=0; j < sNumConnections; j++)
    if (sConnections[j].from == i) {
      /* calculate new delay and take the maximum of the new and old value */
      int to = sConnections[j].to;
      int newDelay = sNodes[i].totalDelay + sNodes[to].delay;
      if (newDelay > sNodes[to].totalDelay) {
	sNodes[to].totalDelay = newDelay;
	if (newDelay > sMaxDelay)
	  sMaxDelay = newDelay;
	/* recursively propagte the new delay */
	if (!sNodes[to].isSynch)
	  propagate_delay(to);
      }
    }
}

