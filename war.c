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
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int numJogadores);
void exibirMenuAtaque(Territorio* territorios, int quantidade);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char corJogador[]);
void exibirMissao(char* missao, int jogador);

// Vetor de missões estratégicas pré-definidas
char* missoesPredefinidas[] = {
    "Conquistar 3 territorios seguidos no mapa",
    "Eliminar todas as tropas da cor Vermelha",
    "Controlar pelo menos 5 territorios no total",
    "Conquistar todos os territorios de uma regiao especifica",
    "Manter 10 tropas em um unico territorio por 2 turnos"
};

#define TOTAL_MISSOES 5

// Função para cadastrar territórios com alocação dinâmica
Territorio* cadastrarTerritorios(int quantidade) {
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

// Função para atribuir missão a um jogador (passagem por referência)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    // Sorteia uma missão aleatória
    int indiceMissao = rand() % totalMissoes;
    
    // Copia a missão para o destino usando strcpy
    strcpy(destino, missoes[indiceMissao]);
}

// Função para exibir a missão de um jogador (passagem por valor)
void exibirMissao(char* missao, int jogador) {
    printf("\n=== MISSAO DO JOGADOR %d ===\n", jogador);
    printf("Sua missao: %s\n", missao);
    printf("Cumpra esta missao para vencer o jogo!\n");
}

// Função para verificar se a missão foi cumprida (lógica simplificada)
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char corJogador[]) {
    // Verifica qual missão está atribuída e aplica a lógica correspondente
    
    // Missão 1: Conquistar 3 territórios seguidos
    if (strstr(missao, "3 territorios seguidos") != NULL) {
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 &&
                strcmp(mapa[i+1].cor, corJogador) == 0 &&
                strcmp(mapa[i+2].cor, corJogador) == 0) {
                return 1; // Missão cumprida
            }
        }
    }
    
    // Missão 2: Eliminar todas as tropas da cor Vermelha
    else if (strstr(missao, "cor Vermelha") != NULL) {
        int vermelhoExiste = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0) {
                vermelhoExiste = 1;
                break;
            }
        }
        return !vermelhoExiste; // Retorna 1 se Vermelho não existe mais
    }
    
    // Missão 3: Controlar pelo menos 5 territórios
    else if (strstr(missao, "5 territorios") != NULL) {
        int territoriosControlados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territoriosControlados++;
            }
        }
        return territoriosControlados >= 5;
    }
    
    // Missão 4: Conquistar todos os territórios de uma região específica
    else if (strstr(missao, "regiao especifica") != NULL) {
        // Considerando os 3 primeiros territórios como uma "região"
        int regiaoConquistada = 1;
        for (int i = 0; i < 3 && i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) {
                regiaoConquistada = 0;
                break;
            }
        }
        return regiaoConquistada;
    }
    
    // Missão 5: Manter 10 tropas em um único território
    else if (strstr(missao, "10 tropas") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 10) {
                return 1;
            }
        }
    }
    
    return 0; // Missão não cumprida
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

// Função para liberar toda a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int numJogadores) {
    // Libera o vetor de territórios
    free(mapa);
    
    // Libera as missões de cada jogador
    for (int i = 0; i < numJogadores; i++) {
        free(missoesJogadores[i]);
    }
    
    printf("Memoria liberada com sucesso!\n");
}

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    int quantidade, numJogadores;
    Territorio* territorios;
    
    printf("=== SISTEMA DE BATALHA COM MISSOES ESTRATEGICAS ===\n");
    
    // Solicita o número de territórios ao usuário
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);
    
    // Solicita o número de jogadores
    printf("Quantos jogadores vao participar? ");
    scanf("%d", &numJogadores);
    
    // Valida as entradas
    if (quantidade <= 0 || numJogadores <= 0) {
        printf("Quantidade invalida! Deve ser maior que zero.\n");
        return 1;
    }
    
    // Aloca memória para as missões dos jogadores
    char** missoesJogadores = (char**)malloc(numJogadores * sizeof(char*));
    char** coresJogadores = (char**)malloc(numJogadores * sizeof(char*));
    
    for (int i = 0; i < numJogadores; i++) {
        missoesJogadores[i] = (char*)malloc(100 * sizeof(char)); // Missões podem ter até 100 chars
        coresJogadores[i] = (char*)malloc(10 * sizeof(char));
        
        printf("\nDigite a cor do exercito do Jogador %d: ", i + 1);
        scanf("%9s", coresJogadores[i]);
    }
    
    // Cadastra os territórios com alocação dinâmica
    territorios = cadastrarTerritorios(quantidade);
    
    // Atribui missões para cada jogador
    for (int i = 0; i < numJogadores; i++) {
        atribuirMissao(missoesJogadores[i], missoesPredefinidas, TOTAL_MISSOES);
        exibirMissao(missoesJogadores[i], i + 1);
    }
    
    // Exibe os territórios cadastrados
    exibirTerritorios(territorios, quantidade);
    
    int opcao, turno = 0;
    int jogoAtivo = 1;
    
    do {
        turno++;
        printf("\n=== TURNO %d ===\n", turno);
        
        for (int jogadorAtual = 0; jogadorAtual < numJogadores && jogoAtivo; jogadorAtual++) {
            printf("\n--- Vez do Jogador %d (%s) ---\n", jogadorAtual + 1, coresJogadores[jogadorAtual]);
            
            printf("\n=== MENU PRINCIPAL ===\n");
            printf("1. Realizar ataque\n");
            printf("2. Exibir territorios\n");
            printf("3. Ver minha missao\n");
            printf("4. Passar turno\n");
            printf("5. Sair do jogo\n");
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
                    // Exibe a missão do jogador atual
                    exibirMissao(missoesJogadores[jogadorAtual], jogadorAtual + 1);
                    break;
                    
                case 4:
                    printf("Jogador %d passou o turno.\n", jogadorAtual + 1);
                    break;
                    
                case 5:
                    jogoAtivo = 0;
                    break;
                    
                default:
                    printf("Opcao invalida! Tente novamente.\n");
            }
            
            // Verifica silenciosamente se a missão foi cumprida
            if (verificarMissao(missoesJogadores[jogadorAtual], territorios, quantidade, coresJogadores[jogadorAtual])) {
                printf("\n*** PARABENS JOGADOR %d! ***\n", jogadorAtual + 1);
                printf("*** VOCE CUMPRIU SUA MISSAO E VENCEU O JOGO! ***\n");
                printf("Missao cumprida: %s\n", missoesJogadores[jogadorAtual]);
                jogoAtivo = 0;
                break;
            }
        }
        
    } while (opcao != 5 && jogoAtivo);
    
    printf("\n=== FIM DO JOGO ===\n");
    
    // Libera toda a memória alocada dinamicamente
    liberarMemoria(territorios, missoesJogadores, numJogadores);
    
    // Libera as cores dos jogadores
    for (int i = 0; i < numJogadores; i++) {
        free(coresJogadores[i]);
    }
    free(coresJogadores);
    free(missoesJogadores);
    
    return 0;
}