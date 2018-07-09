#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arista.h"
#include "subconjunto.h"

int ciudades = 0;

int Comparar(const void* a, const void* b)
{
    struct Arista* a1 = (struct Arista*)a;
    struct Arista* b1 = (struct Arista*)b;
    return a1->peso - b1->peso;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Modo de uso: ./solver test.txt\n");
		return 0;
	}

	const size_t len1 = strlen("tests/");
	const size_t len2 = strlen(argv[1]);
	char *resultado = malloc(len1 + len2 + 1);
	memcpy(resultado, "tests/", len1);
  memcpy(resultado + len1, argv[1], len2 + 1);

	FILE* file = fopen (resultado, "r");
  int i = 0;
	fscanf (file, "%i", &i);
	ciudades = i;
	fscanf (file, "%i", &i);
	int fuentes = i;
	fscanf (file, "%i", &i);
	int conexiones = i;

	int V = ciudades + fuentes;

	// Crear grafo inicial como arreglo de aristas
  Arista *arista = malloc(sizeof(Arista)*conexiones);

	// Poblar grafo
	int j = 0;
  while (j < conexiones)
    {
			fscanf (file, "%i", &i);
			arista[j].origen = i;
			fscanf (file, "%i", &i);
			arista[j].destino = i;
			fscanf (file, "%i", &i);
			arista[j].peso = i;
			arista[j].posicion = j;
			j++;
    }
  fclose (file);
  free(resultado);

	// Kruskal
	Arista result[V];
	int e = 0;
	i = 0;
	qsort(arista, conexiones, sizeof(Arista), Comparar);

	// Cambio nomenclatura de subconjunto a subset en ingles porque es mas corto
	Subconjunto *subsets =(Subconjunto*)malloc(V*sizeof(Subconjunto));

	// Comienzan cada uno en su subconjunto
	for (int v = 0; v < V; v++) {
      subsets[v].padre = v;
			subsets[v].rango = 0;
			if (v > 19) {
				subsets[v].rango = 1000000;
			}
  }

  int listo;
	while (e < V - 1) {
      // Menor arista
      Arista proximo = arista[i++];

      int x = find(subsets, proximo.origen);
      int y = find(subsets, proximo.destino);

			// Si ambas root son fuente, seguir a proxima arista
      if (x >= ciudades && y >= ciudades) {
        continue;
      }

      // Buscamos ciclo
      if (x != y)
      {
          result[e++] = proximo;
          Union(subsets, x, y);
      }

			// Verificamos si todos estan conectados a alguna fuente
			listo = 1;
			for (int v = 0; v < ciudades; v++) {
        int root = find(subsets,v);
				if (root < ciudades) {
					listo = 0;
					break;
				}
		  }

			if (listo == 1) {
				break;
			}
    }

    FILE* output = fopen ("result.txt", "w");
		int peso = 0;
		for (int m = 0; m < e; m++) {
			peso += result[m].peso;
      // Imprimimos la arista agregada
      fprintf(output, "%i\n",result[m].posicion);
		}
    fclose(output);
    free(arista);
    free(subsets);

	// Retorno ok
	return 0;
}
