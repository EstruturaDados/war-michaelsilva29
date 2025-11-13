#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
Territorio* cadastrarTerritorios(int quantidade);
void exibirTerritorios(Territorio* territorios, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void exibirMenuAtaque(Territorio* territorios, int quantidade);

// Função para cadastrar territórios com alocação dinâmica
Territorio* cadastrarTerritorios(int quantidade) {
    // Alocação dinâmica de memória para o vetor de territórios
    Territorio* territorios = (Territorio*)malloc(quantidade * sizeof(Territorio));
    
    if (territorios == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    
    printf("\n=== CADASTRO DE TERRITORIOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: ");
        scanf("%29s", territorios[i].nome);
        printf("Cor do exercito: ");
        scanf("%9s", territorios[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    
    return territorios;
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* territorios, int quantidade) {
    printf("\n=== TERRITORIOS CADASTRADOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
}

// Função para simular um ataque entre territórios usando ponteiros
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("%s (%s) atacando %s (%s)\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    // Validação: não permitir ataque a território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("ERRO: Voce nao pode atacar um territorio da mesma cor!\n");
        return;
    }
    
    // Verifica se o atacante tem tropas suficientes
    if (atacante->tropas <= 0) {
        printf("ERRO: O territorio atacante nao tem tropas suficientes!\n");
        return;
    }
    
    // Simula a rolagem de dados (1-6 para cada lado)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    // Determina o vencedor da batalha
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence - conquista o território
        printf("VITORIA DO ATACANTE!\n");
        printf("%s agora pertence a %s!\n", defensor->nome, atacante->cor);
        
        // Atualiza o controle do território (muda a cor)
        strcpy(defensor->cor, atacante->cor);
        
        // Transfere metade das tropas do defensor (mínimo 1)
        int tropasTransferidas = defensor->tropas / 2;
        if (tropasTransferidas < 1) {
            tropasTransferidas = 1;
        }
        defensor->tropas = tropasTransferidas;
        
        printf("Tropas em %s atualizadas para: %d\n", defensor->nome, defensor->tropas);
        
    } else if (dadoAtacante < dadoDefensor) {
        // Defensor vence - atacante perde uma tropa
        printf("VITORIA DO DEFENSOR!\n");
        
        // Atacante perde uma tropa
        atacante->tropas--;
        printf("%s perdeu 1 tropa. Tropas restantes: %d\n", 
               atacante->nome, atacante->tropas);
        
    } else {
        // Empate - nada acontece
        printf("EMPATE! Nenhum territorio foi conquistado.\n");
    }
}

// Função para exibir o menu de seleção de ataque
void exibirMenuAtaque(Territorio* territorios, int quantidade) {
    printf("\n=== MENU DE ATAQUE ===\n");
    printf("Selecione os territorios pelo numero:\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("%d. %s (%s) - Tropas: %d\n", 
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// Função para liberar a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("Memoria liberada com sucesso!\n");
}

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    int quantidade;
    Territorio* territorios;
    
    printf("=== SISTEMA DE BATALHA ===\n");
    
    // Solicita o número de territórios ao usuário
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);
    
    // Valida a quantidade de territórios
    if (quantidade <= 0) {
        printf("Quantidade invalida! Deve ser maior que zero.\n");
        return 1;
    }
    
    // Cadastra os territórios com alocação dinâmica
    territorios = cadastrarTerritorios(quantidade);
    
    // Exibe os territórios cadastrados
    exibirTerritorios(territorios, quantidade);
    
    int opcao;
    do {
        // Menu principal do sistema
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Realizar ataque\n");
        printf("2. Exibir territorios\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                // Realizar ataque entre territórios
                exibirMenuAtaque(territorios, quantidade);
                
                int atacanteIdx, defensorIdx;
                
                // Solicita seleção do atacante e defensor
                printf("\nSelecione o territorio ATACANTE (numero): ");
                scanf("%d", &atacanteIdx);
                printf("Selecione o territorio DEFENSOR (numero): ");
                scanf("%d", &defensorIdx);
                
                // Valida os índices informados
                if (atacanteIdx < 1 || atacanteIdx > quantidade || 
                    defensorIdx < 1 || defensorIdx > quantidade) {
                    printf("ERRO: Indices invalidos! Use numeros entre 1 e %d.\n", quantidade);
                    break;
                }
                
                // Valida se não está tentando atacar o mesmo território
                if (atacanteIdx == defensorIdx) {
                    printf("ERRO: Voce nao pode atacar o mesmo territorio!\n");
                    break;
                }
                
                // Obtém ponteiros para os territórios selecionados
                Territorio* atacante = &territorios[atacanteIdx - 1];
                Territorio* defensor = &territorios[defensorIdx - 1];
                
                // Executa o ataque usando ponteiros
                atacar(atacante, defensor);
                
                // Exibe os territórios atualizados após o ataque
                printf("\n=== SITUACAO POS-ATAQUE ===\n");
                printf("Atacante - %s: %d tropas (%s)\n", 
                       atacante->nome, atacante->tropas, atacante->cor);
                printf("Defensor - %s: %d tropas (%s)\n", 
                       defensor->nome, defensor->tropas, defensor->cor);
                break;
            }
            
            case 2:
                // Exibe todos os territórios
                exibirTerritorios(territorios, quantidade);
                break;
                
            case 3:
                printf("Saindo do sistema...\n");
                break;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
    } while (opcao != 3);
    
    // Libera a memória alocada dinamicamente
    liberarMemoria(territorios);
    
    return 0;
}