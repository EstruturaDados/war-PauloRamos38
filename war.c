#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5
#define NOME_MAX 30
#define COR_MAX 16
#define COR_INIMIGA "Verde"

typedef struct {
    char nome[NOME_MAX];
    char cor[COR_MAX];
    int tropas;
} Territorio;

void limparBufferEntrada(void);
void lerTexto(char destino[], size_t tamanho);
void cadastrarTerritorios(Territorio territorios[], int tamanho);
void definirCorJogador(char corJogador[], size_t tamanho);
void configurarJogo(Territorio territorios[], int tamanho, char corJogador[], size_t tamanhoCor, int *missao);
void executarLoopPrincipal(Territorio territorios[], int tamanho, const char *corJogador, int missao);
void exibirMapa(const Territorio territorios[], int tamanho);
void exibirMenuPrincipal(void);
int sortearMissao(void);
void exibirMissao(int missao, const char *corJogador);
void faseDeAtaque(Territorio territorios[], int tamanho, const char *corJogador);
void simularAtaque(Territorio territorios[], int tamanho, int origem, int destino, const char *corJogador);
int verificarVitoria(const Territorio territorios[], int tamanho, int missao, const char *corJogador);
int contarTerritoriosComCor(const Territorio territorios[], int tamanho, const char *cor);

void limparBufferEntrada(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void lerTexto(char destino[], size_t tamanho) {
    if (fgets(destino, (int)tamanho, stdin) != NULL) {
        destino[strcspn(destino, "\n")] = '\0';
    }
}

void cadastrarTerritorios(Territorio territorios[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        printf("Digite o nome do territorio: ");
        lerTexto(territorios[i].nome, sizeof(territorios[i].nome));

        printf("Digite a cor do territorio: ");
        lerTexto(territorios[i].cor, sizeof(territorios[i].cor));

        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();
    }
}

void definirCorJogador(char corJogador[], size_t tamanho) {
    printf("\nDigite a cor do seu exercito: ");
    lerTexto(corJogador, tamanho);
}

void configurarJogo(Territorio territorios[], int tamanho, char corJogador[], size_t tamanhoCor, int *missao) {
    cadastrarTerritorios(territorios, tamanho);
    definirCorJogador(corJogador, tamanhoCor);
    *missao = sortearMissao();
}

void exibirMapa(const Territorio territorios[], int tamanho) {
    printf("\n=== MAPA MUNDI ===\n");
    printf("%-12s %-12s %-8s\n", "Territorio", "Cor", "Tropas");
    printf("-------------------------------------\n");

    for (int i = 0; i < tamanho; i++) {
        printf("%-12s %-12s %-8d\n", territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }

    printf("-------------------------------------\n");
}

void exibirMenuPrincipal(void) {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int sortearMissao(void) {
    return (rand() % 2) + 1;
}

void exibirMissao(int missao, const char *corJogador) {
    printf("\n=== MISSAO SECRETA ===\n");

    if (missao == 1) {
        printf("Destruir o exercito %s\n", COR_INIMIGA);
    } else {
        printf("Conquistar 3 territorios da cor %s\n", corJogador);
    }
}

int contarTerritoriosComCor(const Territorio territorios[], int tamanho, const char *cor) {
    int total = 0;

    for (int i = 0; i < tamanho; i++) {
        if (strcmp(territorios[i].cor, cor) == 0) {
            total++;
        }
    }

    return total;
}

int verificarVitoria(const Territorio territorios[], int tamanho, int missao, const char *corJogador) {
    if (missao == 1) {
        return contarTerritoriosComCor(territorios, tamanho, COR_INIMIGA) == 0;
    }

    return contarTerritoriosComCor(territorios, tamanho, corJogador) >= 3;
}

void simularAtaque(Territorio territorios[], int tamanho, int origem, int destino, const char *corJogador) {
    if (origem < 0 || origem >= tamanho || destino < 0 || destino >= tamanho) {
        printf("Territorio invalido.\n");
        return;
    }

    if (origem == destino) {
        printf("O territorio atacante e o defensor precisam ser diferentes.\n");
        return;
    }

    if (strcmp(territorios[origem].cor, corJogador) != 0) {
        printf("Voce so pode atacar a partir de um territorio seu.\n");
        return;
    }

    if (strcmp(territorios[destino].cor, corJogador) == 0) {
        printf("Esse territorio ja pertence a voce.\n");
        return;
    }

    if (territorios[origem].tropas < 2) {
        printf("O territorio atacante precisa ter ao menos 2 tropas.\n");
        return;
    }

    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\nAtaque: %s -> %d\n", territorios[origem].nome, dadoAtaque);
    printf("Defesa: %s -> %d\n", territorios[destino].nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        territorios[destino].tropas--;

        if (territorios[destino].tropas <= 0) {
            territorios[destino].tropas = 1;
            snprintf(territorios[destino].cor, sizeof(territorios[destino].cor), "%s", corJogador);
            printf("Territorio conquistado!\n");
        } else {
            printf("O defensor perdeu 1 tropa.\n");
        }
    } else {
        territorios[origem].tropas--;
        printf("O ataque falhou e o atacante perdeu 1 tropa.\n");
    }
}

void faseDeAtaque(Territorio territorios[], int tamanho, const char *corJogador) {
    int origem;
    int destino;

    printf("\n=== FASE DE ATAQUE ===\n");

    printf("Escolha o territorio atacante (1-%d): ", tamanho);

    if (scanf("%d", &origem) != 1) {
        limparBufferEntrada();
        printf("Entrada invalida.\n");
        return;
    }

    printf("Escolha o territorio defensor (1-%d): ", tamanho);

    if (scanf("%d", &destino) != 1) {
        limparBufferEntrada();
        printf("Entrada invalida.\n");
        return;
    }

    limparBufferEntrada();
    simularAtaque(territorios, tamanho, origem - 1, destino - 1, corJogador);
}

void executarLoopPrincipal(Territorio territorios[], int tamanho, const char *corJogador, int missao) {
    int opcao = -1;

    printf("=== WAR ESTRUTURADO ===\n");
    printf("Seu exercito e o %s.\n", corJogador);

    while (opcao != 0) {
        exibirMapa(territorios, tamanho);
        exibirMissao(missao, corJogador);
        exibirMenuPrincipal();

        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            printf("Opcao invalida.\n");
            continue;
        }

        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(territorios, tamanho, corJogador);
                if (verificarVitoria(territorios, tamanho, missao, corJogador)) {
                    exibirMapa(territorios, tamanho);
                    printf("\nMissao cumprida. Voce venceu!\n");
                    opcao = 0;
                }
                break;
            case 2:
                if (verificarVitoria(territorios, tamanho, missao, corJogador)) {
                    printf("\nMissao cumprida. Voce venceu!\n");
                    opcao = 0;
                } else {
                    printf("\nA missao ainda nao foi cumprida.\n");
                }
                break;
            case 0:
                printf("\nSaindo do jogo.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
}

int main(void) {
    Territorio *territorios = calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    char corJogador[COR_MAX];
    int missao;

    if (territorios == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para os territorios.\n");
        return 1;
    }

    srand((unsigned)time(NULL));
    configurarJogo(territorios, TOTAL_TERRITORIOS, corJogador, sizeof(corJogador), &missao);
    executarLoopPrincipal(territorios, TOTAL_TERRITORIOS, corJogador, missao);

    free(territorios);
    return 0;
}