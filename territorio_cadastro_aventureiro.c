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
Territorio* cadastrarTerritorios(int numTerritorios);
void exibirTerritorios(Territorio* territorios, int numTerritorios);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int numTerritorios;
    Territorio* territorios;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Solicita ao usuário o número de territórios
    printf("Digite o número de territórios: ");
    scanf("%d", &numTerritorios);
    getchar(); // Consome o '\n' deixado pelo scanf

    // Aloca dinamicamente o vetor de territórios
    territorios = cadastrarTerritorios(numTerritorios);

    // Loop principal do jogo
    int escolha;
    do {
        printf("\n--- Menu ---\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // Consome o '\n' deixado pelo scanf

        switch (escolha) {
            case 1:
                exibirTerritorios(territorios, numTerritorios);
                break;
            case 2: {
                int atacante_idx, defensor_idx;

                printf("Escolha o território atacante (0 a %d): ", numTerritorios - 1);
                scanf("%d", &atacante_idx);
                getchar();

                printf("Escolha o território defensor (0 a %d): ", numTerritorios - 1);
                scanf("%d", &defensor_idx);
                getchar();

                // Validação das escolhas
                if (atacante_idx < 0 || atacante_idx >= numTerritorios || defensor_idx < 0 || defensor_idx >= numTerritorios) {
                    printf("Índices inválidos.\n");
                    break;
                }

                if (strcmp(territorios[atacante_idx].cor, territorios[defensor_idx].cor) == 0) {
                    printf("Não é possível atacar um território da mesma cor.\n");
                    break;
                }
                
                atacar(&territorios[atacante_idx], &territorios[defensor_idx]);
                exibirTerritorios(territorios, numTerritorios); // Exibe após o ataque

                break;
            }
            case 0:
                printf("Saindo do jogo.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    // Libera a memória alocada
    liberarMemoria(territorios);

    return 0;
}

// Função para cadastrar os territórios
Territorio* cadastrarTerritorios(int numTerritorios) {
    Territorio* territorios = (Territorio*)calloc(numTerritorios, sizeof(Territorio));

    if (territorios == NULL) {
        printf("Erro ao alocar memória para os territórios.\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    }

    printf("==============================\n");
    printf("Cadastro de Territórios\n");
    printf("==============================\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("---\nCadastrando Território %d---\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;

        printf("Cor do Exército: ");
        scanf("%s", territorios[i].cor);
        getchar(); // Consume o '\n' deixado pelo scanf

        printf("Quantidade de Tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Consume o '\n' deixado pelo scanf
    }

    return territorios;
}

// Função para exibir os dados dos territórios
void exibirTerritorios(Territorio* territorios, int numTerritorios) {
    printf("\n--- Dados dos Territórios Cadastrados --- \n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
    }
}

// Função para simular um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- Simulação de Ataque ---\n");
    printf("Atacante: %s (%s, %d tropas)\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s, %d tropas)\n", defensor->nome, defensor->cor, defensor->tropas);

    // Simulação da batalha com dados aleatórios
    int ataque = (rand() % 6) + 1; // Gera um número aleatório entre 1 e 6
    int defesa = (rand() % 6) + 1; // Gera um número aleatório entre 1 e 6

    printf("Resultado do ataque: %d\n", ataque);
    printf("Resultado da defesa: %d\n", defesa);

    if (ataque > defesa) {
        printf("O atacante venceu!\n");

        // Atualiza os dados do defensor
        strcpy(defensor->cor, atacante->cor); // Transfere a cor
        defensor->tropas = atacante->tropas / 2;  // Transfere metade das tropas (inteiro)
        atacante->tropas /= 2; // Atacante perde metade das tropas que mandou para o ataque.
    } else {
        printf("O defensor venceu!\n");
        atacante->tropas--;  // Atacante perde uma tropa

        if(atacante->tropas < 0){
            atacante->tropas = 0;
        }
    }

    printf("--- Resultados do Ataque ---\n");
    printf("Atacante: %s (%s, %d tropas)\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s, %d tropas)\n", defensor->nome, defensor->cor, defensor->tropas);
}

// Função para liberar a memória alocada para os territórios
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("Memória liberada.\n");
}
