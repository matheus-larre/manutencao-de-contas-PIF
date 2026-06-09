#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_NAME "contas.bin"

typedef struct {
    int numero_conta;
    char nome[50];
    double saldo;
    bool ativo;
} Cliente;

void menu() {
    printf("\n--- Sistema de Manutencao de Contas ---\n");
    printf("1. Cadastrar um novo cliente em uma posicao especifica\n");
    printf("2. Consultar um cliente pelo numero da conta\n");
    printf("3. Atualizar o saldo de um cliente\n");
    printf("4. Encerra conta (remover cliente)\n");
    printf("5. Listar todos os clientes\n");
    printf("6. Restaurar a leitura do arquivo (rewind)\n");
    printf("7. Encerrar\n");
    printf("Escolha uma opcao: ");
}

void cadastrar_cliente(FILE *fp) {
    int posicao;
    Cliente c;
    printf("Digite a posicao (0, 1, 2...): ");
    scanf("%d", &posicao);
    
    fseek(fp, posicao * sizeof(Cliente), SEEK_SET);
    
    printf("Numero da conta: ");
    scanf("%d", &c.numero_conta);
    printf("Nome: ");
    scanf(" %[^\n]s", c.nome);
    printf("Saldo: ");
    scanf("%lf", &c.saldo);
    c.ativo = true;
    
    fwrite(&c, sizeof(Cliente), 1, fp);
    printf("Cliente cadastrado na posicao %d.\n", posicao);
}

void consultar_cliente(FILE *fp) {
    int numero;
    Cliente c;
    bool encontrado = false;
    
    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    
    rewind(fp);
    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.ativo && c.numero_conta == numero) {
            printf("\nConta: %d\nNome: %s\nSaldo: %.2f\n", c.numero_conta, c.nome, c.saldo);
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void atualizar_saldo(FILE *fp) {
    int numero;
    Cliente c;
    long pos;
    bool encontrado = false;
    
    printf("Digite o numero da conta para atualizar saldo: ");
    scanf("%d", &numero);
    
    rewind(fp);
    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.ativo && c.numero_conta == numero) {
            pos = ftell(fp) - sizeof(Cliente);
            printf("Saldo atual: %.2f\nNovo saldo: ", c.saldo);
            scanf("%lf", &c.saldo);
            
            fseek(fp, pos, SEEK_SET);
            fwrite(&c, sizeof(Cliente), 1, fp);
            printf("Saldo atualizado com sucesso!\n");
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void remover_cliente(FILE *fp) {
    int numero;
    Cliente c;
    long pos;
    bool encontrado = false;
    
    printf("Digite o numero da conta para encerrar: ");
    scanf("%d", &numero);
    
    rewind(fp);
    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.ativo && c.numero_conta == numero) {
            pos = ftell(fp) - sizeof(Cliente);
            c.ativo = false;
            
            fseek(fp, pos, SEEK_SET);
            fwrite(&c, sizeof(Cliente), 1, fp);
            printf("Conta encerrada com sucesso.\n");
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void listar_clientes(FILE *fp) {
    Cliente c;
    bool existem_clientes = false;
    
    printf("\n--- Listagem de Clientes ---\n");
    // Nao damos rewind aqui automaticamente se quisermos testar a opcao 6
    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (c.ativo) {
            printf("Conta: %d | Nome: %-20s | Saldo: %.2f\n", c.numero_conta, c.nome, c.saldo);
            existem_clientes = true;
        }
    }
    
    if (!existem_clientes) {
        printf("Nenhum cliente ativo encontrado ou fim do arquivo atingido.\n");
    }
}

int main() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        fp = fopen(FILE_NAME, "wb+");
        if (fp == NULL) {
            perror("Erro ao abrir arquivo");
            return 1;
        }
    }
    
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: cadastrar_cliente(fp); break;
            case 2: consultar_cliente(fp); break;
            case 3: atualizar_saldo(fp); break;
            case 4: remover_cliente(fp); break;
            case 5: listar_clientes(fp); break;
            case 6: 
                rewind(fp); 
                printf("Leitura do arquivo restaurada ao inicio.\n");
                break;
            case 7: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 7);
    
    fclose(fp);
    return 0;
}
