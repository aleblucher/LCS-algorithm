#include <stdio.h>
#include "dna.h"

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

void load_string(FILE *file, int *p, char *s, int t) {
  if (fscanf(file, "%d", p) != 1) {
    fprintf(stderr, "erro ao ler tamanho do teste %d\n", t);
  }

  char c;
  do {
    c = getc(file);
  } while (c != '\n');

  if (!fgets(s, *p + 1, file)) {
    fprintf(stderr, "erro ao ler string do teste %d\n", t);
  }
}

int mlcs_w(char a[], int n, char b[], int m, int length[MAX_SIZE + 1][MAX_SIZE + 1]) {

  // Base
  if (n == 0 || m == 0) {
    length[n][m] = 0;
    //printf("%d %d \n",n,m);
    return 0;
  }

  else if(length[n][m] >= 0){
    return length[n][m];
  }

  // Caso de genes iguais
  else if (a[n - 1] == b[m - 1]) {
    // Soma 1 ao returno e adicionando o caso na matriz
    int sol1 = mlcs_w(a, n - 1, b, m - 1, length);
    length[n][m] = 1 + sol1;
    return 1 + sol1;

  } else {
    int sol2 = mlcs_w(a,n-1,b,m, length);
    int sol3 = mlcs_w(a,n,b,m-1, length);
    //Adiciona o caso na matriz

    if (sol2 >= sol3){
      length[n][m]=sol2;
      return sol2;
    }
    else{
      length[n][m]=sol3;
      return sol3;
    }
  }
}

int mlcs(char a[], int n, char b[], int m) {
  int length[MAX_SIZE+1][MAX_SIZE+1];

  for (int i = 0; i <= MAX_SIZE; i++) {
    for (int j = 0; j <= MAX_SIZE; j++) {
      length[i][j] = -1;
      //printf("PRIMEIRO %d \n", length[i][j]);
    }
  }
  mlcs_w(a, n, b, m, length);
  return length[n][m];
}

int dlcs(char a[], int n, char b[], int m) {
  return 2;
}
