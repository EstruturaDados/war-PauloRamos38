# 🗺️ Desafio WAR Estruturado – Conquista de Territórios

Bem-vindo ao **Desafio WAR Estruturado!** Inspirado no famoso jogo de estratégia, este desafio convida você a programar diferentes versões do jogo WAR, evoluindo seus conhecimentos em **C** à medida que avança pelos níveis **Novato**, **Aventureiro** e **Mestre**.

A empresa **MateCheck** contratou você para criar uma versão estruturada do WAR. Cada nível propõe novas funcionalidades, conceitos e desafios de programação. **Você escolhe por onde começar!**

---

## 🧩 Nível Novato: Cadastro Inicial dos Territórios

### 🎯 Objetivo

- Criar uma `struct` chamada `Territorio`.
- Usar um **vetor estático de 5 elementos** para armazenar os territórios.
- Cadastrar os dados de cada território: **Nome**, **Cor do Exército**, e **Número de Tropas**.
- Exibir o estado atual do mapa.

### ⚙️ Funcionalidades

- Leitura de dados pelo terminal (`fgets` e `scanf`)
- Impressão organizada dos dados de todos os territórios

### 💡 Conceitos abordados

- `struct`
- Vetor estático
- Entrada/saída com `scanf`, `fgets`, e `printf`

### 📥 Entrada

O usuário digita o nome do território, a cor do exército dominante e o número de tropas para **cada um dos 5 territórios**.

### 📤 Saída



## 🧗‍♂️ Nível Aventureiro: Batalhas Estratégicas

### 🎯 Objetivo

- Substituir o vetor estático por **alocação dinâmica com `calloc`**
- Criar uma função para **simular ataques entre dois territórios**
- Utilizar números aleatórios para representar dados de batalha

### 🆕 Novidades em relação ao Nível Novato

- Alocação dinâmica de memória com `calloc`
- Uso de **ponteiros**
- Laço interativo para o jogador escolher **territórios para atacar e defender**
- Simulação de dados de ataque e defesa com `rand()`

### ⚙️ Funcionalidades

- Cadastro dos territórios (como no Nível Novato)
- Fase de ataque com:
  - Escolha de atacante e defensor
  - Dados de ataque/defesa
  - Lógica:
    - Se atacante vence → defensor perde 1 tropa
    - Se defensor perde todas → território é conquistado
    - Empates favorecem o atacante

### 💡 Conceitos abordados

- Ponteiros
- `calloc` / `free`
- Aleatoriedade com `rand()` / `srand()`
- Funções para modularização

### 📥 Entrada

- Território **atacante** (1 a 5)
- Território **defensor** (1 a 5)

### 📤 Saída

Exibição do resultado da batalha, dados sorteados e mudanças no mapa.



## 🧠 Nível Mestre: Missões e Modularização Total

### 🎯 Objetivo

- Dividir o código em funções bem definidas
- Implementar um **sistema de missões**
- Verificar cumprimento da missão
- Aplicar **boas práticas** (uso de `const`, modularização, etc.)

### 🆕 Diferenças em relação ao Nível Aventureiro

- Modularização total em funções
- Missões aleatórias atribuídas:
  1. Destruir o exército **Verde**
  2. Conquistar **3 territórios**
- Menu interativo com opções

### ⚙️ Funcionalidades

- Inicialização automática dos territórios
- Menu principal com 3 opções:
  1. Atacar
  2. Verificar Missão
  3. Sair
- Verificação de vitória da missão

### 💡 Conceitos abordados

- Modularização
- `const` correctness
- Estruturação em múltiplas funções
- Passagem por referência

### 📥 Entrada

- Ações do jogador via menu:
  - `1` - Atacar
  - `2` - Verificar Missão
  - `0` - Sair
- Escolha de territórios para ataque

### 📤 Saída

- Mapa atualizado
- Resultados das batalhas
- Verificação da missão
- Mensagem de vitória



## 🏁 Conclusão

Com este **Desafio WAR Estruturado**, você praticará fundamentos essenciais da linguagem **C** de forma **divertida e progressiva**.

Cada nível foca em um conjunto de habilidades:

- 🟢 **Novato**: `struct`, vetor, entrada/saída
- 🔵 **Aventureiro**: ponteiros, memória dinâmica, lógica de jogo
- 🟣 **Mestre**: modularização, design limpo, sistema de missões



🚀 **Boa sorte! Avance nos níveis e torne-se um mestre da programação estratégica!**

> Equipe de Ensino – MateCheck

// ================================ // Desafio: Nível Aventureiro // Projeto: Cadastro de Territórios (War) // Autor: Paulo Ramos // ================================
// Blibioteca//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes Globais ---
#define MAX_NOME 30
#define MAX_COR 10
//Struct//
// --- Estrutura de Dados --- 
//Cria o “modelo” dos territórios:

nome
cor
tropas//
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
//main()//
int main() {

    int quantidade;
    int atacante;
    int defensor;

    srand(time(NULL));

    printf("Digite a quantidade de territorios: ");
    scanf("%d", &quantidade);

    Territorio* mapa = alocarMapa(quantidade);

    cadastrarTerritorios(mapa, quantidade);

    exibirTerritorios(mapa, quantidade);

    printf("\nEscolha o territorio atacante: ");
    scanf("%d", &atacante);

    printf("Escolha o territorio defensor: ");
    scanf("%d", &defensor);

    atacar(&mapa[atacante - 1], &mapa[defensor - 1]);

    printf("\n=== MAPA ATUALIZADO ===\n");

    exibirTerritorios(mapa, quantidade);

    liberarMemoria(mapa);

    return 0;
}
//srand(time(NULL))//
//Inicializa números aleatórios diferentes.//
//Usuário escolhe quantos territórios existirão.//
scanf("%d", &quantidade);
//Agora o mapa usa ponteiros.//
Territorio* mapa
//Cria memória dinamicamente usando calloc.//
//alocarMapa(quantidade)
Envia os territórios para batalha.

O & significa:

enviar endereço de memória
usar ponteiros//
atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
//cria memória dinâmica.//
Territorio* alocarMapa(int quantidade) {

    Territorio* mapa;

    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    if(mapa == NULL) {

        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    return mapa;
}
//descobre tamanho da struct.//
sizeof(Territorio)
//devolve o ponteiro do vetor.//
return mapa;
//Agora usa ponteiros. Cadastro//
void cadastrarTerritorios(Territorio* mapa, int quantidade)
//Função alocarMapa
Na implementação://
Territorio* alocarMapa(int quantidade) {

    Territorio* mapa;

    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    if(mapa == NULL) {

        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    return mapa;
}
//Cadastro e Agora usa ponteiros.//
void cadastrarTerritorios(Territorio* mapa, int quantidade)
//const garante:

apenas leitura
sem modificar dados//
void exibirTerritorios(const Territorio* mapa, int quantidade)
//Essa função:

sorteia dados
compara valores
reduz tropas
conquista territórios//
void atacar(Territorio* atacante, Territorio* defensor)
//Gera número:

de 1 até 6

simulando dado.//
rand() % 6 + 1
//Verifica se pertencem ao mesmo exército.//
strcmp(atacante->cor, defensor->cor)
A seta acessa campos da struct via ponteiro.

14. Liberação de memória
free(mapa);

ou:

liberarMemoria(mapa);

Evita vazamento de memória.

15. Final do Codespace

Depois:

salvar
testar
terminal:
git add .
git commit -m "Implementa nivel aventureiro"
git push

Isso mantém o repositório atualizado corretamente.

não, eu falo // explicando cada ação que fazemos// acrescentar isso.
como abro o codespace para acrescentar esse codigo como continuação do mesmo projeto?

Para continuar o mesmo projeto no Codespace, faça assim:

Entre no GitHub
Abra o repositório do projeto WAR.
Clique no botão verde:
Code
Vá na aba:
Codespaces
Você verá:
o Codespace já criado
ou a opção “Create codespace on main”

Se o projeto já existe:

clique em:
Resume

Isso reabre exatamente o mesmo ambiente com seus arquivos.

Depois:

Abrir o arquivo .c

Na lateral esquerda:

clique no arquivo do projeto
normalmente:
main.c

ou:

war.c
Acrescentar comentários explicando as ações

Agora entendi sua dúvida.

Você quer colocar comentários como:

// Inicializa os números aleatórios do jogo
srand(time(NULL));

Isso é correto e o README pede:

“Comentar o código explicando cada função e trecho importante.”

Então você DEVE acrescentar comentários explicativos.

Exemplo correto:

// Solicita ao usuário a quantidade de territórios
printf("Digite a quantidade de territorios: ");
scanf("%d", &quantidade);

Outro:

// Aloca dinamicamente memória para os territórios
Territorio* mapa = alocarMapa(quantidade);

Outro:

// Simula um dado de batalha de 1 até 6
dadoAtaque = rand() % 6 + 1;

Outro:

// Libera a memória alocada dinamicamente
free(mapa);

Então no aventureiro:

você NÃO só programa
você também explica as ações importantes com // comentários

Isso deixa o projeto fiel ao enunciado e mais profissional.

tem um espaço com o nome current branch, miniature computing maxine, é esse que eu clico?

Sim, provavelmente é esse mesmo.

No Codespaces, às vezes aparece algo como:

Current Branch

e abaixo um nome automático parecido com:

miniature-computing-maxine

Esse nome estranho é apenas o nome do seu Codespace.

Você pode clicar nele para reabrir/continuar o ambiente do projeto.

O fluxo geralmente é:

GitHub
Repositório
Code
Codespaces
Clique no Codespace existente
(ex.: miniature-computing-maxine)

Depois disso:

o VS Code web abrirá
seus arquivos voltarão
você continua exatamente do ponto onde parou




