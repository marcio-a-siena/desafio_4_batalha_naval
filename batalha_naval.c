/*
BATALHA NAVAL
Márcio A. Siena - Matrícula 202104552807

Este é o desafio do módulo "4. Jogo de Batalha Naval".

A versão mais atual sempre chama-se batalha_naval.c.
Para referência, as versões anteriores são salvas em arquivos chamados "batalha_naval_N_descricao.c", como em "batalha_naval_1_novato.c".

CONSIDERAÇÕES 


Última versão:
Versão 3 - nível Mestre

Mensagem de commit (para referência):
Desafio: nível Mestre
Batalha Naval
Esta é a versão final do nível Mestre.
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

// Tipos de habilidades
#define HABILIDADE_TIPO_CONE 1
#define HABILIDADE_TIPO_CRUZ 2
#define HABILIDADE_TIPO_OCTAEDRO 3


void exibe_tabuleiro_ou_habilidades (int o_que);
void inicializa_tabuleiro_e_habilidades (void);
int  insere_habilidade (int habilidade[]);
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

Idem para a matriz de habilidades.

Para navios: valor 3 na posição ocupada pelo navio.
Para habilidades: valor 1 na posição ocupada pela habilidade.
*/
int tabuleiro[LINHAS][COLUNAS]; // valores 0 ou 3
int habilidades[LINHAS][COLUNAS]; // valores 0 ou 1


// Conversão de números para letras (exibição do cabeçalho do tabuleiro)
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

Uma melhor representação seria o uso de structs encapsuladas em módulos, mas o problema pede que arrays sejam usados.
*/
int navio_1_horizontal[6] = {NAVIO_TIPO_HORIZONTAL, 6, 4,   3, 3, 3}; // navio horizontal   a partir de Linha 6, coluna 4 ("E")
int navio_2_vertical[6]   = {NAVIO_TIPO_VERTICAL,   3, 3,   3, 3, 3}; // navio vertical     a partir de Linha 3, coluna 3 ("D")
int navio_3_diag_e_d[6]   = {NAVIO_TIPO_DIAG_E_D,   1, 5,   3, 3, 3}; // navio diagonal e-d a partir de Linha 1, coluna 5 ("F")
int navio_4_diag_d_e[6]   = {NAVIO_TIPO_DIAG_D_E,   0, 4,   3, 3, 3}; // navio diagonal d-e a partir de Linha 0, coluna 4 ("E")


/*
HABILIDADES

Cada habilidade é representada por um array de 3 inteiros:

[0] =  o tipo da navio:
- 1 = cone. As coordenadas referem-se à célula do topo.
- 2 = cruz. As coordenadas referem-se à célula do topo.
- 3 = octaedro (losango). As coordenadas referem-se à célula do topo.

[1] = linha: número da linha da primeira casa, a partir de 0.

[2] = coluna: número da coluna da primeira casa, a partir de 0.

Assim como no caso dos navios, uma melhor representação seria o uso de structs encapsuladas em módulos, mas o problema pede que arrays sejam usados.
*/

int habilidade_1_cone[3]     = {HABILIDADE_TIPO_CONE,     3, 5};
int habilidade_2_cruz[3]     = {HABILIDADE_TIPO_CRUZ,     0, 4};
int habilidade_3_octaedro[3] = {HABILIDADE_TIPO_OCTAEDRO, 3, 5};


/* ============================================================
PROGRAMA PRINCIPAL
============================================================ */
int main ()
{
  printf("\n********** DESAFIO: JOGO DE BATALHA NAVAL - NOVATO **********\n\n");

  inicializa_tabuleiro_e_habilidades();

  if (!insere_navio(navio_1_horizontal)) { return 0; }
  if (!insere_navio(navio_2_vertical))   { return 0; } 
  if (!insere_navio(navio_3_diag_e_d))   { return 0; } 
  if (!insere_navio(navio_4_diag_d_e))   { return 0; } 

  if (!insere_habilidade(habilidade_1_cone)) { return 0; }
  if (!insere_habilidade(habilidade_2_cruz)) { return 0; }
  //if (!insere_habilidade(habilidade_3_octaedro)) { return 0; }

  exibe_tabuleiro_ou_habilidades(1);
  exibe_tabuleiro_ou_habilidades(2);
  exibe_tabuleiro_ou_habilidades(3);
 

  printf("\n");
  return 1;
} // main()


/*
Exibe a matriz do tabuleiro OU a matriz de habilidades.

"o_que":
1 - tabuleiro (0 para água, 3 para navio)
2 - habilidades (0 para água, 5 para habilidade)
3 - tabuleiro + habilidades (0 para água, 3 para navio, 5 para habilidade)
*/
void exibe_tabuleiro_ou_habilidades (int o_que)
{
  // Cabeçalho das colunas
  char *cabecalho;

  if (o_que == 1) {
    cabecalho = "TABULEIRO";
  } else if (o_que == 2) {
    cabecalho = "HABILIDADES";
  } else {
    cabecalho = "TABULEIRO + HABILIDADES";
  }

  printf("** %s **********\n", cabecalho);
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
      int numero_exibido;

      if (o_que == 1) { // tabuleiro
        numero_exibido = tabuleiro[linha][coluna];
      } else if (o_que == 2) { // habilidades
        numero_exibido = habilidades[linha][coluna];
      } else { // tabuleiro + habilidades
        int valor_navio = tabuleiro[linha][coluna];
        int valor_habilidade =  habilidades[linha][coluna];
        
        if (valor_navio == 0 && valor_habilidade == 0) {
          numero_exibido = 0;
        } else if (valor_navio == 0 && valor_habilidade != 0) {
          numero_exibido = 1;
        } else if (valor_navio != 0 && valor_habilidade == 0) {
          numero_exibido = 3;
        } else {
          numero_exibido = 5;
        }
      }

      printf(" %d ", numero_exibido);
    }
    printf("\n");
  }
} // exibe_tabuleiro_ou_habilidades()


/*
Inicializa o tabuleiro e as habilidades com zeros.
Deve ser chamada a partir de main(), antes do início do jogo.
*/
void inicializa_tabuleiro_e_habilidades (void)
{
  for (int linha = 0; linha < LINHAS; ++linha) {
    for (int coluna = 0; coluna < COLUNAS; ++coluna) {
      tabuleiro[linha][coluna] = 0;
      habilidades[linha][coluna] = 0;
    }
  }
} // inicializa_tabuleiro_e_habilidades()


/*
Insere uma habilidade na matriz de habilidades.
habilidade: matriz com os dados da habilidade (veha comentários no início do arquivo).
Retorna 1 em caso de sucesso, 0 em caso de falha.
*/
int insere_habilidade (int habilidade[])
{
  const int tipo   = habilidade[0];
  const int linha  = habilidade[1];
  const int coluna = habilidade[2];

  // ------------------------------ Cone ------------------------------
  if (tipo == HABILIDADE_TIPO_CONE)
  {
    if (linha < 2) {
      printf("Linha inválida: %d\n", linha);
      return 0;
    }
  
    if (linha > (LINHAS - 3)) {
      printf("Linha inválida: %d\n", linha);
      return 0;
    }

    if (coluna < 2) {
      printf("Coluna inválida: %d\n", coluna);
      return 0;
    }

    if (coluna > (COLUNAS - 3)) {
      printf("Coluna inválida: %d\n", coluna);
      return 0;
    }

    // Ok, testa se posição está disponível
    if (habilidades[linha][coluna] != 0) {
      printf("Linha %d, coluna %d já está ocupada\n", linha, coluna);
      return 0;
    }

    for (int lin = linha+1, col = coluna-1; col <= (coluna+1); ++col) {
      if (habilidades[lin][col] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", lin, col);
        return 0;
      }
    }

    for (int lin = linha+2, col = coluna-2; col <= (coluna+2); ++col) {
      if (habilidades[lin][col] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", lin, col);
        return 0;
      }
    }

    // Ok, atribui valores 1 às posições adequadas
    habilidades[linha][coluna] = 1;
    for (int lin = linha+1, col = coluna-1; col <= (coluna+1); ++col) { habilidades[lin][col] = 1; }
    for (int lin = linha+2, col = coluna-2; col <= (coluna+2); ++col) { habilidades[lin][col] = 1; }
  }
  // ------------------------------ Cruz ------------------------------
  else if (tipo == HABILIDADE_TIPO_CRUZ)
  {
    if (linha < 0) {
      printf("Linha inválida: %d\n", linha);
      return 0;
    }
  
    if (linha > (LINHAS - 3)) {
      printf("Linha inválida: %d\n", linha);
      return 0;
    }

    if (coluna < 2) {
      printf("Coluna inválida: %d\n", coluna);
      return 0;
    }

    if (coluna > (COLUNAS - 3)) {
      printf("Coluna inválida: %d\n", coluna);
      return 0;
    }

    // Ok, testa se posição está disponível
    for (int lin=linha; lin <= (linha+2); ++lin) {
      if (habilidades[lin][coluna] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", lin, coluna);
        return 0;
      }
    }

    for (int col=(coluna-2); col <= (coluna+2); ++col) {
      if (habilidades[linha+1][col] != 0) {
        printf("Linha %d, coluna %d já está ocupada\n", linha, col);
        return 0;
      }
    }

    // Ok, atribui valores 1 às posições adequadas
    for (int lin=linha; lin <= (linha+2); ++lin)        { habilidades[lin][coluna] = 1; }
    for (int col=(coluna-2); col <= (coluna+2); ++col)  { habilidades[linha+1][col] = 1; }
  }
  // ------------------------------ Erro ------------------------------
  else
  {
    printf("Tipo inválido de habilidade: %d\n", tipo);
    return 0;
  }
  
  return 1;  // chegou aqui, inserção funcionou
} // insere_habilidade()


/*
Insere um navio (3 posições) no tabuleiro.
navio: matriz com os dados do navio (veha comentários no início do arquivo).
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

