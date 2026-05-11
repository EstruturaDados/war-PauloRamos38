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
void atacar(Territorio* atacante, Territorio* defensor);

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
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante, dadoDefensor;

    printf("\n=== BATALHA ===\n");
    printf("Atacante: %s (%s) com %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n\n", defensor->nome, defensor->cor, defensor->tropas);

    // strcmp verifica se pertencem ao mesmo exército
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Territorios pertencem ao mesmo exercito!\n");
        return;
    }

    // Verifica se o atacante tem tropas suficientes
    if (atacante->tropas <= 0) {
        printf("Erro: O atacante nao possui tropas!\n");
        return;
    }

    // Sorteia dados (números aleatórios de 1 até 6)
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("Dado do Atacante: %d\n", dadoAtacante);
    printf("Dado do Defensor: %d\n\n", dadoDefensor);

    // Compara valores
    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        atacante->tropas++;
        defensor->tropas--;

        // Conquista o territorio se defensor não tiver mais tropas
        if (defensor->tropas <= 0) {
            printf("\n*** TERRITORIO CONQUISTADO! ***\n");
            // A seta (->) acessa campos da struct via ponteiro
            // Significa: (*defensor).cor
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }
    } else if (dadoDefensor > dadoAtacante) {
        printf("Defensor venceu!\n");
        atacante->tropas--;
    } else {
        printf("Empate! Nenhuma tropa eh perdida.\n");
    }
}

// Libera memória dinâmica
// free(mapa) ou liberarMemoria(mapa)
// Evita vazamento de memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ========================================
// FUNÇÃO PRINCIPAL
// ========================================

int main() {
    int quantidade;
    int atacante;
    int defensor;

    // srand(time(NULL)) inicializa números aleatórios diferentes
    srand(time(NULL));

    printf("========================================\n");
    printf("   BEM-VINDO AO JOGO DA GUERRA!\n");
    printf("========================================\n");

    // Usuário escolhe quantos territórios existirão
       // Loop até receber uma quantidade válida
       do {
           printf("\nDigite a quantidade de territorios (maior que 0): ");
           scanf("%d", &quantidade);
           limparBufferEntrada();

           if (quantidade <= 0) {
               printf("Erro: Quantidade deve ser maior que zero!\n");
           }
       } while (quantidade <= 0);

    // Territorio* mapa
    // Agora o mapa usa ponteiros
    Territorio* mapa = alocarMapa(quantidade);

    cadastrarTerritorios(mapa, quantidade);

    exibirTerritorios(mapa, quantidade);

    printf("\nEscolha o territorio atacante (numero): ");
    scanf("%d", &atacante);
    limparBufferEntrada();

    printf("Escolha o territorio defensor (numero): ");
    scanf("%d", &defensor);
    limparBufferEntrada();

    // Valida entrada
    if (atacante < 1 || atacante > quantidade || defensor < 1 || defensor > quantidade) {
        printf("Erro: Territorio invalido!\n");
        liberarMemoria(mapa);
        return 0;
    }

    if (atacante == defensor) {
        printf("Erro: Atacante e defensor nao podem ser o mesmo territorio!\n");
        liberarMemoria(mapa);
        return 0;
    }

    // atacar(&mapa[atacante - 1], &mapa[defensor - 1])
    // Envia os territórios para batalha
    // O & significa: enviar endereço de memória, usar ponteiros
    atacar(&mapa[atacante - 1], &mapa[defensor - 1]);

    printf("\n=== MAPA ATUALIZADO ===\n");

    exibirTerritorios(mapa, quantidade);

    liberarMemoria(mapa);

    printf("\nJogo finalizado. Memoria liberada.\n");

    return 0;
}