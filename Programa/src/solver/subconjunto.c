#include "subconjunto.h"

extern int ciudades;

int find(Subconjunto subs[], int i){
  if (subs[i].padre != i)
        subs[i].padre = find(subs, subs[i].padre);

  return subs[i].padre;
}

void Union(Subconjunto subs[], int x, int y){
  int xroot = find(subs, x);
  int yroot = find(subs, y);

  if (xroot >= ciudades ) {
    subs[yroot].padre = xroot;
    subs[xroot].rango++;
    return;
  }

  if (yroot >= ciudades ) {
    subs[xroot].padre = yroot;
    subs[yroot].rango++;
    return;
  }

  if (subs[xroot].rango < subs[yroot].rango)
      subs[xroot].padre = yroot;
  else if (subs[xroot].rango > subs[yroot].rango)
      subs[yroot].padre = xroot;

  else
  {
      subs[yroot].padre = xroot;
      subs[xroot].rango++;
  }
}
