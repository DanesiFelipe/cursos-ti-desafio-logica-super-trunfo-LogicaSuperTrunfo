#include <stdio.h>
#include <string.h>

// Desafio Super Trunfo - Países
// Sistema de comparação de cartas de cidades
// Versão melhorada com validações e cálculos normalizados

int main() {
    // Declaração das variáveis
    char codigo1[20] = "A01", codigo2[20] = "B02";
    char cidade1[30] = "São Paulo (SP)", cidade2[30] = "Rio de Janeiro (RJ)";
    int populacao1 = 12325000, populacao2 = 6748000;
    float area1 = 1521.11, area2 = 1200.25;
    float pib1 = 699.28, pib2 = 300.50;
    int ponto1 = 50, ponto2 = 30;
    char estado1 = 'A', estado2 = 'B';
    float densidade1, densidade2;
    float capita1, capita2;
    float super1, super2;
    int escolha;

    // Validação dos dados de entrada
    if (populacao1 <= 0 || populacao2 <= 0) {
        printf("Erro: População deve ser maior que zero!\n");
        return 1;
    }

    if (area1 <= 0 || area2 <= 0) {
        printf("Erro: Área deve ser maior que zero!\n");
        return 1;
    }

    if (pib1 < 0 || pib2 < 0) {
        printf("Erro: PIB não pode ser negativo!\n");
        return 1;
    }

    if (ponto1 < 0 || ponto2 < 0) {
        printf("Erro: Número de pontos turísticos não pode ser negativo!\n");
        return 1;
    }

    // Cálculos
    densidade1 = (float)populacao1 / area1;
    densidade2 = (float)populacao2 / area2;

    // PIB per capita em milhares de reais
    capita1 = (pib1 * 1000000000.0) / populacao1;
    capita2 = (pib2 * 1000000000.0) / populacao2;

    // Cálculo normalizado do Super Poder
    // Cada componente é normalizado para uma escala de 0-100 antes da soma
    super1 = (float)populacao1/1000000 + // população em milhões (max ~12)
             area1/20 +                   // área em km² (max ~2000)
             pib1/7 +                     // PIB em bilhões (max ~700)
             ponto1 +                     // pontos turísticos (max ~100)
             densidade1/100 +             // densidade (max ~10000)
             capita1/1000;                // PIB per capita em milhares (max ~100000)

    super2 = (float)populacao2/1000000 +
             area2/20 +
             pib2/7 +
             ponto2 +
             densidade2/100 +
             capita2/1000;

    // Exibição dos dados da carta 1
    printf("\n-----------------------------Carta 1----------------------------- \n");
    printf("Estado: %c \n", estado1);
    printf("Codigo: %s \n", codigo1); 
    printf("Nome da cidade: %s \n", cidade1);
    printf("População: %d de habitantes \n", populacao1); 
    printf("Área: %.2f km² \n", area1);
    printf("PIB: %.2f bilhoes \n", pib1); 
    printf("Número de pontos Turisticos: %d \n", ponto1);
    printf("Densidade Populacional: %.2f Hab/km²\n", densidade1);
    printf("PIB per Capita: %.2f reais\n", capita1);
    printf("Super Poder: %.2f\n", super1);
    
    // Exibição dos dados da carta 2
    printf("\n-----------------------------Carta 2----------------------------- \n");
    printf("Estado: %c \n", estado2);
    printf("Codigo: %s \n", codigo2); 
    printf("Nome da cidade: %s \n", cidade2);
    printf("População: %d de habitantes \n", populacao2); 
    printf("Área: %.2f km² \n", area2);
    printf("PIB: %.2f bilhoes \n", pib2); 
    printf("Número de pontos Turisticos: %d \n", ponto2);
    printf("Densidade Populacional: %.2f Hab/km²\n", densidade2);
    printf("PIB per Capita: %.2f reais.\n", capita2);
    printf("Super Poder: %.2f\n", super2);

    // Escolher atributo a ser comparado
    printf("Escolha o atributo a ser comparado:\n");
    printf("----------------------------------------\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Número de pontos turísticos\n");
    printf("5 - Densidade Populacional\n");
    printf("6 - PIB per capita\n");
    printf("7 - Super poder\n");
    printf("----------------------------------------\n");
    printf("Digite sua escolha (1-7): ");
    scanf("%d", &escolha);

    if (escolha < 1 || escolha > 7) {
        printf("\nOpção inválida! Por favor, escolha um número entre 1 e 7.\n");
        return 1;
    }

    printf("\n========== RESULTADO DA BATALHA ==========\n");

    switch (escolha) {
        case 1:
            printf("Comparando população:\n");
            printf("Carta 1 (%s): %d habitantes\n", cidade1, populacao1);
            printf("Carta 2 (%s): %d habitantes\n", cidade2, populacao2);
            if (populacao1 > populacao2) {
                printf("\nCarta 1 venceu! 🏆\n");
            } else if (populacao2 > populacao1) {
                printf("\nCarta 2 venceu! 🏆\n");
            } else {
                printf("\nEmpate!\n");
            }
            break;

        case 2:
            printf("Comparando área:\n");
            printf("Carta 1 (%s): %.2f km²\n", cidade1, area1);
            printf("Carta 2 (%s): %.2f km²\n", cidade2, area2);
            if (area1 > area2) {
                printf("\nCarta 1 venceu! 🏆\n");
            } else if (area2 > area1) {
                printf("\nCarta 2 venceu! 🏆\n");
            } else {
                printf("\nEmpate!\n");
            }
            break;

        case 3:
            printf("Comparando PIB:\n");
            printf("Carta 1 (%s): %.2f bilhões\n", cidade1, pib1);
            printf("Carta 2 (%s): %.2f bilhões\n", cidade2, pib2);
            if (pib1 > pib2) {
                printf("\nCarta 1 venceu! 🏆\n");
            } else if (pib2 > pib1) {
                printf("\nCarta 2 venceu! 🏆\n");
            } else {
                printf("\nEmpate!\n");
            }
            break;

        case 4:
            printf("Comparando Pontos Turísticos:\n");
            printf("Carta 1 (%s): %d pontos\n", cidade1, ponto1);
            printf("Carta 2 (%s): %d pontos\n", cidade2, ponto2);
            if (ponto1 > ponto2) {
                printf("\nCarta 1 venceu! 🏆\n");
            } else if (ponto2 > ponto1) {
                printf("\nCarta 2 venceu! 🏆\n");
            } else {
                printf("\nEmpate!\n");
            }
            break;

        case 5:
            printf("Comparando densidade populacional:\n");
            printf("Carta 1 (%s): %.2f Hab/km²\n", cidade1, densidade1);
            printf("Carta 2 (%s): %.2f Hab/km²\n", cidade2, densidade2);
            if (densidade1 < densidade2) {
                printf("\nCarta 1 venceu! 🏆\n");
            } else if (densidade2 < densidade1) {
                printf("\nCarta 2 venceu! 🏆\n");
            } else {
                printf("\nEmpate!\n");
            }
            break;

        case 6:
            printf("Comparando PIB per capita:\n");
            printf("Carta 1 (%s): %.2f reais\n", cidade1, capita1);
            printf("Carta 2 (%s): %.2f reais\n", cidade2, capita2);
            if (capita1 > capita2) {
                printf("\nCarta 1 venceu! 🏆\n");
            } else if (capita2 > capita1) {
                printf("\nCarta 2 venceu! 🏆\n");
            } else {
                printf("\nEmpate!\n");
            }
            break;

        case 7:
            printf("Comparando Super poder:\n");
            printf("Carta 1 (%s): %.2f pontos\n", cidade1, super1);
            printf("Carta 2 (%s): %.2f pontos\n", cidade2, super2);
            if (super1 > super2) {
                printf("\nCarta 1 venceu! 🏆\n");
            } else if (super2 > super1) {
                printf("\nCarta 2 venceu! 🏆\n");
            } else {
                printf("\nEmpate!\n");
            }
            break;
    }

    printf("\n=======================================\n");
    return 0;
}
    
    
