#include <stdio.h>
#include <stdlib.h>  // Adicionado para corrigir uso de abs()


#define TAM 10
#define HABILIDADE_TAM 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para sobrepor uma matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HABILIDADE_TAM][HABILIDADE_TAM], int origemLinha, int origemColuna) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            int tabLinha = origemLinha - HABILIDADE_TAM / 2 + i;
            int tabColuna = origemColuna - HABILIDADE_TAM / 2 + j;
            // Verifica se está dentro dos limites do tabuleiro
            if (tabLinha >= 0 && tabLinha < TAM && tabColuna >= 0 && tabColuna < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[tabLinha][tabColuna] != NAVIO) {
                    tabuleiro[tabLinha][tabColuna] = HABILIDADE;
                }
            }
        }
    }
}

// Função para criar matriz Cone
void criarCone(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            habilidade[i][j] = (j >= HABILIDADE_TAM / 2 - i && j <= HABILIDADE_TAM / 2 + i) ? 1 : 0;
        }
    }
}

// Função para criar matriz Cruz
void criarCruz(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            habilidade[i][j] = (i == HABILIDADE_TAM / 2 || j == HABILIDADE_TAM / 2) ? 1 : 0;
        }
    }
}

// Função para criar matriz Octaedro (losango)
void criarOctaedro(int habilidade[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            int distancia = abs(HABILIDADE_TAM / 2 - i) + abs(HABILIDADE_TAM / 2 - j);
            habilidade[i][j] = (distancia <= HABILIDADE_TAM / 2) ? 1 : 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializar tabuleiro com água
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posicionar dois navios horizontais/verticais
    tabuleiro[1][2] = NAVIO; tabuleiro[1][3] = NAVIO; tabuleiro[1][4] = NAVIO;
    tabuleiro[4][7] = NAVIO; tabuleiro[5][7] = NAVIO; tabuleiro[6][7] = NAVIO;

    // Posicionar dois navios diagonais
    tabuleiro[0][0] = NAVIO; tabuleiro[1][1] = NAVIO; tabuleiro[2][2] = NAVIO;
    tabuleiro[0][9] = NAVIO; tabuleiro[1][8] = NAVIO; tabuleiro[2][7] = NAVIO;

    // Criar e aplicar habilidades
    int cone[HABILIDADE_TAM][HABILIDADE_TAM];
    int cruz[HABILIDADE_TAM][HABILIDADE_TAM];
    int octaedro[HABILIDADE_TAM][HABILIDADE_TAM];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);

    // Exibir tabuleiro final
    printf("\nTabuleiro com habilidades:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf("~ ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf("■ ");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf("* ");
            }
        }
        printf("\n");
    }

    return 0;
}