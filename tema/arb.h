#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree {
	unsigned char red, green, blue;
	struct Tree *st_sus, *dr_sus, *st_jos, *dr_jos;
} QNod, *Qtree;

typedef struct rgb {
    unsigned char Red, Green, Blue;
} Pixel;

typedef struct celula
{
  Qtree p;
  struct celula* urm;
} TCelula, *TLista;

typedef struct que {
  TLista prim, ult;
} Que;

int Cntniv(Qtree quadtree);
int nr_frunze(Qtree r);
int find_zone(Qtree r, int h);
void DistrArb(Qtree *a);
void imagine(int x, int y, Pixel **mat, Qtree *quadtree, int h, int argument);

Que* InitQ ();
int IntrQ(Que *c, Qtree x);
int ExtrQ(Que *c, Qtree *x);
void bfs(Qtree r,int nr_n);
int nr_noduri(Qtree r);
