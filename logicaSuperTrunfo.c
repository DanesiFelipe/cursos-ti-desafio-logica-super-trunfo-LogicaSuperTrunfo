// Simulador de batalha entre territórios
// Implementa alocação dinâmica, ponteiros e ataque com dados aleatórios

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct Territorio conforme especificação
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Lê uma linha do stdin e remove o '\n' ao final, se existir
static void lerLinha(char* buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

// Lê uma string com prompt, utilizando ponteiro para armazenar
static void lerString(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);
    lerLinha(buffer, size);
}

// Lê um inteiro no intervalo [min, max]
static int lerInteiro(const char* prompt, int min, int max) {
    char linha[64];
    while (1) {
        printf("%s", prompt);
        lerLinha(linha, sizeof(linha));
        char* endptr = NULL;
        long v = strtol(linha, &endptr, 10);
        if (endptr == linha || *endptr != '\0') {
            printf("Entrada inválida. Digite um número.\n");
            continue;
        }
        if (v < min || v > max) {
            printf("Valor fora do intervalo (%d a %d).\n", min, max);
            continue;
        }
        return (int)v;
    }
}

// Cadastra territórios no vetor apontado por 'mapa'
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        Territorio* t = &mapa[i];
        printf("\n=== Cadastro do território %d ===\n", i);
        lerString("Nome: ", t->nome, sizeof(t->nome));
        lerString("Cor (ex.: vermelho, azul): ", t->cor, sizeof(t->cor));
        t->tropas = lerInteiro("Tropas iniciais: ", 0, 1000000);
    }
}

// Exibe todos os territórios (somente leitura)
void exibirTerritorios(const Territorio* mapa, int n) {
    printf("\n--- Territórios ---\n");
    for (int i = 0; i < n; i++) {
        const Territorio* t = &mapa[i];
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, t->nome, t->cor, t->tropas);
    }
}

// Escolhe um índice válido de território com prompt
int escolherIndice(const Territorio* mapa, int n, const char* prompt) {
    exibirTerritorios(mapa, n);
    return lerInteiro(prompt, 0, n - 1);
}

// Simula um ataque entre atacante e defensor usando rolagem de dados
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nRolagens: atacante = %d, defensor = %d\n", dadoAtacante, dadoDefensor);

    // Defensor vence em caso de empate para tornar a disputa mais equilibrada
    if (dadoAtacante > dadoDefensor) {
        int movidas = atacante->tropas / 2;
        if (movidas < 0) movidas = 0;

        // Atualização dos campos: transfere a cor e metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = movidas;

        // Tropas remanescentes ficam no território atacante
        atacante->tropas -= movidas;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("Vitória do atacante! %s conquistou %s.\n", atacante->nome, defensor->nome);
        printf("Metade das tropas (%d) se moveram para o território conquistado.\n", movidas);
    } else {
        // Derrota do atacante: perde uma tropa
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
        printf("Defensor resistiu ao ataque. %s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Libera a memória alocada para o mapa
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main(void) {
    // Inicializa gerador de números aleatórios
    srand((unsigned int)time(NULL));

    printf("Simulador de batalha entre territórios\n");

    // Alocação dinâmica do vetor de territórios
    int n = lerInteiro("Informe o número total de territórios: ", 1, 1000);
    Territorio* mapa = (Territorio*)calloc((size_t)n, sizeof(Territorio));
    if (!mapa) {
        fprintf(stderr, "Falha ao alocar memória para os territórios.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    // Loop de ataques
    while (1) {
        printf("\nDeseja realizar um ataque? (s/n): ");
        char resposta[8];
        lerLinha(resposta, sizeof(resposta));
        if (resposta[0] == 'n' || resposta[0] == 'N') {
            break;
        }
        if (resposta[0] != 's' && resposta[0] != 'S') {
            printf("Resposta inválida. Use 's' para sim ou 'n' para não.\n");
            continue;
        }

        int idxAtacante = escolherIndice(mapa, n, "Escolha o índice do território atacante: ");
        int idxDefensor = escolherIndice(mapa, n, "Escolha o índice do território defensor: ");

        if (idxAtacante == idxDefensor) {
            printf("O atacante e o defensor devem ser territórios diferentes.\n");
            continue;
        }

        Territorio* atacante = &mapa[idxAtacante];
        Territorio* defensor = &mapa[idxDefensor];

        // Valida que não é possível atacar território da mesma cor
        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Não é permitido atacar um território da mesma cor (%s).\n", atacante->cor);
            continue;
        }

        // Executa a simulação de ataque
        atacar(atacante, defensor);

        // Exibição pós-ataque
        exibirTerritorios(mapa, n);
    }

    liberarMemoria(mapa);
    printf("\nMemória liberada. Encerrando o programa.\n");
    return 0;
}
