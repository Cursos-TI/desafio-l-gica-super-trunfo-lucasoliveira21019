#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Regiao
typedef struct {
    char ident[30];         // Identificador da região
    char grupo[10];          // Grupo dominante (cor do exército)
    int efetivo;            // Número de soldados
} Regiao;

// Protótipos das funções
Regiao* criar_regioes(int num_regioes);
void exibir_mapa(Regiao* regioes, int num_regioes);
void confrontar(Regiao* atacante, Regiao* defensor);
void desalocar_memoria(Regiao* mapa, char* plano_jogador); // Alterado o nome
void definir_plano(char* destino, char* planos[], int total_planos); // Alterado o nome
int verificar_objetivo(char* plano, Regiao* mapa, int extensao); // Alterado o nome

int main() {
    int num_regioes;
    Regiao* regioes;
    char* plano_jogador;       // Plano estratégico do jogador
    char* planos[] = {       // Vetor de planos estratégicos
        "Dominar 4 regioes consecutivas.",
        "Aniquilar todas as forcas do grupo verde.",
        "Acumular mais de 25 soldados em uma regiao.",
        "Conquistar 6 regioes distintas.",
        "Controlar um ponto chave por 4 rodadas."
    };
    int total_planos = sizeof(planos) / sizeof(planos[0]);

    // Inicializa o gerador de aleatoriedade
    srand(time(NULL));

    // Solicita ao usuário a quantidade de regiões
    printf("Informe a quantidade de regioes: ");
    scanf("%d", &num_regioes);
    getchar(); // Limpa o buffer

    // Aloca espaço para o mapa
    regioes = criar_regioes(num_regioes);

    // Aloca espaço para o plano do jogador
    plano_jogador = (char*)malloc(100 * sizeof(char));
    if (plano_jogador == NULL) {
        printf("Erro ao alocar memoria para o plano.\n");
        desalocar_memoria(regioes, NULL);
        exit(1);
    }

    // Define o plano do jogador
    definir_plano(plano_jogador, planos, total_planos);
    printf("\nSeu plano: %s\n", plano_jogador);

    // Loop principal
    int escolha;
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1 - Visualizar Mapa\n");
        printf("2 - Iniciar Conflito\n");
        printf("0 - Encerrar Jogo\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer

        switch (escolha) {
            case 1:
                exibir_mapa(regioes, num_regioes);
                break;
            case 2: {
                int atk_idx, def_idx;

                printf("Regiao atacante (0 a %d): ", num_regioes - 1);
                scanf("%d", &atk_idx);
                getchar();

                printf("Regiao defensora (0 a %d): ", num_regioes - 1);
                scanf("%d", &def_idx);
                getchar();

                // Validação das escolhas
                if (atk_idx < 0 || atk_idx >= num_regioes || def_idx < 0 || def_idx >= num_regioes) {
                    printf("Indices invalidos.\n");
                    break;
                }

                if (strcmp(regioes[atk_idx].grupo, regioes[def_idx].grupo) == 0) {
                    printf("Nao e possivel atacar uma regiao do mesmo grupo.\n");
                    break;
                }

                confrontar(&regioes[atk_idx], &regioes[def_idx]);
                exibir_mapa(regioes, num_regioes);

                // Verifica se o objetivo foi alcancado
                if (verificar_objetivo(plano_jogador, regioes, num_regioes)) {
                    printf("\nParabens! Seu plano foi concretizado! Vitoria!\n");
                    escolha = 0;
                }

                break;
            }
            case 0:
                printf("Finalizando o jogo.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (escolha != 0);

    // Libera a memória
    desalocar_memoria(regioes, plano_jogador);

    return 0;
}

// Função para criar as regiões
Regiao* criar_regioes(int num_regioes) {
    Regiao* regioes = (Regiao*)calloc(num_regioes, sizeof(Regiao));

    if (regioes == NULL) {
        printf("Erro ao alocar memoria para as regioes.\n");
        exit(1);
    }

    printf("==============================\n");
    printf("Cadastro de Regioes\n");
    printf("==============================\n");
    for (int i = 0; i < num_regioes; i++) {
        printf("---\nRegiao %d---\n", i + 1);

        printf("Nome: ");
        fgets(regioes[i].ident, sizeof(regioes[i].ident), stdin);
        regioes[i].ident[strcspn(regioes[i].ident, "\n")] = 0;

        printf("Grupo: ");
        scanf("%s", regioes[i].grupo);
        getchar(); // Limpa o buffer

        printf("Efetivo: ");
        scanf("%d", &regioes[i].efetivo);
        getchar(); // Limpa o buffer
    }

    return regioes;
}

// Função para exibir as regiões
void exibir_mapa(Regiao* regioes, int num_regioes) {
    printf("\n--- Situacao Atual do Mapa ---\n");
    for (int i = 0; i < num_regioes; i++) {
        printf("\nRegiao %d:\n", i + 1);
        printf("Nome: %s\n", regioes[i].ident);
        printf("Grupo: %s\n", regioes[i].grupo);
        printf("Efetivo: %d\n", regioes[i].efetivo);
    }
}

// Função para simular um conflito
void confrontar(Regiao* atacante, Regiao* defensor) {
    printf("\n--- Simulação de Conflito ---\n");
    printf("Atacante: %s (%s, %d)\n", atacante->ident, atacante->grupo, atacante->efetivo);
    printf("Defensor: %s (%s, %d)\n", defensor->ident, defensor->grupo, defensor->efetivo);

    // Simula o combate
    int ataque = (rand() % 6) + 1;
    int defesa = (rand() % 6) + 1;

    printf("Ataque: %d\n", ataque);
    printf("Defesa: %d\n", defesa);

    if (ataque > defesa) {
        printf("Atacante prevaleceu!\n");

        // Atualiza
        strcpy(defensor->grupo, atacante->grupo);
        defensor->efetivo = atacante->efetivo / 2;
        atacante->efetivo /= 2;
    } else {
        printf("Defensor resistiu!\n");
        atacante->efetivo--;

        if(atacante->efetivo < 0){
            atacante->efetivo = 0;
        }
    }

    printf("--- Resultado ---\n");
    printf("Atacante: %s (%s, %d)\n", atacante->ident, atacante->grupo, atacante->efetivo);
    printf("Defensor: %s (%s, %d)\n", defensor->ident, defensor->grupo, defensor->efetivo);
}

// Função para desalocar a memória
void desalocar_memoria(Regiao* mapa, char* plano_jogador) {
    free(mapa);
    if (plano_jogador != NULL) {
        free(plano_jogador);
    }
    printf("Memoria liberada.\n");
}

// Função para definir o plano estratégico
void definir_plano(char* destino, char* planos[], int total_planos) {
    int indice = rand() % total_planos;
    strcpy(destino, planos[indice]);
}

// Função para verificar o objetivo
int verificar_objetivo(char* plano, Regiao* mapa, int extensao) {
    // Lógica de exemplo
    if (strcmp(plano, "Acumular mais de 25 soldados em uma regiao.") == 0) {
        for (int i = 0; i < extensao; i++) {
            if (mapa[i].efetivo > 25) {
                return 1;
            }
        }
        return 0;
    }
    else if (strcmp(plano, "Aniquilar todas as forcas do grupo verde.") == 0) {
        int forcas_verdes_encontradas = 0;
        for (int i = 0; i < extensao; i++) {
            if (strcmp(mapa[i].grupo, "verde") == 0) {
                forcas_verdes_encontradas++;
            }
        }
        if(forcas_verdes_encontradas == 0) return 1;
        else return 0;

    }
    else if (strcmp(plano, "Conquistar 6 regioes distintas.") == 0) {
        int territoriosConquistados = 0;
        for (int i = 0; i < extensao; i++) {
            territoriosConquistados++;
        }
        if(territoriosConquistados == 6) return 1;
        else return 0;

    }
    
    else if (strcmp(plano, "Controlar um ponto chave por 4 rodadas.") == 0) {
        //implementar a lógica de contar os turnos
    }

    return 0;
}
