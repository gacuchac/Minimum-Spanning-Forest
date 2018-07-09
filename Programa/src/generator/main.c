#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void shuffle(int *array, size_t n)
{
  if (n > 1)
  {
    size_t i;
    for (i = 0; i < n - 1; i++)
    {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc != 7)
  {
    printf("Modo de uso: ./generator cities sources arcs lower_bound upper_bound file.txt\n");
    return 0;
  }

  int cities = atoi(argv[1]);
  int sources = atoi(argv[2]);
  int arcs = atoi(argv[3]);
  int lower_bound = atoi(argv[4]);
  int upper_bound = atoi(argv[5]);

  if (arcs < cities + sources)
  {
    printf("Deben haber al menos (cities + sources) arcos\n");
    return 0;
  }

  // Guardo en el archivo la primera linea del archivo
  FILE* file = fopen(argv[6], "w");
  fprintf(file, "%d %d %d\n", cities, sources, arcs);

  // Primero hago un ciclo completo para asegurar que el grafo es conexo
  // Creo un arreglo de nodos desordenado
  int* nodes = malloc(sizeof(int) * (cities + sources));
  for (int i = 0; i < cities + sources; i++) nodes[i] = i;
  shuffle(nodes, cities + sources);

  // Creo aristas formando un ciclo hamiltoniano
  for (int i = 0; i < cities + sources; i++)
  {
    int id1 = nodes[i];
    int id2;
    if (i < cities + sources - 1) id2 = nodes[i + 1];
    else id2 = nodes[0];
    int cost = rand() % (upper_bound - lower_bound + 1) + lower_bound;
    fprintf(file, "%d %d %d\n", id1, id2, cost);
  }

  // Creo el resto de las aristas
  for (int i = cities + sources; i < arcs; i++)
  {
    int id1 = rand() % (cities + sources);
    int id2 = rand() % (cities + sources);
    int cost = rand() % (upper_bound - lower_bound + 1) + lower_bound;
    fprintf(file, "%d %d %d\n", id1, id2, cost);
  }

  fclose(file);

  return 0;
}
