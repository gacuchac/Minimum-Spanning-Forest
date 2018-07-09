typedef struct Subconjunto
{
    int padre, rango;
}Subconjunto;

int find(Subconjunto subs[], int i);
void Union(Subconjunto subs[], int x, int y);
