#include "dna.h"
#include <stdio.h>

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
    return 0;
  }

  // Caso já registrado na matriz
  else if (length[n][m] >= 0) {
    return length[n][m];
  }

  // Caso de genes iguais
  else if (a[n - 1] == b[m - 1]) {
    int next_pair = mlcs_w(a, n - 1, b, m - 1, length); // Chamada recursiva para o próximo par
    length[n][m] = 1 + next_pair;                       // Soma 1 a recursão e adicionando o caso na matriz
    return 1 + next_pair;

    // Caso de genes diferentes
  } else {
    int shift_n = mlcs_w(a, n - 1, b, m, length);
    int shift_m = mlcs_w(a, n, b, m - 1, length);
    //Adiciona o caso na matriz

    if (shift_n >= shift_m) {
      length[n][m] = shift_n;
      return shift_n;
    } else {
      length[n][m] = shift_m;
      return shift_m;
    }
  }
}

int mlcs(char a[], int n, char b[], int m) {
  int length[MAX_SIZE + 1][MAX_SIZE + 1];

  // Inicializa a matriz com todos valores sendo -1
  for (int i = 0; i <= MAX_SIZE; i++) {
    for (int j = 0; j <= MAX_SIZE; j++) {
      length[i][j] = -1;
    }
  }
  mlcs_w(a, n, b, m, length);
  return length[n][m];
}

int dlcs(char a[], int n, char b[], int m) {
  //Cria a matriz com o tamanho ajustado
  int lenght[n + 1][m + 1];

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (i == 0 || j == 0) {
        // Preenche a primeira linha e a primeira coluna com zeros
        lenght[i][j] = 0;
      } else if (a[i - 1] == b[j - 1]) {
        // Caso de genes iguais
        lenght[i][j] = 1 + lenght[i - 1][j - 1];
      } else {
        // Devolve o "caminho" da matriz com a maior subsquencia
        lenght[i][j] = max(lenght[i - 1][j], lenght[i][j - 1]);
      }
    }
  }
  return lenght[n][m];
}
