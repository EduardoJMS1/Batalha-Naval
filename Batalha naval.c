#include <stdio.h>

#define TAM     10     // tamanho do tabuleiro: 10x10
#define VAZIO   0
#define OCUPADO 3

typedef enum { HORIZONTAL, VERTICAL, DIAG_PRINCIPAL, DIAG_SECUNDARIA } Direcao;

typedef struct {
    int linha;   
    int coluna;   
    int tamanho;  
    Direcao dir;
} Navio;

// -------- utilitários de tabuleiro --------
void inicializar(int m[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            m[i][j] = VAZIO;
}

void imprimir(const int m[TAM][TAM]) {
    printf("\n=== TABULEIRO 10x10 ===\n    ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);  // cabeçalho das colunas
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        printf("%2d: ", i);                           // rótulo da linha
        for (int j = 0; j < TAM; j++) printf("%d ", m[i][j]);
        printf("\n");
    }
}

// coordenadas da k-ésima casa do navio conforme a direção
static inline void passo(const Navio *n, int k, int *li, int *co) {
    switch (n->dir) {
        case HORIZONTAL:      *li = n->linha + 0;     *co = n->coluna + k; break;
        case VERTICAL:        *li = n->linha + k;     *co = n->coluna + 0; break;
        case DIAG_PRINCIPAL:  *li = n->linha + k;     *co = n->coluna + k; break;
        case DIAG_SECUNDARIA: *li = n->linha + k;     *co = n->coluna - k; break;
    }
}

// verifica se o navio cabe no tabuleiro e não sobrepõe outros
int podePosicionar(const int m[TAM][TAM], const Navio *n) {
    for (int k = 0; k < n->tamanho; k++) {
        int li, co; passo(n, k, &li, &co);
        if (li < 0 || li >= TAM || co < 0 || co >= TAM) return 0;   // sai dos limites
        if (m[li][co] != VAZIO) return 0;                           // sobreposição
    }
    return 1;
}

void posicionar(int m[TAM][TAM], const Navio *n) {
    for (int k = 0; k < n->tamanho; k++) {
        int li, co; passo(n, k, &li, &co);
        m[li][co] = OCUPADO;
    }
}

int main(void) {
    int tab[TAM][TAM];
    inicializar(tab);

    /* ======= NAVIOS =======*/
    Navio frota[4] = {
        { .linha = 2, .coluna = 1, .tamanho = 4, .dir = HORIZONTAL     }, // →
        { .linha = 5, .coluna = 0, .tamanho = 3, .dir = VERTICAL       }, // ↓
        { .linha = 0, .coluna = 5, .tamanho = 4, .dir = DIAG_PRINCIPAL }, // ↘
        { .linha = 0, .coluna = 8, .tamanho = 3, .dir = DIAG_SECUNDARIA}  // ↙
    };

    // valida e posiciona cada navio
    for (int i = 0; i < 4; i++) {
        if (!podePosicionar(tab, &frota[i])) {
            printf("ERRO: navio %d nao cabe ou sobrepoe outro. Ajuste as variaveis.\n", i+1);
            return 1;
        }
        posicionar(tab, &frota[i]);
    }

    imprimir(tab);   // saída completa exigida: 0 = livre, 3 = ocupado
    return 0;

}
