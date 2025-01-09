#include "arb.h"

void imagine(int x, int y, Pixel **mat, Qtree *quadtree, int h, int argument) {
    int i, j;
    unsigned long long red = 0, green = 0, blue = 0, mean = 0;
    for(i = x; i < x + h; i++) {
        for(j = y; j < y + h; j++) {
            red = red + mat[i][j].Red;
            green = green + mat[i][j].Green;
            blue = blue + mat[i][j].Blue;
        }
    }
    red = red / (h * h);
    green = green / (h * h);
    blue = blue / (h * h);
    (*quadtree) = malloc(sizeof(QNod));
    (*quadtree)->red = red;
    (*quadtree)->green = green;
    (*quadtree)->blue = blue;
    for(i = x; i < x + h; i++) {
        for(j = y; j < y + h; j++) {
            mean = mean + (red - mat[i][j].Red) * (red - mat[i][j].Red);
            mean = mean + (green - mat[i][j].Green) * (green - mat[i][j].Green);
            mean = mean + (blue - mat[i][j].Blue) * (blue - mat[i][j].Blue);
        }
    }
    mean = mean / (3 * h * h);
    if(mean > argument) {
        imagine(x, y, mat, &(*quadtree)->st_sus, h / 2, argument);
        imagine(x , y + h / 2, mat, &(*quadtree)->dr_sus, h / 2, argument);
        imagine(x + h / 2, y, mat, &(*quadtree)->st_jos, h / 2, argument);
        imagine(x + h / 2, y + h / 2, mat, &(*quadtree)->dr_jos, h / 2, argument);
        return;
    } else if (mean <= argument) {
        (*quadtree)->st_sus = NULL;
        (*quadtree)->dr_sus = NULL;
        (*quadtree)->st_jos = NULL;
        (*quadtree)->dr_jos = NULL;
        return;
    }
}

int Cntniv(Qtree r)
{
	int nst_js, ndr_js, nst_ss, ndr_ss;
	if (!r) return 0;
	nst_js = Cntniv(r->st_jos); ndr_js = Cntniv(r->dr_jos); nst_ss = Cntniv(r->st_sus); ndr_ss = Cntniv(r->dr_sus);
    if (nst_js >= ndr_js && nst_js >= nst_ss && nst_js >= ndr_ss) return nst_js + 1;
    if (ndr_js >= nst_js && ndr_js >= nst_ss && ndr_js >= ndr_ss) return ndr_js + 1;
    if (nst_ss >= nst_js && nst_ss >= ndr_js && nst_ss >= ndr_ss) return nst_ss + 1;
    if (ndr_ss >= nst_js && ndr_ss >= ndr_js && ndr_ss >= nst_ss) return ndr_ss + 1;
}

int nr_frunze(Qtree r) {
    if(r == NULL)
        return 0;
    if(r->st_sus == NULL && r->dr_sus == NULL && r->st_jos == NULL && r->dr_jos == NULL)
        return 1;
    return nr_frunze(r->st_sus) + nr_frunze(r->dr_sus) + nr_frunze(r->st_jos) + nr_frunze(r->dr_jos);
}

int find_zone(Qtree r, int h) {
    int nst_js, ndr_js, nst_ss, ndr_ss;
    if(!r)
    return 0;
    if(!r->st_sus && !r->dr_sus && !r->st_jos && !r->dr_jos) {
        return h;
    } else {
        nst_js = find_zone(r->st_jos, h / 2);
        ndr_js = find_zone(r->dr_jos, h / 2);
        nst_ss = find_zone(r->st_sus, h / 2);
        ndr_ss = find_zone(r->dr_sus, h / 2);
        if(nst_ss >= ndr_ss && nst_ss >= nst_js && nst_ss >= ndr_js) {
            return nst_ss;
        } else if(ndr_ss >= nst_ss && ndr_ss >= nst_js && ndr_ss >= ndr_js) {
            return ndr_ss;
        } else if(nst_js >= ndr_js && nst_js >= nst_ss && nst_js >= ndr_ss) {
            return nst_js;
        } else if(ndr_js >= nst_js && ndr_js >= nst_ss && ndr_js >= ndr_ss) {
            return ndr_js;
        }
    }
}



void DistrArb(Qtree *r)
{
    if (!(*r)) return;
	if((*r)->st_sus != NULL && (*r)->dr_sus != NULL && (*r)->st_jos != NULL && (*r)->dr_jos != NULL) {
        DistrArb(&(*r)->st_sus);
        DistrArb(&(*r)->dr_sus);
        DistrArb(&(*r)->st_jos);
        DistrArb(&(*r)->dr_jos);
    }
    free(*r);
}

Que* InitQ ()  /* creeaza coada vida cu elemente de dimensiune d;
				   anumite implementari pot necesita si alti parametri */
{
  Que* c;          /* spatiu pentru descriptor coada */
  c = (Que*)malloc(sizeof(Que));
  if ( ! c ) return NULL;                  /* nu exista spatiu -> "esec" */

  c->prim = c->ult = NULL;
  return c;          /* intoarce adresa descriptorului cozii */
}


int IntrQ(Que *c, Qtree x)
{
  TLista aux;
  aux = (TLista)malloc(sizeof(TCelula));
  if ( ! aux) return 0;

  aux->p = x; aux->urm = NULL;

  if (c->ult != NULL)
    c->ult->urm = aux;
  else
    c->prim = aux;
  c->ult = aux;
  return 1;
}

int ExtrQ(Que *c, Qtree *x)
{ TLista aux;
  if(c->prim == NULL) {
    return 0;
  } else {
    if(c->prim == c->ult) {
      *x = c->prim->p;
      aux=c->prim;
      c->prim=NULL;
      c->ult = NULL;
      free(aux);
    } else {
      *x=c->prim->p;
      aux=c->prim;
      c->prim=c->prim->urm;
      free(aux);
    }
  return 1;
  }
}

void DistrQ(Que **c)
{
  TLista p, aux;
  p = (*c)->prim;
  while(p)
  {
    aux = p;
    p = p->urm;
    free(aux);
  }
  free(*c);
  *c = NULL;
}

int nr_noduri(Qtree r) {
    if(!r) return 0;
    return 1 + nr_noduri(r->st_sus) + nr_noduri(r->dr_sus) + nr_noduri(r->st_jos) + nr_noduri(r->dr_jos);
}

void bfs(Qtree r,int nr_n)  {
    unsigned char tip = 0;
    Qtree aux;
    Que *q = InitQ();
    IntrQ(q, r);
    int front = 0, rear = 1;
    while (front != rear) {
        ExtrQ(q, &aux);
        front++;
        if(aux->st_sus != NULL && aux->dr_sus != NULL && aux->st_jos != NULL && aux->dr_jos != NULL) {
            tip = 0;
           // fwrite(&tip, sizeof(unsigned char), 1, f);
           printf("%d\n", tip);
            IntrQ(q, aux->st_sus);
            IntrQ(q, aux->dr_sus);
            IntrQ(q, aux->st_jos);
            IntrQ(q, aux->dr_jos);
            rear += 4;
        } else {
            tip = 1;
            //fwrite(&tip, sizeof(unsigned char), 1, f);
           // fwrite(&aux->red, sizeof(unsigned char), 1, f);
          //  fwrite(&aux->green, sizeof(unsigned char), 1, f);
           // fwrite(&aux->blue, sizeof(unsigned char), 1, f);
           printf("%d\n", tip);
           printf("%d\n", aux->red);
           printf("%d\n", aux->green);
           printf("%d\n", aux->blue);
        }
    }

}

int main(int argc, char const *argv[])
{
    char  tip[3],cr[2];
    unsigned int w, h, val_max;
    int niv_fiu;
    int i, j, niv, frunze, zona = 1;
    int dimensiune;
    Qtree quadtree = NULL;
    Pixel **mat;
    FILE *f = fopen("test6.ppm", "rb");
    fscanf(f, "%s\n", tip);
    fscanf(f, "%d", &w);
    fscanf(f, "%d\n", &h);
    fscanf(f, "%d", &val_max);
    fscanf(f, "%c",cr);
    mat = malloc(h * sizeof(Pixel *));
    for(i = 0; i < h; i++)
        mat[i] = malloc(w * sizeof(Pixel));
    for(i = 0; i < h; i++) {
        for(j = 0; j < h; j++) {
        fread(&mat[i][j].Red, sizeof(unsigned char), 1, f);
        fread(&mat[i][j].Green, sizeof(unsigned char), 1, f);
        fread(&mat[i][j].Blue, sizeof(unsigned char), 1, f);
        }
    }
    fclose(f);
    imagine(0, 0, mat, &quadtree, h, 0);
    printf("%d\n", h);
    Que *q = InitQ();
    int nr_n;
    nr_n = nr_noduri(quadtree);
    bfs(quadtree,nr_n);
    return 0;
}
