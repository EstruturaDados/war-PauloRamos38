// ========================================
// PROGRAMA: GUERRA - DOMINE TERRITÓRIOS
// ========================================

// --- Bibliotecas ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_NOME 30
#define MAX_COR 10

// --- Estrutura de Dados ---
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---

// Funções de setup e gerenciamento de memória:
Territorio* alocarMapa(int quantidade);
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void liberarMemoria(Territorio* mapa);

// Funções de interface com o usuário:
void exibirTerritorios(const Territorio* mapa, int quantidade);

// Funções de lógica principal do jogo:
int atacar(Territorio* atacante, Territorio* defensor);

// Função utilitária:
void limparBufferEntrada();

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
// Agora usa ponteiros
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor do territorio: ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite o numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// Exibe os territórios na tela
// O const garante apenas leitura, sem modificar dados
void exibirTerritorios(const Territorio* mapa, int quantidade) {
    printf("\n=== MAPA MUNDIAL ===\n");
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

    printf("\n=== BATALHA ===\n");
    printf("Atacante: %s (%s) com %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n\n", defensor->nome, defensor->cor, defensor->tropas);

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
        atacante->tropas++;
        defensor->tropas--;

        // Conquista o territorio se defensor não tiver mais tropas
        if (defensor->tropas <= 0) {
            printf("\n*** TERRITORIO CONQUISTADO! ***\n");
            printf("Novo dono: %s (Exercito %s)\n", atacante->nome, atacante->cor);
            // A seta (->) acessa campos da struct via ponteiro
            // Significa: (*defensor).cor
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }
        printf("==========================================\n");
        return 1;
    } else if (dadoDefensor > dadoAtacante) {
        printf("RESULTADO: VITORIA DO DEFENSOR!\n");
        atacante->tropas--;
        printf("==========================================\n");
        return -1;
    } else {
        printf("RESULTADO: EMPATE!\n");
        printf("Nenhuma tropa eh perdida.\n");
        printf("==========================================\n");
        return 0;
    }
}

// Libera memória dinâmica
// free(mapa) ou liberarMemoria(mapa)
// Evita vazamento de memória
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}

// ========================================
// FUNÇÃO PRINCIPAL
// ========================================

int main() {
    int quantidade;
    int atacante;
    int defensor;
    Territorio* mapa;

    setvbuf(stdout, NULL, _IONBF, 0);
    srand(1);

    printf("========================================\n");
    printf("   BEM-VINDO AO JOGO DA GUERRA!\n");
    printf("========================================\n");

    // Solicita quantidade de territórios
    printf("\nQuantos territorios deseja criar? ");
    scanf("%d", &quantidade);
    limparBufferEntrada();

    // Aloca memória para o mapa
    mapa = alocarMapa(quantidade);

    // Cadastra os territórios
    cadastrarTerritorios(mapa, quantidade);

    int continuar = 1;

    // Loop principal do jogo
    while (continuar == 1) {

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
        continue;
    }

    // Impede ataque ao mesmo territorio
    if (atacante == defensor) {

        printf("Erro: Escolha territorios diferentes!\n");
        continue;
    }

    // Realiza o ataque usando ponteiros
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

    // Pergunta se o jogador deseja continuar
    printf("\nDeseja continuar jogando?");
    printf("\n1 - Sim");
    printf("\n0 - Nao");
    printf("\nOpcao: ");

    scanf("%d", &continuar);
    limparBufferEntrada();
}

// Libera a memória alocada dinamicamente
liberarMemoria(mapa);
mapa = NULL;

printf("\nJogo finalizado. Memoria liberada.\n");

return 0;
}