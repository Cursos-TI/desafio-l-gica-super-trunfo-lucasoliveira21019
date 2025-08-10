#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Declaração do vetor de structs Territorio
    Territorio territorios[5];

    // Entrada de dados para os 5 territórios
    printf("==============================\n");
    printf("vamos cadastrar nossos 5 territorios iniciais\n");
    printf("Cadastro de Territórios\n");
    printf("==============================\n");
    for (int i = 0; i < 5; i++) {
        printf("---\nCadastrando Território %d---\n", i + 1);

        printf("Nome: ");
        // Usando fgets para evitar problemas com espaços no nome
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        // Removendo o '\n' do final da string lida por fgets
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;

        printf("Cor do Exército: ");
        scanf("%s", territorios[i].cor);

        printf("Quantidade de Tropas: ");
        scanf("%d", &territorios[i].tropas);

        // Limpar o buffer do teclado após o scanf para evitar problemas com o próximo fgets
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Exibição dos dados dos territórios cadastrados
    printf("\nDados dos Territórios Cadastrados:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
