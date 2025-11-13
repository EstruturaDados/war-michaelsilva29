#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];      // Nome do território (até 29 caracteres + \0)
    char cor[10];       // Cor do exército (até 9 caracteres + \0)
    int tropas;         // Quantidade de tropas
};

int main() {
    // Declaração do vetor de structs com capacidade para 5 territórios
    struct Territorio territorios[5];
    
    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS ===\n\n");
    
    // CADASTRO DOS TERRITORIOS
    // Laço for para preencher os dados dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("--- Cadastro do Territorio %d ---\n", i + 1);
        
        // Entrada do nome do território
        printf("Digite o nome do territorio: ");
        scanf("%29s", territorios[i].nome);
        
        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        
        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n"); // Linha em branco para melhor organização
    }
    
    // EXIBIÇÃO DOS DADOS CADASTRADOS
    printf("=== TERRITORIOS CADASTRADOS ===\n\n");
    
    // Laço for para exibir todos os territórios cadastrados
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }
    
    return 0;
}