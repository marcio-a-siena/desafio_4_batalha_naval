/*
BATALHA NAVAL
Márcio A. Siena - Matrícula 202104552807

Este é o desafio do módulo "4. Jogo de Batalha Naval".

A versão mais atual sempre chama-se batalha_naval.c.
Para referência, as versões anteriores são salvas em arquivos chamados "batalha_naval_N_descricao.c", como em "batalha_naval_1_novato.c".

CONSIDERAÇÕES 


Última versão:
Versão 2 - nível Aventureiro

Mensagem de commit (para referência):
Desafio: nível Aventureiro
Batalha Naval
Esta é a versão final do nível Aventureiro.
*/


#include <stdio.h>


// Tamanho do tabuleiro
#define LINHAS 10
#define COLUNAS 10

// Tamanho do navio
#define TAMANHO_NAVIO 3

// Limites para inserção de navio
#define ULTIMA_LINHA_PARA_INSERCAO (LINHAS - TAMANHO_NAVIO)
#define ULTIMA_COLUNA_PARA_INSERCAO (COLUNAS - TAMANHO_NAVIO)

// Tipos de navios
#define NAVIO_TIPO_HORIZONTAL 1 // Horizontal
#define NAVIO_TIPO_VERTICAL 2   // Vertical
#define NAVIO_TIPO_DIAG_E_D 3   // Diagonal de cima para baixo, esquerda para direita
#define NAVIO_TIPO_DIAG_D_E 4   // Diagonal de cima para baixo, direita para esquerda


void exibe_tabuleiro (void);
void inicializa_tabuleiro (void);
int  insere_navio (int navio[]);


/*
TABULEIROS
No caso de um tabuleiro 10x10, teríamos:
       C0  C1  C2  C3  C4  C5  C6  C7  C8  C9
L0   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L1   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L2   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L3   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L4   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L5   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L6   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L7   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L8   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
L9   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
*/
int tabuleiro[LINHAS][COLUNAS];


// Conversão de números para letras (exibição do tabuleiro)
char *letras = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


/*
NAVIOS

Cada navio é representado por um array de 6 inteiros:

[0] = a direcao (tipo) do navio:
- 1 = inserção na horizontal, da esquerda para a direita;
- 2 = inserção vertical, de cima para baixo;
- 3 = inserção diagonal de cima para baixo, esquerda para direita;
- 4 = inserção diagonal de cima para baixo, direita para esquerda.

[1] = linha: número da linha da primeira casa, a partir de 0.

[2] = coluna: número da coluna da primeira casa, a partir de 0.

[3..5] = o estado da respectiva parte do navio. 3=íntegro.

Uma melhor representação seria o uso de structs encapsuladas em módulos,
mas o problema pede que arrays sejam usados.
*/
int navio_1_horizontal[6] = {NAVIO_TIPO_HORIZONTAL, 6, 4,   3, 3, 3}; // navio horizontal   a partir de Linha 6, coluna 4 ("E")
int navio_2_vertical[6]   = {NAVIO_TIPO_VERTICAL,   3, 3,   3, 3, 3}; // navio vertical     a partir de Linha 3, coluna 3 ("D")
int navio_3_diag_e_d[6]   = {NAVIO_TIPO_DIAG_E_D,   1, 5,   3, 3, 3}; // navio diagonal e-d a partir de Linha 1, coluna 5 ("F")
int navio_4_diag_d_e[6]   = {NAVIO_TIPO_DIAG_D_E,   0, 4,   3, 3, 3}; // navio diagonal d-e a partir de Linha 0, coluna 4 ("E")



int main ()
{
  printf("\n********** DESAFIO: JOGO DE BATALHA NAVAL - NOVATO **********\n\n");

  inicializa_tabuleiro();

  if (!insere_navio(navio_1_horizontal)) { return 0; }
  if (!insere_navio(navio_2_vertical))   { return 0; } 
  if (!insere_navio(navio_3_diag_e_d))   { return 0; } 
  if (!insere_navio(navio_4_diag_d_e))   { return 0; } 

  exibe_tabuleiro();
 

  printf("\n");
  return 1;
} // main()


void exibe_tabuleiro (void)
{
  // Cabeçalho das colunas
  printf("     ");
  for (int coluna = 0; coluna < COLUNAS; ++coluna) {
    printf(" %c ", letras[coluna]);
  }
  printf("\n");

  printf("     ");
  for (int coluna = 0; coluna < COLUNAS; ++coluna) {
    printf(" - ");
  }
  printf("\n");

  // Linhas
  for (int linha = 0; linha < LINHAS; ++linha) {
    printf("%2d | ", linha);
    for (int coluna = 0; coluna < COLUNAS; ++coluna) {
      printf(" %d ", tabuleiro[linha][coluna]);
    }
    printf("\n");
  }
} // exibe_tabuleiro()


/*
Inicializa o tabuleiro com zeros.
Deve ser chamada a partir de main(), antes do início do jogo.
*/
void inicializa_tabuleiro (void)
{
  for (int linha = 0; linha < LINHAS; ++linha) {
    for (int coluna = 0; coluna < COLUNAS; ++coluna) {
      tabuleiro[linha][coluna] = 0;
    }
  }
} // inicializa_tabuleiro()


/*
Insere um navio (3 posições) no tabuleiro.

linha: número da linha da primeira casa, a partir de 0.

coluna: número da coluna da primeira casa, a partir de 0.

direcao:
- 1 = inserção na horizontal, da esquerda para a direita;
- 2 = inserção vertical, de cima para baixo;

Retorna 1 em caso de sucesso, 0 em caso de falha.
*/
int insere_navio (int navio[])
{
  const int direcao = navio[0];
  const int linha   = navio[1];
  const int coluna  = navio[2];

  if (linha < 0) {
    printf("Linha inválida: %d\n", linha);
    return 0;
  }

  if (coluna < 0) {
    printf("Coluna inválida: %d\n", coluna);
    return 0;
  }

  // ------------------------------ Horizontal ------------------------------
  if (direcao == NAVIO_TIPO_HORIZONTAL) {
    if (coluna > ULTIMA_COLUNA_PARA_INSERCAO) {
      printf("Não é possível inserir na horizontal depois da coluna %d\n", ULTIMA_COLUNA_PARA_INSERCAO);
      return 0;
    }

    for (int n = 0; n < TAMANHO_NAVIO; ++n) { // Ok, testa se posição está disponível
      if (tabuleiro[linha][coluna + n] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", linha, coluna);
        return 0;
      }
    }

    for (int n = 0; n < TAMANHO_NAVIO; ++n) { tabuleiro[linha][coluna + n] = 3; } // Ok, insere
  }
  // ------------------------------ Vertical ------------------------------
  else if (direcao == NAVIO_TIPO_VERTICAL) {
    if (linha > ULTIMA_LINHA_PARA_INSERCAO ) {
      printf("Não é possível inserir na vertical depois da linha %d\n", ULTIMA_LINHA_PARA_INSERCAO);
      return 0;
    }

    for (int n = 0; n < TAMANHO_NAVIO; ++n) { // Ok, testa se posição está disponível
      if(tabuleiro[linha + n][coluna] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", linha, coluna);
        return 0;
      }
    }

    for (int n = 0; n < TAMANHO_NAVIO; ++n) { tabuleiro[linha + n][coluna] = 3; } // Ok, insere
  }
  // ------------------------------ Diagonal E-D ------------------------------
  else if (direcao == NAVIO_TIPO_DIAG_E_D) {
    if (linha > ULTIMA_LINHA_PARA_INSERCAO ) {
      printf("Não é possível inserir na diagonal depois da linha %d\n", ULTIMA_LINHA_PARA_INSERCAO);
      return 0;
    }

    if (coluna > ULTIMA_COLUNA_PARA_INSERCAO ) {
      printf("Não é possível inserir na diagonal depois da coluna %d\n", ULTIMA_COLUNA_PARA_INSERCAO);
      return 0;
    }

    for (int n = 0; n < TAMANHO_NAVIO; ++n) { // Ok, testa se posição está disponível
      if(tabuleiro[linha + n][coluna + n] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", linha+n, coluna+n);
        return 0;
      }
    }

    for (int n = 0; n < TAMANHO_NAVIO; ++n) { tabuleiro[linha + n][coluna + n] = 3; } // Ok, insere
  }
  // ------------------------------ Diagonal D-E ------------------------------
  else if (direcao == NAVIO_TIPO_DIAG_D_E) {
    for (int n = 0; n < TAMANHO_NAVIO; ++n) { // Ok, testa se posição está disponível
      if(tabuleiro[linha + n][coluna - n] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", linha+n, coluna-n);
        return 0;
      }
    }

    for (int n = 0; n < TAMANHO_NAVIO; ++n) { tabuleiro[linha + n][coluna - n] = 3; } // Ok, insere
  }
  // ------------------------------ Erro ------------------------------
  else {
    printf("Direção de inserção inválida: %d\n", direcao);
      return 0;
  }
  
  return 1;  // chegou aqui, inserção funcionou
} // insere_navio()

