// ========================================
// PROGRAMA: GUERRA - DOMINE TERRITÓRIOS
// ========================================

// --- Bibliotecas ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define MAX_NOME 30
#define MAX_COR 10
#define MAX_MISSAO 100
#define TOTAL_TERRITORIOS 5
#define TOTAL_MISSOES 5

// --- Estrutura de Dados ---
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---

// Funções de setup e gerenciamento de memória:
// Aloca dinamicamente um vetor de territórios usando calloc
Territorio* alocarMapa(int quantidade);
// Lê e armazena informações de cada território (nome, cor, tropas)
void cadastrarTerritorios(Territorio* mapa, int quantidade);
// Libera toda memória alocada dinamicamente com free()
void liberarMemoria(Territorio* mapa);

// Funções de interface com o usuário:
// Exibe a tabela de territórios com seus dados atualizados
void exibirTerritorios(const Territorio* mapa, int quantidade);

// Funções de lógica principal do jogo:
// Simula um ataque com dados (1-6), transfere cor e tropas entre territórios
int atacar(Territorio* atacante, Territorio* defensor);

// Função utilitária:
void limparBufferEntrada();

// Funções de missões
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(char* missao);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);

// Funções do menu
void exibirMenu();

// ========================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ========================================

// Aloca memória dinâmica para o mapa de territórios
Territorio* alocarMapa(int quantidade) {
    Territorio* mapa;

    // calloc cria memória dinâmica
    // sizeof(Territorio) descobre tamanho da struct
    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    if(mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    // retorna o ponteiro do vetor
    return mapa;
}

// Limpa o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Limpa o buffer
    }
}

// Cadastra informações dos territórios
// Agora usa um mapa inicial pré-definido
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    const char* nomesPadrao[TOTAL_TERRITORIOS] = {
        "america",
        "Europa",
        "asia",
        "Africa",
        "Oceania"
    };

    const char* coresPadrao[TOTAL_TERRITORIOS] = {
        "verde",
        "Azul",
        "vermelho",
        "amarelo",
        "branco"
    };

    const int tropasPadrao[TOTAL_TERRITORIOS] = {5, 2, 2, 4, 1};

    for (int i = 0; i < quantidade; i++) {
        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);
        strcpy(mapa[i].nome, nomesPadrao[i]);
        strcpy(mapa[i].cor, coresPadrao[i]);
        mapa[i].tropas = tropasPadrao[i];

        printf("%d-%s (exercito %s, tropa %d)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Exibe os territórios na tela
// O const garante apenas leitura, sem modificar dados
void exibirTerritorios(const Territorio* mapa, int quantidade) {
    printf("\n=== MAPA DO MUNDO ===\n");
    printf("%-15s %-15s %-10s\n", "Territorio", "Cor", "Tropas");
    printf("==========================================\n");

    for (int i = 0; i < quantidade; i++) {
        printf("%-15s %-15s %-10d\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    printf("==========================================\n");
}

// Simula um ataque entre dois territórios
int atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    int tropasAtacanteAntes;
    int tropasDefensorAntes;

    printf("\n=== BATALHA ===\n");
    printf("Atacante: %s (%s) com %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n\n", defensor->nome, defensor->cor, defensor->tropas);

    tropasAtacanteAntes = atacante->tropas;
    tropasDefensorAntes = defensor->tropas;

    // strcmp verifica se pertencem ao mesmo exército
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Territorios pertencem ao mesmo exercito!\n");
        return 0;
    }

    // Verifica se o atacante tem tropas suficientes
    if (atacante->tropas <= 0) {
        printf("Erro: O atacante nao possui tropas!\n");
        return 0;
    }

    // Sorteia dados (números aleatórios de 1 até 6)
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("Dado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n", dadoDefensor);
    printf("==========================================\n");

    // Compara valores
    if (dadoAtacante > dadoDefensor) {
        printf("RESULTADO: VITORIA DO ATACANTE!\n");
        
        // Transfere metade das tropas do defensor para o atacante
        int tropasTransferidas = defensor->tropas / 2;
        if (tropasTransferidas < 1) {
            tropasTransferidas = 1;
        }
        if (tropasTransferidas > defensor->tropas) {
            tropasTransferidas = defensor->tropas;
        }
        atacante->tropas += tropasTransferidas;
        defensor->tropas -= tropasTransferidas;

        // Conquista o territorio se defensor não tiver mais tropas
        if (defensor->tropas <= 0) {
            printf("\n*** TERRITORIO CONQUISTADO! ***\n");
            printf("Novo dono: %s (Exercito %s)\n", atacante->nome, atacante->cor);
            // A seta (->) acessa campos da struct via ponteiro
            // Significa: (*defensor).cor
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }

        printf("Tropas atualizadas: %s %d -> %d | %s %d -> %d\n",
               atacante->nome, tropasAtacanteAntes, atacante->tropas,
               defensor->nome, tropasDefensorAntes, defensor->tropas);
        printf("==========================================\n");
        return 1;
    } else if (dadoDefensor > dadoAtacante) {
        printf("RESULTADO: VITORIA DO DEFENSOR!\n");
        // Atacante perde uma tropa
        atacante->tropas--;
        printf("Atacante perdeu 1 tropa. Tropas restantes: %d\n", atacante->tropas);
        printf("Tropas atualizadas: %s %d -> %d | %s %d -> %d\n",
               atacante->nome, tropasAtacanteAntes, atacante->tropas,
               defensor->nome, tropasDefensorAntes, defensor->tropas);
        printf("==========================================\n");
        return -1;
    } else {
        printf("RESULTADO: EMPATE!\n");
        printf("Nenhuma tropa eh perdida. Batalha desfeita.\n");
        printf("Tropas mantidas: %s %d | %s %d\n",
               atacante->nome, atacante->tropas,
               defensor->nome, defensor->tropas);
        printf("==========================================\n");
        return 0;
    }
}

// Libera memória dinâmica alocada para o mapa de territórios
// Evita vazamentos de memória usando free()
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa); // Desaloca o bloco de memória
        mapa = NULL; // Define para NULL após liberar (boa prática)
    }
}

// Atribui uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão do jogador
void exibirMissao(char* missao) {
    printf("\n=== MISSAO DO JOGADOR ===\n");
    printf("Missao: %s\n", missao);
    printf("============================\n");
}

// Verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    int i;

    // Conta quantos territórios cada cor domina e mede o maior domínio do mapa
    int maiorDomino = 0;
    for (i = 0; i < tamanho; i++) {
        int contagemAtual = 0;

        for (int j = 0; j < tamanho; j++) {
            if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                contagemAtual++;
            }
        }

        if (contagemAtual > maiorDomino) {
            maiorDomino = contagemAtual;
        }
    }

    // Verificar "Conquistar 3 territorios"
    if (strstr(missao, "Conquistar 3")) {
        return maiorDomino >= 3;
    }

    // Verificar "Conquistar 5 territorios"
    if (strstr(missao, "Conquistar 5")) {
        return maiorDomino >= 5;
    }

    // Verificar "Eliminar o exercito vermelho"
    if (strstr(missao, "vermelho")) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) {
                return 0;
            }
        }
        return 1;
    }

    // Verificar "Eliminar o exercito azul"
    if (strstr(missao, "azul")) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0 || strcmp(mapa[i].cor, "azul") == 0) {
                return 0;
            }
        }
        return 1;
    }
    
    // Verificar "Dominar metade do mapa"
    if (strstr(missao, "metade")) {
        return maiorDomino > tamanho / 2; // Mais de 50%
    }
    
    return 0; // Missão não cumprida
}

// Exibe o menu de opções
void exibirMenu() {
    printf("\n=== MENU ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("3 - Sair\n");
    printf("Escolha uma opcao: ");
}

// ========================================
// FUNÇÃO PRINCIPAL
// ========================================

int main() {
    int quantidade;
    int atacante;
    int defensor;
    Territorio* mapa;
    int opcao = 0;
    int venceu = 0;

    // Vetor de missões
    char* missoes[TOTAL_MISSOES] = {
        "Conquistar 3 territorios",
        "Eliminar o exercito vermelho",
        "Eliminar o exercito azul",
        "Conquistar 5 territorios",
        "Dominar metade do mapa"
    };

    // Missão dinâmica do jogador
    char* missaoJogador;
    missaoJogador = (char*) malloc(MAX_MISSAO * sizeof(char));

    setvbuf(stdout, NULL, _IONBF, 0);
    // Inicializa o gerador de números aleatórios com o tempo atual
    srand(time(NULL));

    printf("========================================\n");
    printf("   BEM-VINDO AO JOGO DA GUERRA!\n");
    printf("========================================\n");

    // O mapa já vem pré-cadastrado com territórios iniciais
    quantidade = TOTAL_TERRITORIOS;

    // Aloca memória para o mapa
    mapa = alocarMapa(quantidade);

    // Cadastra os territórios
    cadastrarTerritorios(mapa, quantidade);

    // Sorteia a missão do jogador
    atribuirMissao(missaoJogador, missoes, TOTAL_MISSOES);

    // Exibe a missão apenas no início
    exibirMissao(missaoJogador);

    // Loop principal do jogo
    while (opcao != 3 && venceu == 0) {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1: {
            printf("\n=== MAPA ATUAL ===\n");
            exibirTerritorios(mapa, quantidade);

            printf("\nEscolha o territorio atacante (numero): ");
            scanf("%d", &atacante);
            limparBufferEntrada();

            printf("Escolha o territorio defensor (numero): ");
            scanf("%d", &defensor);
            limparBufferEntrada();

            // Valida entrada
            if (atacante < 1 || atacante > quantidade ||
                defensor < 1 || defensor > quantidade) {
                printf("Erro: Territorio invalido!\n");
                break;
            }

            // Impede ataque ao mesmo territorio
            if (atacante == defensor) {
                printf("Erro: Escolha territorios diferentes!\n");
                break;
            }

            // Realiza batalha
            int resultadoBatalha = atacar(&mapa[atacante - 1], &mapa[defensor - 1]);

            if (resultadoBatalha == 1) {
                printf("\nVENCEDOR: %s (Exercito %s)\n", mapa[atacante - 1].nome, mapa[atacante - 1].cor);
            } else if (resultadoBatalha == -1) {
                printf("\nVENCEDOR: %s (Exercito %s)\n", mapa[defensor - 1].nome, mapa[defensor - 1].cor);
            } else {
                printf("\nSEM VENCEDOR: EMPATE OU ERRO\n");
            }

            printf("\n=== MAPA ATUALIZADO ===\n");
                exibirTerritorios(mapa, quantidade);

                // Verifica vitória silenciosamente
                venceu = verificarMissao(missaoJogador, mapa, quantidade);

                if (venceu == 1) {
                    printf("\nMISSAO CUMPRIDA!\n");
                    printf("VOCE VENCEU O JOGO!\n");
                    opcao = 3;
                }

                break;
            }
            case 2:
                printf("\n=== SUA MISSAO ===\n");
                printf("%s\n", missaoJogador);

                venceu = verificarMissao(missaoJogador, mapa, quantidade);
                if (venceu == 1) {
                    printf("\nMISSAO CUMPRIDA!\n");
                    printf("VOCE VENCEU O JOGO!\n");
                    opcao = 3;
                } else {
                    printf("\nMissao ainda nao cumprida.\n");
                }
                break;

            case 3:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    }

    // Libera toda a memória alocada dinamicamente para evitar vazamentos
    liberarMemoria(mapa);
    mapa = NULL; // Zera o ponteiro após liberar

    // Libera memória da missão armazenada dinamicamente
    free(missaoJogador);
    missaoJogador = NULL; // Zera o ponteiro após liberar

    printf("\nJogo finalizado. Memoria liberada.\n");

    return 0;
}