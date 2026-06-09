# Manutenção de Contas - PIF

Este projeto é um sistema simples de manutenção de contas bancárias desenvolvido em C11 para a disciplina de Programação Imperativa Funcional.

## Funcionalidades

O sistema permite realizar as seguintes operações em um arquivo binário de registros de tamanho fixo:

1.  **Cadastrar um novo cliente em uma posição específica:** Utiliza `fseek()` para posicionar o ponteiro do arquivo no índice desejado e `fwrite()` para gravar os dados.
2.  **Consultar um cliente pelo número da conta:** Percorre o arquivo comparando o número da conta fornecido.
3.  **Atualizar o saldo de um cliente:** Localiza o cliente, posiciona o ponteiro de volta ao início do registro com `fseek()` e sobrescreve com `fwrite()`.
4.  **Encerrar conta (remover cliente):** Realiza uma "exclusão lógica" marcando o campo `ativo` como `false`.
5.  **Listar todos os clientes:** Lê sequencialmente o arquivo a partir da posição atual do ponteiro.
6.  **Restaurar a leitura do arquivo:** Utiliza `rewind()` para voltar o ponteiro para o início do arquivo, permitindo repetir a listagem completa.
7.  **Encerrar:** Fecha o arquivo e finaliza o programa.

## Tecnologias Utilizadas

-   Linguagem C (Padrão C11)
-   Manipulação de Arquivos Binários (`fopen`, `fread`, `fwrite`, `fseek`, `ftell`, `rewind`)

## Como Compilar e Executar

Certifique-se de ter um compilador C instalado (como GCC).

1.  Abra o terminal na pasta do projeto.
2.  Compile o código:
    ```bash
    gcc main.c -o manutencao_contas
    ```
3.  Execute o programa:
    ```bash
    ./manutencao_contas
    ```

## Estrutura de Dados

A estrutura utilizada para representar um cliente é:

```c
typedef struct {
    int numero_conta;
    char nome[50];
    double saldo;
    bool ativo;
} Cliente;
```
