# Super Trunfo - Cadastro de Territórios

Este projeto implementa um sistema simples para cadastrar e exibir informações sobre territórios, como nome, cor do exército e quantidade de tropas.  É parte de um desafio de programação para consolidar conceitos de structs e entrada/saída de dados em C.

## Funcionalidades

*   **Cadastro de Territórios:** Permite o cadastro de 5 territórios, solicitando o nome, cor do exército e número de tropas.
*   **Exibição de Dados:** Exibe as informações de todos os territórios cadastrados após o preenchimento.

## Como Usar

1.  **Clonar o Repositório:**

    ```bash
    git clone <URL_DO_SEU_REPOSITÓRIO>
    cd <NOME_DO_REPOSITÓRIO>
    ```

2.  **Compilar o Código:**

    Certifique-se de ter um compilador C instalado (como o GCC).

    ```bash
    gcc super_trunfo.c -o super_trunfo
    ```

3.  **Executar o Programa:**

    ```bash
    ./super_trunfo
    ```

    O programa solicitará que você insira os dados de cada território.

4.  **Visualizar os Dados:**

    Após o cadastro dos 5 territórios, o programa exibirá as informações de cada um.

## Estrutura do Código

*   `super_trunfo.c`:  Contém o código fonte principal.  A struct `Territorio` é definida para armazenar os dados de cada território.  O programa utiliza `fgets` para ler o nome dos territórios (permitindo espaços) e `scanf` para ler a cor e o número de tropas.  A limpeza do buffer do teclado também foi implementada para evitar problemas com a leitura de dados.

## Requisitos Técnicos

*   Linguagem C
*   Bibliotecas: `stdio.h`, `string.h`



## Autor
Lucas Oliveira
